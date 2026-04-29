#include "entidades/aeronaves.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gestor_entidades/gestor.h"
#include "utils/string_pool.h"

struct aeronave
{
    char *identifier;         // identificador único (tail number)
    const char *manufacturer; // fabricante
    const char *model;        // modelo
    int num_flights;          // número de voos que esta aeronave fez
};

Aeronave initialize_aeronave()
{
    Aeronave aeronave = malloc(sizeof(struct aeronave));
    aeronave->identifier = NULL;
    aeronave->manufacturer = NULL;
    aeronave->model = NULL;
    aeronave->num_flights = 0;
    return aeronave;
}

Aeronave create_aeronave(char *id, char *manufacturer, char *model, String_Pool sp)
{
    Aeronave aeronave = initialize_aeronave();
    set_aeronave_identifier(aeronave, id);
    set_aeronave_manufacturer(aeronave, manufacturer, sp);
    set_aeronave_model(aeronave, model, sp);
    return aeronave;
}

void free_aeronave(void *a)
{
    Aeronave aeronave = a;
    // É libertado no string pool
    free(aeronave->identifier);
    // free(aeronave->manufacturer);
    // free(aeronave->model);
    free(aeronave);
}

// getters

char *get_aeronave_identifier(Aeronave aeronave)
{
    return strdup(aeronave->identifier);
}

char *get_aeronave_manufacturer(Aeronave aeronave)
{
    return strdup(aeronave->manufacturer);
}
char *get_aeronave_model(Aeronave aeronave)
{
    return strdup(aeronave->model);
}

int get_aeronave_num_flights(Aeronave aeronave)
{
    return aeronave->num_flights;
}

// setters

void set_aeronave_identifier(Aeronave aeronave, char *id)
{
    aeronave->identifier = strdup(id);
}
void set_aeronave_manufacturer(Aeronave aeronave, char *manufacturer, String_Pool sp)
{
    aeronave->manufacturer = insert_string_in_pool(manufacturer, sp);
}
void set_aeronave_model(Aeronave aeronave, char *model, String_Pool sp)
{
    aeronave->model = insert_string_in_pool(model, sp);
}

void set_aeronave_num_flights(Aeronave aeronave, int num_flights)
{
    aeronave->num_flights = num_flights;
}