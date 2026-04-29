#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "gestor_entidades/gestor.h"

/**
 * @brief Executes queries from a file using the entity managers
 * @param g_global Manager containing all entity managers
 * @param queries_path Path to the file containing the queries to execute
 */
void interpreter(Gestor_Global g_global, char *queries_path);

#endif // INTERPRETER_H