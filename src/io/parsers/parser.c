#include "io/parsers/parser.h"
#include "entidades/aeroportos.h"
#include "entidades/voos.h"
#include <string.h>
#include <stdlib.h>
#include "utils/utils.h"
#include <sys/types.h> // Para obter ssize_
#include <glib.h>
#include <stdbool.h>
#include "gestor_entidades/gestor.h"
#include "validacoes/validacoes.h"

void parse_dataset(FILE *file, FILE *f_erros, void (*parse_line)(char *, int, FILE *, Gestor_Global, size_t size), int is_used, Gestor_Global g_global)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&line, &len, file);
    if (read == -1)
        return;
    if (line)
        print_error_in_file(f_erros, line);

    while ((read = getline(&line, &len, file)) != -1)
    {
        // Remover \n do fim
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        // Chamar o parser
        parse_line(line, is_used, f_erros, g_global, read);
    }
    free(line);
}

FILE *open_file(char *dataset_path, char *file_name, char *mode, int path_has_file_name)
{
    FILE *file = NULL;
    if (!path_has_file_name)
    {
        char *final_path = create_path(dataset_path, file_name);
        file = fopen(final_path, mode);
        free(final_path);
    }
    else
        file = fopen(dataset_path, mode);

    if (!file)
        return NULL;

    return file;
}

char *get_line(FILE *file, int *acabou)
{
    ssize_t read;
    size_t size = 0;
    char *linha = NULL;
    read = getline(&linha, &size, file);
    if (read != -1)
    {
        if (linha[read - 1] == '\n') // verifica se é a última linha
            linha[read - 1] = '\0';
        else
        {
            linha = realloc(linha, read + sizeof(char)); // na última linha não tem /n
            linha[read] = '\0';
        }
    }
    else
    {
        *acabou = 1;
        free(linha);
        return NULL;
    }
    return linha;
}

char *parse_string(char **ptr, char separator)
{
    if (!ptr || !*ptr)
        return NULL;

    char *start = *ptr;

    if (*start == separator)
        start++;

    char *p = start;
    while (*p && *p != separator)
        p++;

    if (*p == separator)
    {
        *p = '\0';
        p++;
    }

    if (*p == ',')
        p++;

    *ptr = p;
    return start[0] ? start : NULL;
}

void string_to_datetime(char *datahora, int *data, int *hora)
{
    if (data && datahora)
    {
        *data = (datahora[0] - '0') * 10000000 + (datahora[1] - '0') * 1000000 + (datahora[2] - '0') * 100000 + (datahora[3] - '0') * 10000 +
                (datahora[5] - '0') * 1000 + (datahora[6] - '0') * 100 + (datahora[8] - '0') * 10 +
                (datahora[9] - '0');
    }

    if (hora && datahora)
    {

        *hora = (datahora[11] - '0') * 1000 + (datahora[12] - '0') * 100 + (datahora[14] - '0') * 10 + (datahora[15] - '0');
    }
}

int string_to_data(char *date)
{
    int data = (date[0] - '0') * 10000000 + (date[1] - '0') * 1000000 + (date[2] - '0') * 100000 + (date[3] - '0') * 10000 +
               (date[5] - '0') * 1000 + (date[6] - '0') * 100 + (date[8] - '0') * 10 +
               (date[9] - '0');
    return data;
}

void parse_ids_list(char **ptr, char **first, char **second)
{
    char *curr = *ptr;

    curr++; // passa a abertura de aspas

    if (*curr != '[')
    {
        // Lógica manual de parse_string(ptr, '"') + skip comma
        while (*curr && *curr != '"')
        {
            curr++;
        }
        if (*curr == '"')
        {
            *curr = '\0';
            curr++;

            // Verifica e passa a vírgula se existir
            if (*curr == ',')
                curr++;
        }

        *ptr = curr; // Atualiza o ponteiro original
        return;
    }

    curr++; // passa o '['
    int index = 0;

    // é uma lista
    while (*curr && *(curr + 1) != '"')
    {
        if (index >= 2)
        {
            *first = NULL;
            *second = NULL;
            break;
        }

        if (*curr == '\'')
        {
            curr++; // Passa a aspa de abertura

            char *start = curr; // Guarda o início do ID

            // Procura a aspa de fecho '
            while (*curr && *curr != '\'')
            {
                curr++;
            }

            if (*curr == '\'')
            {
                *curr = '\0'; // Termina a string do ID

                if (index == 0)
                    *first = start;
                else
                    *second = start;

                curr++; // Passa a aspa de fecho
                index++;
            }
        }
        else
        {
            curr++; // Avança (ignora espaços, vírgulas, etc.)
        }
    }

    // Verifica se terminou corretamente com ']'
    if (*curr != ']')
    {
        // Avança 3 casas (x","...) e limpa tudo
        curr += 3;
        *first = NULL;
        *second = NULL;
        *ptr = curr;
        return;
    }

    while (*curr && *curr != ',')
    {
        curr++;
    }

    // Substitui a vírgula (ou final) por \0 e avança
    if (*curr == ',')
    {
        *curr = '\0';
        curr++;
    }

    // atualizar
    *ptr = curr;
}

int string_to_int(char *num)
{
    int result = 0;
    int i;
    int is_neg = 0;
    if (num[0] == '-')
    {
        i = 1; // se o primeiro for - e não é um número negativo e só quero contar o número apartir de num[1]
        is_neg = 1;
    }
    else
        i = 0; // é positivo
    for (; num[i]; i++)
    {
        result = result * 10 + num[i] - '0';
    }
    return is_neg ? -result : result;
}

float string_to_float(char *num)
{
    float result = 0.0;
    int i = 0;
    int is_neg = 0;
    if (num[0] == '-')
    {
        i = 1; // se o primeiro for - e não é um número negativo e só quero contar o número apartir de num[1]
        is_neg = 1;
    }
    else
        i = 0; // é positivo

    // Cria a parte inteira
    while (num[i] && num[i] != '.')
    {
        result *= 10;
        result += num[i] - '0';
        i++;
    }
    float decimal = 0.1;

    if (num[i] == '.')
    {
        i++; // salta do '.'
        // Cria a parte fracionária
        for (; num[i]; i++)
        {
            float aux = (num[i] - '0') * decimal;
            result += aux;
            decimal /= 10;
        }
    }
    return is_neg ? -result : result;
}

bool parse_bool(char **ptr)
{
    (*ptr)++; // passa as abertura de aspas
    char *arg = strsep(ptr, "\"");
    if ((*ptr)[0] == ',')
        (*ptr)++;
    if (!arg)
        return false;
    if (strcmp(arg, "TRUE") == 0)
        return true;
    return false;
}

aeroporto_type parse_aeroporto_type(char **ptr)
{
    (*ptr)++; // passa as abertura de aspas
    char *arg = strsep(ptr, "\"");
    if ((*ptr)[0] == ',')
        (*ptr)++;
    if (!arg)
        return SMALL_AIRPORT;

    if (arg[0] == 's')
    {
        if (arg[1] == 'm')
        {
            if (strcmp(arg, "small_airport") == 0)
                return SMALL_AIRPORT;
        }
        else if (arg[1] == 'e')
        {
            if (strcmp(arg, "seaplane_base") == 0)
                return SEAPLANE_BASE;
        }
    }
    else
    {
        switch (arg[0])
        {
        case 'l':
            if (strcmp(arg, "large_airport") == 0)
                return LARGE_AIRPORT;
            break;
        case 'm':
            if (strcmp(arg, "medium_airport") == 0)
                return MEDIUM_AIRPORT;
            break;
        case 'h':
            if (strcmp(arg, "heliport") == 0)
                return HELIPORT;
            break;
        }
    }
    return ERROR_TYPE;
}

voo_status parse_voo_status(char **ptr)
{
    (*ptr)++; // passa as abertura de aspas
    char *arg = strsep(ptr, "\"");
    if ((*ptr)[0] == ',')
        (*ptr)++;
    if (!arg)
        return ON_TIME;

    switch (arg[0])
    {
    case 'O':
        if (strcmp(arg, "On Time") == 0)
            return ON_TIME;
        else
            break;
    case 'D':
        if (strcmp(arg, "Delayed") == 0)
            return DELAYED;
        else
            break;
    case 'C':
        if (strcmp(arg, "Cancelled") == 0)
            return CANCELLED;
        else
            break;
    }
    return ERROR_STATUS;
}

// Passa um argumento do csv à frente sem fazer parse
void skip(char **ptr)
{
    int num_aspas = 3; // Só à terceira aspas é que se encontra o novo argumento
    while (num_aspas != 0)
    {
        if ((*ptr)[0] == '"')
            num_aspas--;
        if (num_aspas != 0)
            (*ptr)++;
    }
}