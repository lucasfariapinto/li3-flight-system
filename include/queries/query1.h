#ifndef QUERY1_H
#define QUERY1_H

#include "gestor_entidades/gestor_aeroportos.h"
#include <stdio.h>

/**
 * @brief Executes query 1: retrieves airport information by its IATA code.
 * @param line Input line containing the IATA code.
 * @param a_gestor Manager of airports.
 * @param file File pointer to write the output.
 */
char *query1(char **line, Gestor_Aeroportos a_gestor, char separator);

#endif // QUERY1_H