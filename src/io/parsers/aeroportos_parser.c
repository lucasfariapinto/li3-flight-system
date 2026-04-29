#include "io/parsers/aeroportos_parser.h"
#include "io/parsers/parser.h"
#include "entidades/aeroportos.h"
#include "gestor_entidades/gestor_aeroportos.h"
#include "validacoes/validacoes_aeroportos.h"
#include "validacoes/validacoes.h"
#include <string.h>
#include <stdlib.h>
#include "utils/utils.h"
#include <sys/types.h>
#include <omp.h>

void aeroportos_parser(char *dataset_path, int is_used, Gestor_Global g_global)
{
    FILE *file = open_file(dataset_path, "/airports.csv", "r", 0);
    FILE *f_erros_aeroportos = open_file("resultados/airports_errors.csv", "", "w", 1);

    if (file == NULL)
    {
        return;
    }

    parse_dataset(file, f_erros_aeroportos, aeroporto_parse_line, is_used, g_global);
    fclose(f_erros_aeroportos);
    fclose(file);
}

void aeroporto_parse_line(char *line, int is_used, FILE *f_erros_aeroportos, Gestor_Global g_global, size_t line_size)
{
    Gestor_Aeroportos gestor = get_gestor_aeroportos(g_global);
    char unparsed_line[line_size + 1];
    memcpy(unparsed_line, line, line_size + 1);
    char *ptr = line;
    char *aeroporto_code = parse_string(&ptr, '"');
    char *aeroporto_name = parse_string(&ptr, '"');
    char *aeroporto_city = parse_string(&ptr, '"');
    char *aeroporto_country = parse_string(&ptr, '"');
    char *aeroporto_latitude = parse_string(&ptr, '"');
    char *aeroporto_longitude = parse_string(&ptr, '"');
    // char *aeroporto_icao = parse_string(&ptr, '"');
    skip(&ptr);
    aeroporto_type aeroporto_tipo = parse_aeroporto_type(&ptr);
    Aeroporto aeroporto = NULL;
    int is_valid = valida_aeroporto(f_erros_aeroportos, unparsed_line, aeroporto_code, aeroporto_latitude, aeroporto_longitude, aeroporto_tipo);
    if (is_valid && is_used)
    {
        aeroporto = create_aeroporto(aeroporto_code, aeroporto_name, aeroporto_city, aeroporto_country, aeroporto_tipo, get_string_pool(g_global));
        insert_aeroporto(gestor, aeroporto);
    }
}