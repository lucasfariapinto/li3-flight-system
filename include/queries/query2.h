#ifndef QUERY2_H
#define QUERY2_H

#include "gestor_entidades/gestor_aeronaves.h"
#include <stdio.h>

/**
 * @brief Executes query 2: retrieves the list of aircrafts sorted by number of flights.
 * @param line Input line (not used in this query).
 * @param a_gestor Manager of aircrafts.
 * @param file File pointer to write the output.
 */
char * query2(char **line, Gestor_Aeronaves a_gestor, char separator);

#endif // QUERY2_H