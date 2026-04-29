#include "queries/query3.h"
#include "gestor_entidades/gestor_aeroportos.h"
#include "io/parsers/parser.h"
#include "io/output/output.h"
#include "utils/utils.h"
#include <stdio.h>

char *query3(char **line, Gestor_Aeroportos a_gestor, char separator)
{
    char *i_date_temp = parse_string(line, ' ');
    if (!i_date_temp)
        return generate_empty_result_string();
    int i_date = string_to_data(i_date_temp);
    char *f_date_temp = parse_string(line, ' ');
    if (!f_date_temp)
        return generate_empty_result_string();
    int f_date = string_to_data(f_date_temp);

    int num_departures = 0;
    Aeroporto a = get_aeroporto_with_most_departures(a_gestor, i_date, f_date, &num_departures);
    char *result;
    if (num_departures == 0)
        result = generate_empty_result_string();
    else
    {
        char *code = int_to_iata(get_aeroporto_code(a));
        char *name = get_aeroporto_name(a);
        char *city = get_aeroporto_city(a);
        char *country = get_aeroporto_country(a);

        void *results[5] = {code, name, city, country, &num_departures};
        char *format[5] = {"%s", "%s", "%s", "%s", "%d"};
        result = generate_result_string(results, format, 5, separator);
        free(code);
        free(name);
        free(city);
        free(country);
    }
    return result;
}
