#include "queries/query2.h"
#include "gestor_entidades/gestor_aeronaves.h"
#include "io/parsers/parser.h"
#include <stdio.h>
#include "io/output/output.h"

char *query2(char **line, Gestor_Aeronaves a_gestor, char separator)
{
    sort_aeronaves_by_num_flights(a_gestor); // Permite nos ordenar apenas uma vez o array de aeronaves e nenhuma vez no caso do query não ser chamado

    char *n2 = parse_string(line, ' ');
    if (!n2)
        return generate_empty_result_string();
    int n = string_to_int(n2);
    char *manufacturer = NULL;

    manufacturer = parse_string(line, ' '); // para avançar o ponteiro até ao fim da linha

    char **airplanes = malloc(n * sizeof(char *));
    int count = 0;
    get_n_mais_voos(a_gestor, n, manufacturer, airplanes, &count);

    char *result;

    if (count == 0)
        result = generate_empty_result_string();
    else
    {
        char *buffer = malloc(1);
        buffer[0] = '\0';
        for (int i = 0; i < count; i++)
        {
            Aeronave a = get_aeronave(a_gestor, airplanes[i]);
            char *aeronave_manufacturer = get_aeronave_manufacturer(a);
            char *aeronave_model = get_aeronave_model(a);
            int num_flights = get_aeronave_num_flights(a);

            void *results[4] = {airplanes[i], aeronave_manufacturer, aeronave_model, &num_flights};
            char *format[4] = {"%s", "%s", "%s", "%d"};
            char *current_line = generate_result_string(results, format, 4, separator);

            int old_len = strlen(buffer);
            int line_len = strlen(current_line);
            int new_size = old_len + line_len + 1;

            char *new_buffer = malloc(new_size);
            strcpy(new_buffer, buffer);
            strcat(new_buffer, current_line);

            free(buffer);
            free(current_line);
            buffer = new_buffer;
            free(aeronave_manufacturer);
            free(aeronave_model);
            free(airplanes[i]);
        }
        result = buffer;
    }
    free(airplanes);
    return result;
}