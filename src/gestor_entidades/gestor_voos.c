#include "gestor_entidades/gestor_voos.h"
#include "entidades/voos.h"
#include "utils/utils.h"
#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include "io/output/output.h"
#include "gestor_entidades/gestor.h"
#include "utils/utils.h"
#include <stdint.h>

struct gestor_voos
{
    GHashTable *hash_gestor;
    GHashTable *atraso_companhia;
    GPtrArray *atraso_companhia_order;
    int num_companhias;
    int is_sorted;
};

Voo get_voo(Gestor_Voos g, char *code);

typedef struct airline_stats
{
    float total_delay_minutes;
    int delayed_flights_count;
} *AirlineStats;

struct airline_result
{
    const char *airline;
    int delayed_flights_count;
    float average_delay_minutes;
};

Gestor_Voos initialize_gestor_voos()
{
    Gestor_Voos v = malloc(sizeof(struct gestor_voos));
    v->atraso_companhia = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);
    v->hash_gestor = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, free_voo);
    v->atraso_companhia_order = NULL;
    v->num_companhias = 0;
    v->is_sorted = 0;
    return v;
}

void free_gestor_voos(Gestor_Voos gestor)
{
    if (gestor)
    {
        g_hash_table_destroy(gestor->hash_gestor);
        g_ptr_array_free(gestor->atraso_companhia_order, TRUE);
        free(gestor);
    }
}

void insert_voo(Gestor_Voos gv, Voo voo, char *voo_id)
{
    g_hash_table_insert(gv->hash_gestor, GINT_TO_POINTER(flight_id_to_int(voo_id)), voo);
}

Voo get_voo(Gestor_Voos g, char *code)
{
    return (Voo)g_hash_table_lookup(g->hash_gestor, GINT_TO_POINTER(flight_id_to_int(code)));
}

//  QUERY 5

void insert_airline(Gestor_Voos g_voos, char *airline, float delay_minutes, String_Pool sp)
{
    GHashTable *companhias = g_voos->atraso_companhia;
    uintptr_t airline_ptr = pointer_to_num(insert_string_in_pool(airline, sp));
    gpointer key = GSIZE_TO_POINTER(airline_ptr);
    AirlineStats stats = g_hash_table_lookup(companhias, key);
    if (!stats)
    {
        AirlineStats new_stats = malloc(sizeof(struct airline_stats));
        new_stats->delayed_flights_count = 1;
        new_stats->total_delay_minutes = delay_minutes;
        g_hash_table_insert(companhias, key, new_stats);
        g_voos->num_companhias++;
    }
    else
    {
        stats->delayed_flights_count += 1;
        stats->total_delay_minutes += delay_minutes;
    }
}

void free_AirlineResult(void *a)
{
    AirlineResult a1 = (AirlineResult)a;
    free(a1);
}

struct BuildContext
{
    GPtrArray *atraso_companhia_order;
    int index;
};

void build_q5(gpointer key, gpointer value, gpointer user_data)
{
    struct BuildContext *result = (struct BuildContext *)user_data;
    AirlineStats stats = (AirlineStats)value;
    AirlineResult ar = malloc(sizeof(struct airline_result));
    ar->airline = num_to_const_ptr(GPOINTER_TO_SIZE(key));
    ar->delayed_flights_count = stats->delayed_flights_count;
    ar->average_delay_minutes = (int)(((stats->total_delay_minutes * 1000) / stats->delayed_flights_count) + 0.5); // +0.5 para arredondar
    g_ptr_array_index(result->atraso_companhia_order, result->index) = ar;
    result->index++;
    free(stats);
}

void build_most_delayed(Gestor_Voos g_voos)
{
    GHashTable *companhias = g_voos->atraso_companhia;
    GPtrArray *atraso_companhia_order = g_ptr_array_new_with_free_func(free_AirlineResult);
    struct BuildContext context = {atraso_companhia_order, 0};
    g_ptr_array_set_size(atraso_companhia_order, g_voos->num_companhias);
    g_hash_table_foreach(companhias, build_q5, &context);
    g_voos->atraso_companhia_order = atraso_companhia_order;
    g_hash_table_destroy(companhias);
}

gint compare_airlines_result(gconstpointer a, gconstpointer b)
{
    const AirlineResult aa = *(AirlineResult *)a;
    const AirlineResult bb = *(AirlineResult *)b;

    int avg_a = aa->average_delay_minutes;
    int avg_b = bb->average_delay_minutes;

    if (avg_a > avg_b)
        return -1;
    if (avg_a < avg_b)
        return 1;
    return strcmp(aa->airline, bb->airline);
}

void sort_atraso_companhias(Gestor_Voos g_voos)
{
    if (g_voos->is_sorted == 0)
    {

        g_ptr_array_sort(g_voos->atraso_companhia_order, compare_airlines_result);
        g_voos->is_sorted = 1;
    }
}

char *result_top_n(Gestor_Voos g_voos, int n, char separator)
{
    int i = 0;
    char *result;
    char *buffer = malloc(1);
    buffer[0] = '\0';
    while (i < n && i < (int)g_voos->atraso_companhia_order->len)
    {
        AirlineResult r = g_ptr_array_index(g_voos->atraso_companhia_order, i);
        int delayed_flights_count = r->delayed_flights_count;
        double average_delay = (double)r->average_delay_minutes / 1000.0;
        char *airline = get_string_from_pool(r->airline);
        void *results[3] = {airline, &delayed_flights_count, &average_delay};
        char *format[3] = {"%s", "%d", "%.3f"};
        char *current_line = generate_result_string(results, format, 3, separator);

        int old_len = strlen(buffer);
        int line_len = strlen(current_line);
        int new_size = old_len + line_len + 1;

        char *new_buffer = malloc(new_size);
        strcpy(new_buffer, buffer);
        strcat(new_buffer, current_line);
        free(airline);
        free(buffer);
        free(current_line);
        buffer = new_buffer;
        i++;
    }
    if (i == 0)
    {
        free(buffer);
        result = generate_empty_result_string();
    }
    else
        result = buffer;
    return result;
}