#include "io/parsers/reservas_parser.h"
#include "io/parsers/parser.h"
#include "entidades/reservas.h"
#include "gestor_entidades/gestor_reservas.h"
#include "validacoes/validacoes_reservas.h"
#include "validacoes/validacoes.h"
#include <string.h>
#include <stdlib.h>
#include "utils/utils.h"
#include <sys/types.h>
#include "gestor_entidades/gestor_passageiros.h"
#include "gestor_entidades/gestor_voos.h"
#include "utils/string_pool.h"

void reserva_parse_line(char *line, int is_used, FILE *f_erros_reservas, Gestor_Global g_global, size_t line_size)
{
    Gestor_Reservas g_reservas = get_gestor_reservas(g_global);
    Gestor_Passageiros g_passageiros = get_gestor_passageiros(g_global);
    Gestor_Voos g_voos = get_gestor_voos(g_global);

    char unparsed_line[line_size + 1];
    memcpy(unparsed_line, line, line_size + 1);
    char *ptr = line;
    char *reservation_id = parse_string(&ptr, '"');
    char *first = NULL;
    char *second = NULL;
    parse_ids_list(&ptr, &first, &second);
    char *document_number = parse_string(&ptr, '"');
    int is_valid = valida_reserva(f_erros_reservas, unparsed_line, reservation_id, first, second, document_number, g_passageiros, g_voos, g_reservas);
    if (is_valid && is_used)
    {
        insert_id_reserva(g_reservas, reservation_id);
        // char *seat = parse_string(&ptr, '"');
        skip(&ptr);
        float price = string_to_float(parse_string(&ptr, '"'));
        int doc_number = string_to_int(document_number);
        Voo voo1 = get_voo(g_voos, first);
        voo_status status = get_voo_status(voo1);
        Passageiro p = get_passageiro(g_passageiros, doc_number);
        const char *nacionalidade = get_passageiro_nationality(p);

        insert_week_expense(g_passageiros, get_voo_departure_date(voo1), doc_number, price);
        if (status != CANCELLED)
        {
            int iata1 = get_aeroporto_code(get_voo_destination(voo1));
            incrementa_aeroporto_passageiros_partem(get_voo_origin(voo1));
            incrementa_aeroporto_passageiros_aterram(get_voo_destination(voo1));
            insert_nacionalidade(g_reservas, nacionalidade, iata1);
        }
        if (second)
        {
            Voo voo2 = get_voo(g_voos, second);
            if (get_voo_status(voo2) != CANCELLED)
            {
                int iata2 = get_aeroporto_code(get_voo_destination(voo2));
                incrementa_aeroporto_passageiros_partem(get_voo_origin(voo2));
                incrementa_aeroporto_passageiros_aterram(get_voo_destination(voo2));
                insert_nacionalidade(g_reservas, nacionalidade, iata2);
            }
        }
    }
}

void reserva_parser(char *dataset_path, int is_used, Gestor_Global g_global)
{
    Gestor_Passageiros g_passageiros = get_gestor_passageiros(g_global);
    Gestor_Reservas g_reservas = get_gestor_reservas(g_global);
    FILE *file = open_file(dataset_path, "/reservations.csv", "r", 0);
    FILE *f_erros_reservas = open_file("resultados/reservations_errors.csv", "", "w", 1);

    if (file == NULL)
    {
        return;
    }

    parse_dataset(file, f_erros_reservas, reserva_parse_line, is_used, g_global);
    build_q6(g_reservas);
    build_top_10_by_week(g_passageiros);
    fclose(f_erros_reservas);
    fclose(file);
}
