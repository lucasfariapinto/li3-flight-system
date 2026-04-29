#include "queries/query5.h"
#include "gestor_entidades/gestor_voos.h"
#include "io/parsers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "io/output/output.h"

char *query5(char **line, Gestor_Voos gv, char separator)
{
    char *N_temp = parse_string(line, ' ');
    if (!N_temp)
        return generate_empty_result_string();
    int N = string_to_int(N_temp);
    if (N <= 0)
        return generate_empty_result_string();
    sort_atraso_companhias(gv);
    char *result = result_top_n(gv, N, separator);
    return result;
}