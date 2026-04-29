#include "queries/query4.h"
#include "gestor_entidades/gestor_passageiros.h"
#include "io/parsers/parser.h"
#include "io/output/output.h"
#include "utils/utils.h"
#include <stdio.h>

// NOTAS:
/*
objetivo: passar calcular o top 10 para cada semana apenas o vez e idealmente
sem ter que passar duas vezes pelas reservas
*/

char *query4(char **line, Gestor_Passageiros g_passageiros, char separator)
{
    char *init_date_s = NULL;
    int init_date = 0;
    init_date_s = parse_string(line, ' '); // para avançar o ponteiro até ao fim da linha
    if (init_date_s)
    {
        init_date = string_to_data(init_date_s); // data mais antiga
    }

    char *end_date_s = NULL;
    int end_date = 0;
    end_date_s = parse_string(line, ' '); // para avançar o ponteiro até ao fim da linha
    if (end_date_s)
    {
        end_date = string_to_data(end_date_s); // data mais recente
    }
    int times_in_top_10;
    int doc_number = get_most_times_in_top_10(g_passageiros, init_date == 0 ? NULL : &init_date, end_date == 0 ? NULL : &end_date, &times_in_top_10);

    Passageiro p = get_passageiro(g_passageiros, doc_number);

    char *result;
    if (!p)
    {
        result = generate_empty_result_string();
        return result;
    }
    char *first_name = get_passageiro_first_name(p);
    char *last_name = get_passageiro_last_name(p);
    int dob = get_passageiro_dob(p);
    char *dob_date = convert_date_to_string(dob);
    char *nationality = strdup(get_passageiro_nationality(p));

    void *results[6] = {&doc_number, first_name, last_name, dob_date, nationality, &times_in_top_10};
    char *format[6] = {"%09d", "%s", "%s", "%s", "%s", "%d"};
    result = generate_result_string(results, format, 6, separator);

    free(first_name);
    free(last_name);
    free(dob_date);
    free(nationality);
    return result;
}