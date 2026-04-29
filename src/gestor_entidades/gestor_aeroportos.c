#include "gestor_entidades/gestor_aeroportos.h"
#include "entidades/aeroportos.h"
#include <stdlib.h>
#include <glib.h>
#include "utils/utils.h"
#include <stdio.h>

struct gestor_aeroportos
{
    // A chave vai ser o codigo IATA do aeroporoto e o valor é o próprio aeroporto
    GPtrArray *hash_gestor;
    GPtrArray *aeroportos_array;
    int is_sorted; // indica se o array de departure dates de cada aeroporto está ou não ordenado
};

Gestor_Aeroportos initialize_gestor_aeroportos()
{
    int initial_size = 17576; // Tamanho inicial (e teoricamente máximo que existe) para 3 letras (AAA-ZZZ)-> existem no máximo 26^3 = 17576 aeroportos
    Gestor_Aeroportos g = malloc(sizeof(struct gestor_aeroportos));
    GPtrArray *h = g_ptr_array_new_with_free_func(free_aeroporto);
    GPtrArray *array = g_ptr_array_new();
    g_ptr_array_set_size(h, initial_size);
    g->hash_gestor = h;
    g->aeroportos_array = array;
    g->is_sorted = 0;
    return g;
}

void free_gestor_aeroportos(Gestor_Aeroportos gestor)
{
    if (gestor)
    {
        g_ptr_array_free(gestor->aeroportos_array, TRUE);
        g_ptr_array_free(gestor->hash_gestor, TRUE);
        free(gestor);
    }
}

int get_aeroportos_array_size(Gestor_Aeroportos gestor)
{
    return gestor->aeroportos_array->len;
}

int get_aeroportos_is_sorted(Gestor_Aeroportos gestor)
{
    return gestor->is_sorted;
}

Aeroporto get_aeroporto(Gestor_Aeroportos g, char *code)
{
    int code_int = iata_to_int(code);
    if (code_int == -1)
        return NULL;
    Aeroporto a = g_ptr_array_index(g->hash_gestor, code_int);
    return a;
}

Aeroporto get_aeroporto_with_most_departures(Gestor_Aeroportos gestor, int start_date, int end_date, int *num_departures)
{
    int is_sorted = get_aeroportos_is_sorted(gestor);
    int size = get_aeroportos_array_size(gestor);
    Aeroporto biggest = NULL;
    int max_departures = -1;
    for (int i = 0; i < size; i++)
    {
        Aeroporto a = (Aeroporto)g_ptr_array_index(gestor->aeroportos_array, i);
        if (!is_sorted)
        {
            sort_aeroporto_departure_dates(a);
        }
        int num_departures = get_number_of_departures_between_dates(a, start_date, end_date);
        if (num_departures > max_departures)
        {
            max_departures = num_departures;
            biggest = a;
        }
        else if (num_departures == max_departures)
        {
            int max_code = get_aeroporto_code(biggest);
            int a_code = get_aeroporto_code(a);
            if (a_code < max_code)
            {
                biggest = a;
            }
        }
    }
    if (!is_sorted)
        gestor->is_sorted = 1;
    *num_departures = max_departures;
    return biggest;
}

void insert_aeroporto(Gestor_Aeroportos gestor, Aeroporto aeroporto)
{
    int code = get_aeroporto_code(aeroporto);
    g_ptr_array_index(gestor->hash_gestor, code) = aeroporto;
    g_ptr_array_add(gestor->aeroportos_array, aeroporto);
}