#ifndef QUERY3_H
#define QUERY3_H

#include "gestor_entidades/gestor_aeroportos.h"
#include <stdio.h>

/**
 * @brief Prints the airport with the most departures between two dates
 * @param line Pointer to the input line containing query parameters
 * @param a_gestor Pointer to the Airports manager
 * @param file Pointer to the output file where results will be written
 */
char *query3(char **line, Gestor_Aeroportos a_gestor, char separator);

#endif // QUERY3_H