#ifndef QUERY4_H
#define QUERY4_H

#include "gestor_entidades/gestor_passageiros.h"
#include <stdio.h>

/**
 * @brief Returns the passenger who appeared most often in the weekly top-10 within an optional date range.
 * @param line Pointer to the input line containing query parameters.
 * @param g_passageiros Pointer to the Passengers manager.
 * @param separator Character used to separate fields in the formatted result string.
 * @return Newly allocated string with the formatted result, or an "empty result" string if no passenger found.
 */
char *query4(char **line, Gestor_Passageiros g_passageiros, char separator);

#endif // QUERY4.H