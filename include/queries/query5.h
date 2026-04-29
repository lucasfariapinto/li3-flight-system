#ifndef QUERY5_H
#define QUERY5_H

#include <stdio.h>
#include "gestor_entidades/gestor_voos.h"

/**
 * @brief Executes query 5: Top N airlines with highest average delay per flight
 *
 * Finds the N airlines with the highest average delay time, considering only
 * flights with DELAYED status. The delay is calculated in minutes as the
 * difference between actual_arrival and actual_departure times.
 * Results are sorted by average delay (descending), with ties broken alphabetically.
 *
 * @param line Command line arguments (contains N value)
 * @param gv Manager of all flights
 * @param file Output file pointer for results
 */
char *query5(char **line, Gestor_Voos gv, char separator);

#endif // QUERY5_H