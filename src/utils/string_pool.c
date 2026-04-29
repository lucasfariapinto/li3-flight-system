#include "utils/string_pool.h"
#include <glib.h>
#include <stdint.h>

struct string_pool
{
    GHashTable *string_pool;
};

String_Pool initialize_string_pool()
{
    String_Pool sp = malloc(sizeof(struct string_pool));
    sp->string_pool = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);
    return sp;
}

void free_string_pool(String_Pool sp)
{
    if (sp)
    {
        g_hash_table_destroy(sp->string_pool);
        free(sp);
    }
}

const char *insert_string_in_pool(char const *s, String_Pool sp)
{
    char *str = NULL;
    if (g_hash_table_lookup_extended(sp->string_pool, s, (gpointer *)&str, NULL)) // str fica com o ponteiro original da string se ela existir
    {
        return str;
    }
    else
    {
        char *nova_string = strdup(s);
        g_hash_table_add(sp->string_pool, nova_string);
        return nova_string;
    }
}

// Função que altera o valor do ponteiro para evitar de forma a obter-se um número unico para cada valor de entrada de string e sem expor o endereço real da string
uintptr_t pointer_to_num(const char *ptr)
{
    return ((uintptr_t)ptr) ^ 0xABCDEF1234567890ULL; // realiza um XOR (ou exclusivo) de forma a gerar um valor único
}

const char *num_to_const_ptr(uintptr_t obfuscated_id)
{
    uintptr_t original_addr = obfuscated_id ^ 0xABCDEF1234567890ULL; // fazer o XOR de novo para obter o endereço original

    return (const char *)original_addr; // retornamos o ponteiro mas com const char* para não poder ser modificado
}

char *get_string_from_pool(const char *s)
{
    return strdup(s);
}