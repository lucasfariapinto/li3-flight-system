#include <stdio.h>
#include "gestor_entidades/gestor_aeroportos.h"
#include "gestor_entidades/gestor_voos.h"
#include "gestor_entidades/gestor_aeronaves.h"
#include "gestor_entidades/gestor_passageiros.h"
#include "gestor_entidades/gestor_reservas.h"
#include "gestor_entidades/gestor.h"
#include "io/parsers/aeroportos_parser.h"
#include "io/parsers/voos_parser.h"
#include "io/parsers/aeronaves_parser.h"
#include "io/parsers/passageiros_parser.h"
#include "io/parsers/reservas_parser.h"
#include "io/parsers/parser.h"
#include "queries/query1.h"
#include "queries/query2.h"
#include "queries/query3.h"
#include "queries/interpreter.h"
#include "glib.h"

void programa_principal(char *csv_path, char *queries_path)
{
    Gestor_Global g_global = initialize_gestor_global();
    // Parse e validação das entidades alocando apenas memória para que vão ser usadas nos queries
    aeroportos_parser(csv_path, 1, g_global);

    aeronaves_parser(csv_path, 1, g_global);
    voos_parser(csv_path, 1, g_global);
    passageiros_parser(csv_path, 1, g_global);
    reserva_parser(csv_path, 1, g_global); // Apenas para validação

    // Execução das queries
    interpreter(g_global, queries_path);

    // Libertar memória
    free_gestor_global(g_global);
}

int main(int n, char **args)
{
    switch (n)
    {
    case 3:
        programa_principal(args[1], args[2]);
        break;
    default:
        printf("Comando inválido\n");
        return 1;
    }
    return 0;
}
