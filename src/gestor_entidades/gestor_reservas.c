#include "gestor_entidades/gestor_reservas.h"
#include "gestor_entidades/gestor_voos.h"
#include "gestor_entidades/gestor_passageiros.h"
#include "entidades/voos.h"
#include "entidades/reservas.h"
#include <stdlib.h>
#include <glib.h>
#include "utils/utils.h"
#include "gestor_entidades/gestor.h"
#include "io/parsers/parser.h"
#include "stdint.h"

struct gestor_reservas
{
    // A chave é a nacionalidade
    // o valor vai ser uma estrutura de codigo iata com contador
    GHashTable *ids_reservas;
    GHashTable *hash_tree;
    GHashTable *hash_nacionalidades;
};

typedef struct contador_nacionalidade
{
    int iata;
    int contador;
} *Contador_Nacionalidade;

void free_contador_nacionalidade(void *n_temp)
{
    Contador_Nacionalidade n = n_temp;
    free(n);
}

Gestor_Reservas initialize_gestor_reserva()
{
    Gestor_Reservas g = malloc(sizeof(struct gestor_reservas));
    GHashTable *ids = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);
    GHashTable *h = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);
    GHashTable *t = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, free_contador_nacionalidade);
    g->hash_tree = h;
    g->ids_reservas = ids;
    g->hash_nacionalidades = t;

    return g;
}

// Função que liberta a memória alocada para o gestor de reservas
void free_gestor_reservas(Gestor_Reservas gestor)
{
    if (gestor)
    {
        g_hash_table_destroy(gestor->ids_reservas);
        g_hash_table_destroy(gestor->hash_nacionalidades);
        free(gestor);
    }
}

void insert_id_reserva(Gestor_Reservas g_reservas, char *reservation_id)
{
    int id = string_to_int(reservation_id + 1); // Ignorar o 'R' inicial
    g_hash_table_insert(g_reservas->ids_reservas, GINT_TO_POINTER(id), GINT_TO_POINTER(1));
}

int id_reserva_exists(Gestor_Reservas g_reservas, char *reservation_id)
{
    int id = string_to_int(reservation_id + 1); // Ignorar o 'R' inicial
    gpointer result = g_hash_table_lookup(g_reservas->ids_reservas, GINT_TO_POINTER(id));
    return result != NULL;
}

void insert_nacionalidade(Gestor_Reservas g_reservas, const char *nacionalidade, int iata)
{
    // forma-se uma hash table de hash tables. Na mais exterior a chave é uma nacionalidade e na interor a chave é o iata e o valor é o contador
    uintptr_t nacionalidade_val = pointer_to_num(nacionalidade);
    GHashTable *hash = g_hash_table_lookup(g_reservas->hash_tree, GSIZE_TO_POINTER(nacionalidade_val));
    if (!hash) // se ainda não existir a hash table para essa nacionalidade, cria-se uma nova
    {
        hash = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);
        g_hash_table_insert(hash, GINT_TO_POINTER(iata), GINT_TO_POINTER(1)); // insere o iata com contador 1
        g_hash_table_insert(g_reservas->hash_tree, GSIZE_TO_POINTER(nacionalidade_val), hash);
    }
    else // ja exisita uma hash table para aquela nacionalidade
    {
        gpointer current_count = g_hash_table_lookup(hash, GINT_TO_POINTER(iata));
        if (!current_count)
        {
            g_hash_table_insert(hash, GINT_TO_POINTER(iata), GINT_TO_POINTER(1));
        }
        else
        {
            int new_count = GPOINTER_TO_INT(current_count) + 1;
            g_hash_table_replace(hash, GINT_TO_POINTER(iata), GINT_TO_POINTER(new_count));
        }
    }
}

void build_q6(Gestor_Reservas g_reservas)
{
    g_hash_table_foreach(g_reservas->hash_tree, select_max_iata, g_reservas->hash_nacionalidades);
    g_hash_table_destroy(g_reservas->hash_tree);
}

void select_max_iata(gpointer key, gpointer value, gpointer user_data)
{
    GHashTable *hash_table = (GHashTable *)value;
    GHashTable *q6 = user_data;

    Contador_Nacionalidade max = malloc(sizeof(struct contador_nacionalidade));
    max->contador = 0;
    max->iata = 0;

    g_hash_table_foreach(hash_table, get_max_iata, max);
    g_hash_table_insert(q6, key, max);

    g_hash_table_destroy(hash_table);
}

void get_max_iata(gpointer key, gpointer value, gpointer user_data)
{
    int iata = GPOINTER_TO_INT(key);
    int contador = GPOINTER_TO_INT(value);
    Contador_Nacionalidade max = user_data;

    if (contador > max->contador ||
        (contador == max->contador && max->iata && iata < max->iata))
    {
        max->contador = contador;
        max->iata = iata;
    }
}

int get_q6(Gestor_Reservas g, char *nacionalidade, int *contador, String_Pool sp)
{
    uintptr_t nacionalidade_val = pointer_to_num(insert_string_in_pool(nacionalidade, sp));
    Contador_Nacionalidade resultado = g_hash_table_lookup(g->hash_nacionalidades, GSIZE_TO_POINTER(nacionalidade_val));
    if (!resultado)
    {
        *contador = 0;
        return -1;
    }
    *contador = resultado->contador;
    return resultado->iata;
}

int get_nacionalidade(Gestor_Reservas g_reservas, char *nacionalidade, String_Pool sp)
{
    uintptr_t nacionalidade_val = pointer_to_num(insert_string_in_pool(nacionalidade, sp));
    Contador_Nacionalidade resultado = g_hash_table_lookup(g_reservas->hash_nacionalidades, GSIZE_TO_POINTER(nacionalidade_val));
    if (!resultado)
    {
        return -1;
    }
    return resultado->iata;
}