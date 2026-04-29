#include "queries/query6.h"
#include "gestor_entidades/gestor_reservas.h"
#include "gestor_entidades/gestor.h"
#include "io/parsers/parser.h"
#include "io/output/output.h"
#include "utils/string_pool.h"
#include "utils/utils.h"
#include <stdio.h>

char *query6(char **line, Gestor_Reservas g_reservas, char separator, String_Pool sp)
{
    char *nacionalidade = NULL;
    nacionalidade = parse_string(line, '\n');
    if (!nacionalidade)
        return generate_empty_result_string();
    int contador;
    char *result;
    int iata = get_q6(g_reservas, nacionalidade, &contador, sp);
    if (iata == -1)
        result = generate_empty_result_string();
    else
    {
        char *iata_str = int_to_iata(iata);
        void *results[2] = {iata_str, &contador};
        char *format[2] = {"%s", "%d"};
        result = generate_result_string(results, format, 2, separator);
        free(iata_str);
    }
    return result;
}