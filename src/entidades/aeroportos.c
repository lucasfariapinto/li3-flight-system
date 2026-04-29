#include "entidades/aeroportos.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include "gestor_entidades/gestor.h"
#include "utils/string_pool.h"
#include "utils/utils.h"
struct aeroporto
{
    int code;            // código IATA do aeroporto
    const char *name;    // nome do aeroporto
    const char *city;    // cidade onde o aeroporto se encontra localizado
    const char *country; // país onde o aeroporto se encontra localizado
    // float latitude;          // latitude do aeroporto em graus decimais
    // float longitude;         // longitude do aeroporto em graus decimais
    // char *icao;              // código ICAO do aeroporto
    GArray *departure_dates; // datas de partida dos voos que saem deste aeroporto
    aeroporto_type type;     // tipo do aeroporto
    int passageiros_aterram; // número de passageiros que aterram neste aeroporto
    int passageiros_partem;  // número de passageiros que partem deste aeroporto
};

void free_aeroporto(void *a)
{
    Aeroporto aeroporto = a;
    if (aeroporto)
    {
        g_array_free(aeroporto->departure_dates, TRUE);
        // libertado no string pool
        // free(aeroporto->code);
        // free(aeroporto->name);
        // free(aeroporto->city);
        // free(aeroporto->country);
        // free(aeroporto->icao);
        free(aeroporto);
    }
}

Aeroporto initialize_aeroporto()
{
    Aeroporto aeroporto = malloc(sizeof(struct aeroporto));
    aeroporto->departure_dates = g_array_new(FALSE, FALSE, sizeof(int));
    aeroporto->name = NULL;
    aeroporto->city = NULL;
    aeroporto->country = NULL;
    // aeroporto->latitude = 0.0;
    // aeroporto->longitude = 0.0;
    // aeroporto->icao = NULL;
    aeroporto->passageiros_aterram = 0;
    aeroporto->passageiros_partem = 0;
    return aeroporto;
}

// Getters

int get_aeroporto_code(Aeroporto aeroporto)
{
    return aeroporto->code;
}

char *get_aeroporto_name(Aeroporto aeroporto)
{
    return strdup(aeroporto->name);
}

char *get_aeroporto_city(Aeroporto aeroporto)
{
    return strdup(aeroporto->city);
}

char *get_aeroporto_country(Aeroporto aeroporto)
{
    return strdup(aeroporto->country);
}

int get_aeroporto_passageiros_aterram(Aeroporto aeroporto)
{
    return aeroporto->passageiros_aterram;
}

int get_aeroporto_passageiros_partem(Aeroporto aeroporto)
{
    return aeroporto->passageiros_partem;
}

aeroporto_type get_aeroporto_type(Aeroporto aeroporto)
{
    return aeroporto->type;
}

// Setters
void set_aeroporto_code(Aeroporto aeroporto, char *code)
{
    aeroporto->code = iata_to_int(code);
}

void set_aeroporto_name(Aeroporto aeroporto, char *name, String_Pool sp)
{
    aeroporto->name = insert_string_in_pool(name, sp);
}

void set_aeroporto_city(Aeroporto aeroporto, char *city, String_Pool sp)
{
    aeroporto->city = insert_string_in_pool(city, sp);
}

void set_aeroporto_country(Aeroporto aeroporto, char *country, String_Pool sp)
{
    aeroporto->country = insert_string_in_pool(country, sp);
}

void set_aeroporto_type(Aeroporto aeroporto, aeroporto_type type)
{
    aeroporto->type = type;
}

void set_aeroporto_passageiros_aterram(Aeroporto aeroporto, int passageiros)
{
    aeroporto->passageiros_aterram = passageiros;
}

void set_aeroporto_passageiros_partem(Aeroporto aeroporto, int passageiros)
{
    aeroporto->passageiros_partem = passageiros;
}

void incrementa_aeroporto_passageiros_aterram(Aeroporto aeroporto)
{
    aeroporto->passageiros_aterram += 1;
}
void incrementa_aeroporto_passageiros_partem(Aeroporto aeroporto)
{
    aeroporto->passageiros_partem += 1;
}

void insert_aeroporto_departure_date(Aeroporto aeroporto, int date)
{
    g_array_append_val(aeroporto->departure_dates, date);
}

int compare_ints(gconstpointer a, gconstpointer b) // Para ordenar as datas por ordem crescente
{
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;

    return int_a - int_b;
}

void sort_aeroporto_departure_dates(Aeroporto aeroporto)
{
    g_array_sort(aeroporto->departure_dates, compare_ints);
}

Aeroporto create_aeroporto(char *code, char *name, char *city, char *country, aeroporto_type type, String_Pool sp)
{
    Aeroporto aeroporto = initialize_aeroporto();
    set_aeroporto_code(aeroporto, code);
    set_aeroporto_name(aeroporto, name, sp);
    set_aeroporto_city(aeroporto, city, sp);
    set_aeroporto_country(aeroporto, country, sp);
    set_aeroporto_type(aeroporto, type);
    return aeroporto;
}

int get_number_of_departures_between_dates(Aeroporto aeroporto, int start_date, int end_date)
{
    GArray *a = aeroporto->departure_dates;
    int size = a->len;

    if (size == 0)
        return 0;

    int left = 0, right = size - 1;
    int i_start = size;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int value = g_array_index(a, int, mid);

        if (value >= start_date)
        {
            i_start = mid;
            right = mid - 1; // tenta encontrar a posição ainda mais à esquerda
        }
        else
        {
            left = mid + 1;
        }
    }

    // Se nenhum valor >= start_date —> não há resultados no intervalo
    if (i_start == size)
        return 0;

    left = i_start;
    right = size - 1;
    int i_end = -1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int value = g_array_index(a, int, mid);

        if (value <= end_date)
        {
            i_end = mid;
            left = mid + 1; // tenta achar uma posição maior válida
        }
        else
        { // valor "inválido" inicial
            right = mid - 1;
        }
    }

    // Se nenhum valor <= end_date —> não há resultados no intervalo
    if (i_end == -1 || i_start > i_end)
        return 0;

    return i_end - i_start + 1;
}

char *aeroporto_type_to_string(aeroporto_type type)
{
    switch (type)
    {
    case SMALL_AIRPORT:
        return strdup("small_airport");
    case MEDIUM_AIRPORT:
        return strdup("medium_airport");
    case LARGE_AIRPORT:
        return strdup("large_airport");
    case HELIPORT:
        return strdup("heliport");
    case SEAPLANE_BASE:
        return strdup("seaplane_base");
    default:
        return strdup("desconhecido");
    }
}