#include "gestor_entidades/gestor_passageiros.h"
#include "entidades/passageiros.h"
#include <stdlib.h>
#include <glib.h>
#include "utils/utils.h"

struct gestor_passageiros
{
    // A chave é o número do documento
    // O valor é uma estrutura passageiro
    GHashTable *hash_gestor;
    GPtrArray *week_expenses; // chave: semana do ano (int), valor: total de despesas (convertido para int) dos passageiros nessa semana
    int **top10_by_week;
    int biggest_week;
};

Gestor_Passageiros initialize_gestor_passageiros()
{
    Gestor_Passageiros g = malloc(sizeof(struct gestor_passageiros));
    GHashTable *h = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, free_passageiro);
    GPtrArray *week_expenses = g_ptr_array_new();
    int **top10_by_week = NULL;
    g->biggest_week = 0;
    g->top10_by_week = top10_by_week;
    g->week_expenses = week_expenses;
    g->hash_gestor = h;
    return g;
}

void free_gestor_passageiros(Gestor_Passageiros gestor)
{
    if (gestor)
    {
        g_hash_table_destroy(gestor->hash_gestor);
        if (gestor->week_expenses)
        {
            g_ptr_array_free(gestor->week_expenses, TRUE);
        }
        if (gestor->top10_by_week)
        {
            for (int i = 0; i <= gestor->biggest_week; i++)
            {
                free(gestor->top10_by_week[i]);
            }
            free(gestor->top10_by_week);
        }
        free(gestor);
    }
}

void insert_passageiro(Gestor_Passageiros gestor, int document_number, Passageiro p)
{
    g_hash_table_insert(gestor->hash_gestor, GINT_TO_POINTER(document_number), p);
}

Passageiro get_passageiro(Gestor_Passageiros g, int code)
{
    gpointer temp = g_hash_table_lookup(g->hash_gestor, GINT_TO_POINTER(code));
    Passageiro a = temp;
    return a;
}

int passageiro_exists(Gestor_Passageiros g, int code)
{
    if (!g)
        return 0;
    return g_hash_table_contains(g->hash_gestor, GINT_TO_POINTER(code));
}

// insere um expense(price) para um determinada data/semana.
// ve se essa semana senão cria-a (uma nova hashtable)
// se já exisitir ent insere o nessa hash table
// no final de todas as reservas ficamos com a informação necessária para a query4
void insert_week_expense(Gestor_Passageiros gestor, int date, int document_number, float price)
{
    int week_num = date_to_week(date);

    if (week_num > gestor->biggest_week)
    {
        gestor->biggest_week = week_num; // Atualiza a maior semana que aparecer;
    }
    int size = gestor->week_expenses->len;
    int price_int = (int)(price * 100); // multiplica-se por 100 para depois se poder converter para inteiro sem eliminar precisão
    if (week_num >= size)
        g_ptr_array_set_size(gestor->week_expenses, week_num * 2);
    GHashTable *week = g_ptr_array_index(gestor->week_expenses, week_num);
    if (week == NULL)
    {
        week = g_hash_table_new(g_direct_hash, g_direct_equal);
        g_ptr_array_index(gestor->week_expenses, week_num) = week;
        g_hash_table_insert(week, GINT_TO_POINTER(document_number), GINT_TO_POINTER(price_int));
    }
    else
    {
        gpointer temp = g_hash_table_lookup(week, GINT_TO_POINTER(document_number));
        int expense = temp == NULL ? 0 : GPOINTER_TO_INT(temp);
        price_int += expense;
        g_hash_table_insert(week, GINT_TO_POINTER(document_number), GINT_TO_POINTER(price_int));
    }
}

typedef struct despesa_pessoa
{
    int document_number;
    int expense;
} *DespesaPessoa;

// função usada para o g_sequence para comparar entre duas despesas
gint compare_despesa_pessoa(gconstpointer a, gconstpointer b, gpointer user_data)
{
    (void)user_data;
    const DespesaPessoa a1 = (const DespesaPessoa)a;
    const DespesaPessoa b1 = (const DespesaPessoa)b;
    if (a1->expense != b1->expense)
        return b1->expense - a1->expense;
    else
        return a1->document_number - b1->document_number;
}

// função criada para usar no g_hash_table_foreach e ela o que faz é cada iteração de um par key, value da hash table cujo o varrimento tem o objetivo de encontrar o top 10 para aquela semana
void select_top_10(gpointer key, gpointer value, gpointer user_data)
{
    int max_length = 10;
    int k = GPOINTER_TO_INT(key);
    int v = GPOINTER_TO_INT(value);
    GSequence *top_10 = user_data;
    if (g_sequence_get_length(top_10) < max_length) // se ainda não tiver 10 elemento
    {
        DespesaPessoa new = malloc(sizeof(struct despesa_pessoa));
        new->document_number = k;
        new->expense = v;
        g_sequence_insert_sorted(top_10, new, compare_despesa_pessoa, NULL);
    }
    else
    {
        GSequenceIter *g = g_sequence_get_iter_at_pos(top_10, max_length - 1);
        DespesaPessoa d = g_sequence_get(g);
        if (d->expense < v)
        {
            g_sequence_remove(g);
            DespesaPessoa new = malloc(sizeof(struct despesa_pessoa));
            new->document_number = k;
            new->expense = v;
            g_sequence_insert_sorted(top_10, new, compare_despesa_pessoa, NULL);
        }
    }
}

// função que no fim de percorrer as reservas todas cria para cada semana o teu top 10,
// o resultado é guardado como um array de arrays de document_number(inteiros)
// usamos g_sequence para obter o top10
void build_top_10_by_week(Gestor_Passageiros g_passageiros)
{
    int num_of_top = 10;
    int biggest_week = g_passageiros->biggest_week;
    int **result = malloc(sizeof(int *) * (biggest_week + 1));
    for (int i = 0; i <= biggest_week; i++)
    {
        GHashTable *week = g_ptr_array_index(g_passageiros->week_expenses, i);
        if (week != NULL)
        {
            // em cada iteração pegamos na hash table daquela semana e selecionamos o top 10 para o array top que depois é inserido no top_10_by_week
            int *top = malloc(sizeof(int) * num_of_top);
            memset(top, -1, 10 * sizeof(int)); // inicializa a -1 para o caso de por exemplo haver uma semana que não tem 10 passageiros com voos saber que se acaba
            GSequence *top_10 = g_sequence_new(free);
            g_hash_table_foreach(week, select_top_10, top_10);
            g_ptr_array_index(g_passageiros->week_expenses, i) = NULL; // Meter a null antes de destruir
            g_hash_table_destroy(week);                                // destro-o a hash table pois não é mais necessária
            GSequenceIter *iter = g_sequence_get_begin_iter(top_10);
            for (int j = 0; j < num_of_top && !g_sequence_iter_is_end(iter); j++)
            {
                DespesaPessoa pessoa = g_sequence_get(iter);
                top[j] = pessoa->document_number;
                iter = g_sequence_iter_next(iter);
            }
            result[i] = top;
            g_sequence_free(top_10);
        }
        else
            result[i] = NULL;
    }

    g_ptr_array_free(g_passageiros->week_expenses, TRUE);
    g_passageiros->week_expenses = NULL;
    g_passageiros->top10_by_week = result;
}

// Função que recebe a lista de lista de document_numbers e ve aquele que se mais se repete entre duas datas
int get_most_times_in_top_10(Gestor_Passageiros g_passageiros, int *init_date, int *end_date, int *times_in_top_10)
{
    int **top_10_by_week = g_passageiros->top10_by_week;
    GHashTable *result = g_hash_table_new(g_direct_hash, g_direct_equal);
    int biggest_week = g_passageiros->biggest_week;
    int maior = init_date ? date_to_week(*init_date) : biggest_week; // mais antiga
    int menor = end_date ? date_to_week(*end_date) : 0;              // mais recente
    int most_times = 0;                                              // vai guardando o número máximo de vezes que um passageiro apareceu no top 10
    int doc_number_most_times = -1;                                  // vai guardando o document number do passageiro que mais vezes apareceu no top 10
    for (int i = menor; i <= biggest_week && i <= maior; i++)
    {
        if (top_10_by_week[i] != NULL)
        {
            for (int j = 0; j < 10; ++j)
            {
                int doc_number = top_10_by_week[i][j];
                if (doc_number != -1)
                {
                    gpointer n = g_hash_table_lookup(result, GINT_TO_POINTER(doc_number));
                    int num = n ? GPOINTER_TO_INT(n) : 0;
                    if (num + 1 > most_times || (num + 1 == most_times && doc_number < doc_number_most_times))
                    {
                        most_times = num + 1;
                        doc_number_most_times = doc_number;
                    }
                    g_hash_table_insert(result, GINT_TO_POINTER(doc_number), GINT_TO_POINTER(num + 1));
                }
                else
                    break;
            }
        }
    }
    *times_in_top_10 = most_times;
    g_hash_table_destroy(result);
    return doc_number_most_times;
}