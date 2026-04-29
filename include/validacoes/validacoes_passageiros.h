#ifndef VALIDACOES_PASSAGEIROS
#define VALIDACOES_PASSAGEIROS

#include <stdio.h>

/**
 * @brief Validates a passenger record and writes errors to a file if invalid.
 * @param f_erros_passageiros File pointer where validation errors will be written.
 * @param line Original CSV line (used when reporting the error).
 * @param document_number Document number string to validate.
 * @param dob Date of birth string to validate.
 * @param gender Gender string to validate.
 * @param email Email string to validate.
 * @return 1 if the passenger record is valid, 0 otherwise (and the error is written to f_erros_passageiros).
 */
int valida_passageiro(FILE *f_erros_passageiros, char *line, char *document_number, char *dob, char *gender, char *email);

#endif // VALIDACOES_PASSAGEIROS
