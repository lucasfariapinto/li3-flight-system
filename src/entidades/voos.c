#include "entidades/voos.h"
#include <string.h>
#include <stdlib.h>
#include "entidades/aeroportos.h"
#include "gestor_entidades/gestor_aeroportos.h"

struct voo
{
    int departure_date;    // data de partida
    voo_status status;     // estado do voo: On Time, Delayed, Cancelled
    Aeroporto origin;      // código IATA do aeroporto de origem
    Aeroporto destination; // código IATA do aeroporto de destino
};

void free_voo(void *v)
{
    Voo voo = v;
    if (voo)
    {
        free(voo);
    }
}

Voo initialize_voo()
{
    Voo voo = malloc(sizeof(struct voo));
    voo->departure_date = 0;
    voo->origin = NULL;
    voo->destination = NULL;
    return voo;
}

int get_voo_departure_date(Voo voo)
{
    return (voo->departure_date);
}

voo_status get_voo_status(Voo voo)
{
    return voo->status;
}

Aeroporto get_voo_origin(Voo voo)
{
    return voo->origin;
}

Aeroporto get_voo_destination(Voo voo)
{
    return voo->destination;
}

void set_voo_departure_date(Voo voo, int departure)
{
    voo->departure_date = departure;
}

void set_voo_status(Voo voo, voo_status status)
{
    voo->status = status;
}

void set_voo_origin(Voo voo, char *origin, Gestor_Aeroportos gestor_aeroportos)
{
    voo->origin = get_aeroporto(gestor_aeroportos, origin);
}

void set_voo_destination(Voo voo, char *destination, Gestor_Aeroportos gestor_aeroportos)
{
    voo->destination = get_aeroporto(gestor_aeroportos, destination);
}

Voo create_voo(voo_status status, char *origin, char *destination, int departure_date, Gestor_Aeroportos gestor_aeroportos)
{
    Voo voo = initialize_voo();
    set_voo_departure_date(voo, departure_date);
    set_voo_status(voo, status);
    set_voo_origin(voo, origin, gestor_aeroportos);
    set_voo_destination(voo, destination, gestor_aeroportos);
    return voo;
}