#include "io/parsers/aeronaves_parser.h"
#include "io/parsers/parser.h"
#include "entidades/aeronaves.h"
#include "gestor_entidades/gestor_aeronaves.h"
#include "validacoes/validacoes_aeronaves.h"
#include "validacoes/validacoes.h"
#include <string.h>
#include <stdlib.h>
#include "utils/utils.h"
#include <sys/types.h>

void aeronave_parse_line(char *line, int is_used, FILE *f_erros_aeronaves, Gestor_Global g_global, size_t line_size)
{
    Gestor_Aeronaves gestor = get_gestor_aeronaves(g_global);
    String_Pool sp = get_string_pool(g_global);
    char unparsed_line[line_size + 1];
    memcpy(unparsed_line, line, line_size + 1);
    char *ptr = line;
    char *aeronave_id = parse_string(&ptr, '"');
    char *aeronave_manufacturer = parse_string(&ptr, '"');
    char *aeronave_model = parse_string(&ptr, '"');
    char *aeronave_year = parse_string(&ptr, '"');
    int is_valid = valida_aeronave(f_erros_aeronaves, unparsed_line, aeronave_year);
    Aeronave aeronave = NULL;
    if (is_valid && is_used)
    {
        aeronave = create_aeronave(aeronave_id, aeronave_manufacturer, aeronave_model, sp);
        insert_aeronave(gestor, aeronave);
    }
}

void aeronaves_parser(char *dataset_path, int is_used, Gestor_Global g_global)
{
    FILE *file = open_file(dataset_path, "/aircrafts.csv", "r", 0);
    FILE *f_erros_aeronaves = open_file("resultados/aircrafts_errors.csv", "", "w", 1);

    if (file == NULL)
    {
        return;
    }

    parse_dataset(file, f_erros_aeronaves, aeronave_parse_line, is_used, g_global);
    fclose(f_erros_aeronaves);
    fclose(file);
}