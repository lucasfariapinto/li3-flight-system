#include "gestor_entidades/gestor.h"
#include "gestor_entidades/gestor_aeroportos.h"
#include "gestor_entidades/gestor_aeronaves.h"
#include "gestor_entidades/gestor_voos.h"
#include "gestor_entidades/gestor_passageiros.h"
#include "gestor_entidades/gestor_reservas.h"
#include "utils/string_pool.h"

struct gestor_global
{
    Gestor_Aeroportos gestor_aeroportos;
    Gestor_Aeronaves gestor_aeronaves;
    Gestor_Voos gestor_voos;
    Gestor_Passageiros gestor_passageiros;
    Gestor_Reservas gestor_reservas;
    String_Pool string_pool;
};

Gestor_Global initialize_gestor_global()
{
    Gestor_Global gg = malloc(sizeof(struct gestor_global));
    gg->gestor_aeroportos = initialize_gestor_aeroportos();
    gg->gestor_aeronaves = initialize_gestor_aeronaves();
    gg->gestor_voos = initialize_gestor_voos();
    gg->gestor_passageiros = initialize_gestor_passageiros();
    gg->gestor_reservas = initialize_gestor_reserva(); //  NULL; // Não é necessário para esta fase do projeto
    gg->string_pool = initialize_string_pool();
    return gg;
}

void free_gestor_global(Gestor_Global gestor)
{
    if (gestor)
    {
        if (gestor->gestor_aeroportos)
            free_gestor_aeroportos(gestor->gestor_aeroportos);
        if (gestor->gestor_aeronaves)
            free_gestor_aeronaves(gestor->gestor_aeronaves);
        if (gestor->gestor_voos)
            free_gestor_voos(gestor->gestor_voos);
        if (gestor->gestor_passageiros)
            free_gestor_passageiros(gestor->gestor_passageiros);
        if (gestor->gestor_reservas)
            free_gestor_reservas(gestor->gestor_reservas);
        if (gestor->string_pool)
            free_string_pool(gestor->string_pool);
        free(gestor);
    }
}

void set_gestor_aeroportos(Gestor_Global gg, Gestor_Aeroportos ga)
{
    gg->gestor_aeroportos = ga;
}

void set_gestor_aeronaves(Gestor_Global gg, Gestor_Aeronaves ga)
{
    gg->gestor_aeronaves = ga;
}

void set_gestor_voos(Gestor_Global gg, Gestor_Voos gv)
{
    gg->gestor_voos = gv;
}

void set_gestor_passageiros(Gestor_Global gg, Gestor_Passageiros gp)
{
    gg->gestor_passageiros = gp;
}

void set_gestor_reservas(Gestor_Global gg, Gestor_Reservas gr)
{
    gg->gestor_reservas = gr;
}

void set_string_pool(Gestor_Global gg, String_Pool sp)
{
    gg->string_pool = sp;
}

Gestor_Aeroportos get_gestor_aeroportos(Gestor_Global gg)
{
    return gg->gestor_aeroportos;
}

Gestor_Aeronaves get_gestor_aeronaves(Gestor_Global gg)
{
    return gg->gestor_aeronaves;
}

Gestor_Voos get_gestor_voos(Gestor_Global gg)
{
    return gg->gestor_voos;
}

Gestor_Passageiros get_gestor_passageiros(Gestor_Global gg)
{
    return gg->gestor_passageiros;
}

Gestor_Reservas get_gestor_reservas(Gestor_Global gg)
{
    return gg->gestor_reservas;
}

String_Pool get_string_pool(Gestor_Global gg)
{
    return gg->string_pool;
}
