#include "validacoes/validacoes_voos.h"
#include "validacoes/validacoes.h"
#include <stdio.h>
#include "entidades/voos.h"
#include "gestor_entidades/gestor_aeronaves.h"
#include "gestor_entidades/gestor_aeroportos.h"

int valida_voo(FILE *f_erros_voos, char *line, char *voo_id, char *voo_departure, char *voo_actual_departure, char *voo_arrival, char *voo_actual_arrival, voo_status voo_estado, char *voo_origin, char *destination, char *voo_aircraft, Gestor_Aeronaves g_aeronaves, Gestor_Aeroportos g_aeroportos)
{
    if (verifica_flight_id(voo_id) &&
        verifica_datahora(voo_departure) &&
        verifica_datahora(voo_arrival) &&
        // Validações apenas para os voos que não estão CANCELLED
        ((voo_estado != CANCELLED && verifica_datahora(voo_actual_departure) &&
          verifica_datahora(voo_actual_arrival) &&
          valida_logica_voo_atrasado(voo_estado, voo_departure, voo_arrival, voo_actual_departure, voo_actual_arrival) &&
          compare_datas(voo_departure, voo_arrival) <= 0 &&
          compare_datas(voo_actual_departure, voo_actual_arrival) <= 0) ||
         // Para os que estão concelados
         valida_logica_voo_cancelado(voo_estado, voo_actual_departure, voo_actual_arrival)) &&
        valida_aeroportos_ids(voo_origin, destination, g_aeroportos) &&
        valida_aircraft_id(voo_aircraft, g_aeronaves) &&
        valida_logica_voo_dest(voo_origin, destination))
        return 1;
    else
    {
        print_error_in_file(f_erros_voos, line);
        return 0;
    }
}

// Validação lógica do voo

/*
1 -o destino do voo tem de ser diferente da origem -
2-o arrival e actual arrival tem de ser posterior ao departure e actual departure respetivamente -
3-o aircraft_id tem de existir -
4-Se um voo for cancelato o actual departure e actual arrival devem ser "N/A" -
5-Se um voo for atrasado o actual departure e arrival devem ser posterior ao departure e arrival respetivamente

*/
// 1
int valida_logica_voo_dest(char *origem, char *destino)
{
    int i = 0;
    while (origem[i] != '\0' && destino[i] != '\0')
    {
        if (origem[i] != destino[i])
            return 1; // se for retorna logo diferente
        i++;
    }
    if (origem[i] == '\0' && destino[i] == '\0')
    {
        return 0; // iguais
    }
    return 1;
}

// 2
// devolve >0  se departure for maior que arrival
int compare_datas(char *departure, char *arrival)
{
    // comparar as strings datahora
    return strcmp(departure, arrival);
}

// 3
int valida_aircraft_id(char *id, Gestor_Aeronaves g_aeronaves)
{
    if (get_aeronave(g_aeronaves, id) == NULL)
    {
        return 0;
    }
    return 1;
}

// 4
int valida_logica_voo_cancelado(voo_status estado, char *actual_departure, char *actual_arrival)
{
    if (estado == CANCELLED)
    {
        if (strcmp(actual_departure, "N/A") != 0 || strcmp(actual_arrival, "N/A") != 0)
            return 0;
        return 1;
    }
    return 0;
}

// 5
int valida_logica_voo_atrasado(voo_status estado, char *departure, char *arrival, char *actual_departure, char *actual_arrival)
{
    if (estado == DELAYED)
    {
        if (compare_datas(departure, actual_departure) > 0 || compare_datas(arrival, actual_arrival) > 0) // se o estado for delayed a data do actual tem de ser apos a data inicial
            return 0;
    }
    return 1;
}

int valida_aeroportos_ids(char *origin, char *destination, Gestor_Aeroportos g_aeroportos)
{
    if (!verifica_IATA(origin) || !verifica_IATA(destination) || get_aeroporto(g_aeroportos, origin) == NULL || get_aeroporto(g_aeroportos, destination) == NULL)
    {
        return 0; // Se algum aeroporto não existir, retorna 0
    }
    return 1; // Ambos os aeroportos existem
}
