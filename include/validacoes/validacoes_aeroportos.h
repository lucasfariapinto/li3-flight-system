#ifndef VALIDACOES_AEROPORTOS
#define VALIDACOES_AEROPORTOS

#include <stdio.h>
#include "entidades/aeroportos.h"

/**
 * @brief Validate an airport CSV record and write an error line if invalid.
 * @param f_erros_aeroportos File pointer where validation errors will be written.
 * @param line Original CSV line (used when reporting the error).
 * @param aeroporto_code Airport IATA code string to validate.
 * @param aeroporto_latitude Latitude string (decimal degrees) to validate.
 * @param aeroporto_longitude Longitude string (decimal degrees) to validate.
 * @param aeroporto_tipo Enum value indicating the airport type.
 * @return 1 if the airport record is valid, 0 otherwise (and the original line is written to f_erros_aeroportos).
 */
int valida_aeroporto(FILE *f_erros_aeroportos, char *line, char *aeroporto_code, char *aeroporto_latitude, char *aeroporto_longitude, aeroporto_type aeroporto_tipo);

#endif // VALIDACOES_AEROPORTOS