#ifndef QUERY6_H
#define QUERY6_H

#include "gestor_entidades/gestor_reservas.h"
#include "gestor_entidades/gestor.h"
#include <stdio.h>

/**
 * @brief Executes Query 6: Given a nationality, returns the IATA code of the airport with the most departing passengers
 * @param line Pointer to the input line containing the nationality
 * @param g_reservas Pointer to the reservations manager
 * @param separator Character used to separate fields in the output
 * @param sp String Pool
 * @return Formatted result string according to the specified separator
 */
char *query6(char **line, Gestor_Reservas g_reservas, char separator, String_Pool sp);
#endif // QUERY6_H