/* #include "entidades/reservas.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glib.h>
#include <stdio.h>
#include "entidades/passageiros.h"
#include "entidades/voos.h"
#include "gestor_entidades/gestor_passageiros.h"
#include "gestor_entidades/gestor_voos.h"

struct reserva
{
    char *reservation_id;
    Voo flight1;
    Voo flight2;
    Passageiro passageiro;
    int price;
};

Reserva initialize_reserva()
{
    Reserva r = (Reserva)malloc(sizeof(struct reserva));

    r->reservation_id = NULL;
    r->flight1 = NULL;
    r->flight2 = NULL;
    r->passageiro = NULL;
    r->price = 0;

    return r;
}

Reserva create_reserva(char *reservation_id, char *flight_id1, char *flight_id2,
                       int document_number,
                       int price, Gestor_Passageiros gestor_passageiros, Gestor_Voos gestor_voos)
{
    Reserva r = initialize_reserva();

    r->reservation_id = strdup(reservation_id);
    r->flight1 = get_voo(gestor_voos, flight_id1);
    r->flight2 = get_voo(gestor_voos, flight_id2);
    r->passageiro = get_passageiro(gestor_passageiros, document_number);
    r->price = price;
    return r;
}

void free_reserva(void *reserva)
{
    Reserva r = reserva;
    free(r->reservation_id);
    free(r->flight1);
    free(r->flight2);
    free(r->passageiro);

    free(r);
}

char *get_reserva_id(Reserva r) { return strdup(r->reservation_id); }
Voo get_reserva_flight1(Reserva r) { return r->flight1; }
Voo get_reserva_flight2(Reserva r) { return r->flight2; }
Passageiro get_reserva_document_number(Reserva r) { return r->passageiro; }
int get_reserva_price(Reserva r) { return r->price; }
void set_reserva_id(Reserva r, char *reservation_id)
{
    r->reservation_id = reservation_id;
}

void set_reserva_flights_id1(Reserva r, char *flight_id1, Gestor_Voos g_voos)
{
    r->flight1 = get_voo(g_voos, flight_id1);
}

void set_reserva_flights_id2(Reserva r, char *flight_id2, Gestor_Voos g_voos)
{
    r->flight2 = get_voo(g_voos, flight_id2);
}

void set_reserva_document_number(Reserva r, int document_number, Gestor_Passageiros g_passageiros)
{
    r->passageiro = get_passageiro(g_passageiros, document_number);
}

void set_reserva_price(Reserva r, int price)
{
    r->price = price;
} */