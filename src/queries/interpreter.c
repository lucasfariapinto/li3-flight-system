#include "queries/interpreter.h"
#include "gestor_entidades/gestor_aeroportos.h"
#include "gestor_entidades/gestor_voos.h"
#include "gestor_entidades/gestor_aeronaves.h"
#include "gestor_entidades/gestor.h"
#include "queries/query1.h"
#include "queries/query2.h"
#include "queries/query3.h"
#include "queries/query4.h"
#include "queries/query5.h"
#include "queries/query6.h"
#include "io/parsers/parser.h"
#include <stdio.h>
#include "time.h"
#include "io/output/output.h"
#include "utils/string_pool.h"

void interpreter(Gestor_Global g_global, char *queries_path)
{
    Gestor_Aeroportos a_gestor = get_gestor_aeroportos(g_global);
    Gestor_Aeronaves aero_gestor = get_gestor_aeronaves(g_global);
    Gestor_Passageiros g_passageiros = get_gestor_passageiros(g_global);
    Gestor_Voos g_voos = get_gestor_voos(g_global);
    Gestor_Reservas g_reservas = get_gestor_reservas(g_global);
    String_Pool sp = get_string_pool(g_global);
    FILE *queries_file = open_file(queries_path, "", "r", 1);
    printf("\nExecuting queries...\n");
    if (queries_file == NULL)
    {
        printf("Erro ao abrir o ficheiro de queries\n");
        return;
    }
    int acabou = 0;
    int command_number = 1;
    while (!acabou)
    {
        char *line = get_line(queries_file, &acabou);
        if (line)
        {
            char *l = parse_string(&line, ' '); // avança o ponteiro para depois do '1 ' para ficar apenas com o argumento da query
            char file_path[50];
            sprintf(file_path, "resultados/command%d_output.txt", command_number); // permite formartar o caminho do ficheiro ja com o número correto
            char separator = ';';
            if (l[1] == 'S')
                separator = '=';
            FILE *file = open_file(file_path, "", "w", 1);
            char *result = NULL;
            if (file)
            {
                switch (l[0])
                {
                case '1':
                    result = query1(&line, a_gestor, separator);
                    break;
                case '2':
                    result = query2(&line, aero_gestor, separator);
                    break;
                case '3':
                    result = query3(&line, a_gestor, separator);
                    break;
                case '4':
                    result = query4(&line, g_passageiros, separator);
                    break;
                case '5':
                    result = query5(&line, g_voos, separator);
                    break;
                case '6':
                    result = query6(&line, g_reservas, separator, sp);
                    break;
                default:
                    printf("Query inválida\n");
                }
                print_string_to_file(file, result);
                free(result);
                fclose(file);
            }
            else
                printf("Erro ao criar o ficheiro de output da query %d\n", command_number);
            free(l);
            command_number++;
        }
    }
    printf("Finished executing queries.\n");
    fclose(queries_file);
}