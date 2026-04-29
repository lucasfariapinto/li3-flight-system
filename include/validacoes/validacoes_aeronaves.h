#ifndef VALIDACOES_AERONAVES
#define VALIDACOES_AERONAVES

#include <stdio.h>

/**
 * @brief Validate an aircraft CSV record and write an error line if invalid.
 * @param f_erros_aeronaves File pointer where validation errors will be written.
 * @param line Original CSV line (used when reporting the error).
 * @param aeronave_year Manufacturing year string to validate (YYYY format).
 * @return 1 if the aircraft record is valid, 0 otherwise (and the original line is written to f_erros_aeronaves).
 */
int valida_aeronave(FILE *f_erros_aeronaves, char *line, char *aeronave_year);

#endif // VALIDACOES_AERONAVES