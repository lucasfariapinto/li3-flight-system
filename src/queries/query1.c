#include "queries/query1.h"
#include "gestor_entidades/gestor_aeroportos.h"
#include "entidades/aeroportos.h"
#include "io/parsers/parser.h"
#include "io/output/output.h"
#include "utils/utils.h"
#include <string.h>

char *query1(char **line, Gestor_Aeroportos a_gestor, char separator)
{
    char *code = parse_string(line, ' ');
    char *result;
    Aeroporto aeroporto = get_aeroporto(a_gestor, code);
    if (aeroporto)
    {
        char *code = int_to_iata(get_aeroporto_code(aeroporto));
        char *name = get_aeroporto_name(aeroporto);
        char *city = get_aeroporto_city(aeroporto);
        char *country = get_aeroporto_country(aeroporto);
        char *type = aeroporto_type_to_string(get_aeroporto_type(aeroporto));
        int passageiros_aterram = get_aeroporto_passageiros_aterram(aeroporto);
        int passageiros_partem = get_aeroporto_passageiros_partem(aeroporto);
        void *results[7] = {code, name, city, country, type, &passageiros_aterram, &passageiros_partem};
        char *format[7] = {"%s", "%s", "%s", "%s", "%s", "%d", "%d"};
        result = generate_result_string(results, format, 7, separator);
        free(code);
        free(name);
        free(city);
        free(country);
        free(type);
    }
    else
        result = generate_empty_result_string();
    return result;
}
