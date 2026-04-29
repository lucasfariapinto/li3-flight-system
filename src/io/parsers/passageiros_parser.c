#include "io/parsers/passageiros_parser.h"
#include "io/parsers/parser.h"
#include "entidades/passageiros.h"
#include "gestor_entidades/gestor_passageiros.h"
#include "validacoes/validacoes_passageiros.h"
#include "validacoes/validacoes.h"
#include "utils/utils.h"
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

void passageiros_parser(char *dataset_path, int is_used, Gestor_Global g_global)
{
    FILE *file = open_file(dataset_path, "/passengers.csv", "r", 0);
    FILE *f_erros_passageiros = open_file("resultados/passengers_errors.csv", "", "w", 1);

    if (file == NULL)
    {
        return;
    }

    parse_dataset(file, f_erros_passageiros, passageiro_parse_line, is_used, g_global);
    fclose(f_erros_passageiros);
    fclose(file);
}

void passageiro_parse_line(char *line, int is_used, FILE *f_erros_aeronaves, Gestor_Global g_global, size_t line_size)
{
    Gestor_Passageiros gestor = get_gestor_passageiros(g_global);

    char unparsed_line[line_size + 1];
    memcpy(unparsed_line, line, line_size + 1);
    char *ptr = line;
    char *document_number = parse_string(&ptr, '"');
    char *first_name = parse_string(&ptr, '"');
    char *last_name = parse_string(&ptr, '"');
    char *dob = parse_string(&ptr, '"');
    char *nationality = parse_string(&ptr, '"');
    char *gender = parse_string(&ptr, '"');
    char *email = parse_string(&ptr, '"');
    int is_valid = valida_passageiro(f_erros_aeronaves, unparsed_line, document_number, dob, gender, email);

    if (is_valid && is_used)
    {
        int dob_int = string_to_data(dob);
        int doc_number = string_to_int(document_number);
        Passageiro p = create_passageiro(first_name, last_name, dob_int, nationality, get_string_pool(g_global));
        insert_passageiro(gestor, doc_number, p);
    }
}
