#include "validacoes/validacoes_reservas.h"
#include "validacoes/validacoes.h"
#include <stdio.h>
#include <glib.h>
#include "gestor_entidades/gestor_passageiros.h"
#include "gestor_entidades/gestor_voos.h"
#include "gestor_entidades/gestor_reservas.h"
#include "entidades/reservas.h"
#include "io/parsers/parser.h"
#include "entidades/voos.h"

int valida_reserva(FILE *f_erros_reservas, char *line, char *reservation_id, char *first, char *second, char *document_number, Gestor_Passageiros g_passageiros, Gestor_Voos g_voos, Gestor_Reservas g_reservas)
{
    if (verifica_reservation_id(reservation_id, g_reservas) &&
        valida_logica_reserva_fids(first, second, g_voos) &&
        valida_logica_reserva_docnum(document_number, g_passageiros))
    {
        return 1;
    }
    else
    {
        print_error_in_file(f_erros_reservas, line);
        return 0;
    }
}

// Validação lógica da reserva
/*
1 - o campo flight ids devera corresponder a 1 ou 2 voos existentes
2- o campo document number de uma reserva devera corresponder a um passageiro existente
3- o campo flight ids quando tiver 2 voos devera ter identificador de voo em que o destino do primeiro é o origin do segundo
posso fazer o 3 na mesma função que o 1
*/

// 1 e 3
int valida_logica_reserva_fids(char *first, char *second, Gestor_Voos g_voos)
{

    if (first == NULL)
        return 0;

    Voo voo1 = get_voo(g_voos, first);
    if (voo1 == NULL)
    {
        return 0; // se o voo nao existir
    }

    if (second != NULL) // se tiver 2 voos
    {
        Voo voo2 = get_voo(g_voos, second);

        if (voo2 == NULL)
            return 0; // se o 2 voo nao existir

        // verificar se o destino do primeiro voo é igual à origem do segundo voo
        int dest1 = get_aeroporto_code(get_voo_destination(voo1));
        int origem2 = get_aeroporto_code(get_voo_origin(voo2));

        if (dest1 != origem2)
        {
            return 0;
        }
    }
    return 1;
}

// 2
int valida_logica_reserva_docnum(char *document_number, Gestor_Passageiros g)
{
    int res = 0;
    char *c = document_number;

    while (*c)
    {
        unsigned int digit = (unsigned int)(*c - '0');

        if (digit > 9)
            return 0; // Contém caracteres inválidos

        res = res * 10 + digit;
        c++;
    }
    return passageiro_exists(g, res);
}
