#include "gestor_entidades/gestor_aeronaves.h"
#include "entidades/aeronaves.h"
#include <stdlib.h>
#include <glib.h>
#include "utils/utils.h"
#include <stdio.h>

struct gestor_aeronaves
{
    // A chave vai ser o identifier da aeronave e o valor é a própria aeronave
    GHashTable *hash_gestor;
    GPtrArray *aeronaves_array; // array para facilitar a iteração sobre as aeronaves e permitir ordenação por número de voos (query 2)
    // O objetivo é que os elementos deste array estejam apenas a apontar para as aeronaves que estão na hash table evitando duplicação de dados e poupando memória
    int is_sorted;
};

Gestor_Aeronaves initialize_gestor_aeronaves()
{
    Gestor_Aeronaves g = malloc(sizeof(struct gestor_aeronaves));
    GHashTable *h = g_hash_table_new_full(g_str_hash, g_str_equal, free, free_aeronave);
    GPtrArray *array = g_ptr_array_new();
    g->is_sorted = 0;
    g->aeronaves_array = array;
    g->hash_gestor = h;
    return g;
}

void free_gestor_aeronaves(Gestor_Aeronaves gestor)
{
    if (gestor)
    {
        g_ptr_array_free(gestor->aeronaves_array, TRUE);
        g_hash_table_destroy(gestor->hash_gestor); // A estrutura Aeronave só é libertada aqui
        free(gestor);
    }
}

void insert_aeronave(Gestor_Aeronaves gestor, Aeronave aeronave)
{
    g_hash_table_insert(gestor->hash_gestor, get_aeronave_identifier(aeronave), aeronave); // A hash table fica com uma cópia da key com endereço diferente daquele que está no própria estrutura aeronave (por isso é preciso libertar separadamante as keys)
    g_ptr_array_add(gestor->aeronaves_array, aeronave);
}

int compare_aeronaves_by_num_flights(gconstpointer a, gconstpointer b) // compara primeiro pelo número de voos e em caso de empate pelo id em ordem alfabética
{
    Aeronave aeronave_a = *(const Aeronave *)a; // porque o g_ptr_array_sort passa ponteiros para os elementos do array que ja são ponteiros
    Aeronave aeronave_b = *(const Aeronave *)b;

    int num_flights_a = get_aeronave_num_flights(aeronave_a);
    int num_flights_b = get_aeronave_num_flights(aeronave_b);
    int result;
    if (num_flights_a < num_flights_b)
        result = 1; // Queremos ordem decrescente
    else if (num_flights_a > num_flights_b)
        result = -1;
    else
    {
        char *id_a = get_aeronave_identifier(aeronave_a);
        char *id_b = get_aeronave_identifier(aeronave_b);
        result = strcmp(id_a, id_b);
        free(id_a);
        free(id_b);
    }
    return result;
}

void sort_aeronaves_by_num_flights(Gestor_Aeronaves gestor) // O objetivo é depois do primeiro query 2, manter este array ordenado para evitar ordenações desnecessárias e depois apenas precisamos de percorrer o array para obter as n aeronaves com mais voos
{
    if (gestor->is_sorted)
        return;
    g_ptr_array_sort(gestor->aeronaves_array, compare_aeronaves_by_num_flights);
    gestor->is_sorted = 1;
}

void get_n_mais_voos(Gestor_Aeronaves a_gestor, int n, char *manufacturer, char **airplanes, int *count)
{
    int size = a_gestor->aeronaves_array->len;
    for (int i = 0; i < size && *count < n; i++)
    {
        Aeronave aeronave = g_ptr_array_index(a_gestor->aeronaves_array, i);
        char *aer_manufacturer = get_aeronave_manufacturer(aeronave);
        if (manufacturer == NULL || (manufacturer != NULL && strcmp(manufacturer, aer_manufacturer) == 0))
        {
            airplanes[*count] = get_aeronave_identifier(aeronave);
            (*count)++;
        }
        free(aer_manufacturer);
    }
}

Aeronave get_aeronave(Gestor_Aeronaves g, char *code)
{
    gpointer temp = g_hash_table_lookup(g->hash_gestor, code);
    Aeronave a = temp;
    return a;
}