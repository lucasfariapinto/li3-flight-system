#include "entidades/passageiros.h"
#include <string.h>
#include <stdlib.h>
#include "gestor_entidades/gestor.h"
#include "utils/string_pool.h"

struct passageiro
{
  const char *first_name;
  const char *last_name;
  int dob;
  const char *nationality;
};

Passageiro initialize_passageiro()
{
  Passageiro p = (Passageiro)malloc(sizeof(struct passageiro));
  if (!p)
    return NULL;
  p->first_name = NULL;
  p->last_name = NULL;
  p->dob = 0;
  p->nationality = NULL;
  return p;
}

Passageiro create_passageiro(char *first_name,
                             char *last_name, int dob,
                             char *nationality, String_Pool sp)
{
  Passageiro p = initialize_passageiro();
  if (!p)
    return NULL;

  p->first_name = insert_string_in_pool(first_name, sp);
  p->last_name = insert_string_in_pool(last_name, sp);
  p->dob = dob;
  p->nationality = insert_string_in_pool(nationality, sp);

  return p;
}

void free_passageiro(void *passageiro)
{
  Passageiro p = passageiro;
  if (p)
  {
    free(p);
  }
}

// Getters
char *get_passageiro_first_name(Passageiro p) { return strdup(p->first_name); }
char *get_passageiro_last_name(Passageiro p) { return strdup(p->last_name); }
int get_passageiro_dob(Passageiro p) { return p->dob; }
const char *get_passageiro_nationality(Passageiro p) { return p->nationality; }

// Setters

void set_passageiro_first_name(Passageiro p, char *first_name, String_Pool sp)
{
  p->first_name = insert_string_in_pool(first_name, sp);
}

void set_passageiro_last_name(Passageiro p, char *last_name, String_Pool sp)
{
  p->last_name = insert_string_in_pool(last_name, sp);
}

void set_passageiro_dob(Passageiro p, int dob)
{
  p->dob = dob;
}
void set_passageiro_nationality(Passageiro p, char *nationality, String_Pool sp)
{
  p->nationality = insert_string_in_pool(nationality, sp);
}
