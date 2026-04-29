#include "io/parsers/voos_parser.h"
#include "io/parsers/parser.h"
#include "entidades/voos.h"
#include "gestor_entidades/gestor_voos.h"
#include "gestor_entidades/gestor_aeronaves.h"
#include "gestor_entidades/gestor_aeroportos.h"
#include "entidades/aeronaves.h"
#include "validacoes/validacoes_voos.h"
#include "validacoes/validacoes.h"
#include <string.h>
#include <stdlib.h>
#include "utils/utils.h"
#include <sys/types.h>

void voos_parser(char *dataset_path, int is_used, Gestor_Global g_global)
{
    Gestor_Voos g_voos = get_gestor_voos(g_global);
    FILE *file = open_file(dataset_path, "/flights.csv", "r", 0);
    FILE *f_erros_voos = open_file("resultados/flights_errors.csv", "", "w", 1);

    if (file == NULL)
    {
        return;
    }

    parse_dataset(file, f_erros_voos, voo_parse_line, is_used, g_global);
    build_most_delayed(g_voos);
    fclose(f_erros_voos);
    fclose(file);
}

void voo_parse_line(char *line, int is_used, FILE *f_erros_voos, Gestor_Global g_global, size_t line_size)
{
    Gestor_Voos g_voos = get_gestor_voos(g_global);
    Gestor_Aeronaves g_aeronaves = get_gestor_aeronaves(g_global);
    Gestor_Aeroportos g_aeroportos = get_gestor_aeroportos(g_global);
    char unparsed_line[line_size + 1];
    memcpy(unparsed_line, line, line_size + 1);
    char *ptr = line;
    char *voo_id = parse_string(&ptr, '"');
    char *voo_departure = parse_string(&ptr, '"');
    char *voo_actual_departure = parse_string(&ptr, '"');
    char *voo_arrival = parse_string(&ptr, '"');
    char *voo_actual_arrival = parse_string(&ptr, '"');
    skip(&ptr);
    voo_status voo_estado = parse_voo_status(&ptr);
    char *voo_origin = parse_string(&ptr, '"');
    char *voo_destination = parse_string(&ptr, '"');
    char *voo_aircraft = parse_string(&ptr, '"');
    char *voo_airline = parse_string(&ptr, '"');

    int is_valid = valida_voo(f_erros_voos, unparsed_line, voo_id, voo_departure,
                              voo_actual_departure, voo_arrival, voo_actual_arrival,
                              voo_estado, voo_origin, voo_destination, voo_aircraft,
                              g_aeronaves, g_aeroportos);

    if (is_used && is_valid)
    {
        int departure_date = 0, departure_hour = 0;
        int actual_departure_date = 0, actual_departure_hour = 0;
        string_to_datetime(voo_actual_departure, &actual_departure_date, &actual_departure_hour);
        string_to_datetime(voo_departure, &departure_date, &departure_hour);
        Voo voo = create_voo(voo_estado, voo_origin, voo_destination, departure_date, g_aeroportos);

        if (voo_estado != CANCELLED)
        {
            Aeronave a = get_aeronave(g_aeronaves, voo_aircraft);
            if (a != NULL)
            {
                int num_flights = get_aeronave_num_flights(a);
                set_aeronave_num_flights(a, num_flights + 1);
            }

            Aeroporto aeroporto = get_voo_origin(voo);
            if (aeroporto != NULL)
            {
                insert_aeroporto_departure_date(aeroporto, actual_departure_date);
            }

            if (voo_estado == DELAYED)
            {
                float delay = datetime_diff_minutes(actual_departure_date, actual_departure_hour, departure_date, departure_hour);
                insert_airline(g_voos, voo_airline, delay, get_string_pool(g_global));
            }
        }
        insert_voo(g_voos, voo, voo_id);
    }
}