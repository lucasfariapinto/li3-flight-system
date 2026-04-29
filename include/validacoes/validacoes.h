#ifndef VALIDACOES_H
#define VALIDACOES_H

#include <stdio.h>
#include "entidades/aeroportos.h"
#include "gestor_entidades/gestor_reservas.h"

/**
 * @brief Verifies a combined date and time string.
 * @param datahora String containing date and time.
 * @return 1 if valid, 0 otherwise.
 */
int verifica_datahora(char *datahora);

/**
 * @brief Verifies a date string.
 * @param datahora String containing the date.
 * @return 1 if valid, 0 otherwise.
 */
int verifica_data(char *datahora);

/**
 * @brief Verifies a year string.
 * @param year String containing the year.
 * @return 1 if valid, 0 otherwise.
 */
int verifica_year(char *year);

/**
 * @brief Verifies an aeroporto_type value.
 * @param t The aeroporto_type value to check.
 * @return 1 if valid, 0 otherwise.
 */
int verifica_tipo_aeroporto(aeroporto_type t);

/**
 * @brief Verifies an airport code string.
 * @param code String containing the airport code.
 * @return 1 if valid, 0 otherwise.
 */
int verifica_aeroporto_code(char *code);

/**
 * @brief Verifies an email string.
 * @param email String containing the email.
 * @return 1 if valid, 0 otherwise.
 */
int verifica_email(char *email);

/**
 * @brief Verifies a latitude string.
 * @param latitude String containing the latitude.
 * @return 1 if valid, 0 otherwise.
 */
int verifica_latitude(char *latitude);

/**
 * @brief Verifies a longitude string.
 * @param longitude String containing the longitude.
 * @return 1 if valid, 0 otherwise.
 */
int verifica_longitude(char *longitude);

/**
 * @brief Verifies an IATA code string.
 * @param iata String containing the IATA code.
 * @return 1 if valid, 0 otherwise.
 */
int verifica_IATA(char *iata);

/**
 * @brief Verifies a flight ID string.
 * @param id String containing the flight ID.
 * @return 1 if valid, 0 otherwise.
 */
int verifica_flight_id(char *id);

/**
 * @brief Verifies a reservation ID string.
 * @param id String containing the reservation ID.
 * @return 1 if valid, 0 otherwise.
 */
int verifica_reservation_id(char *id, Gestor_Reservas g_reservas);

/**
 * @brief Verifies a document number string.
 * @param dn String containing the document number.
 * @return 1 if valid, 0 otherwise.
 */
int verifica_document_number(char *dn);

/**
 * @brief Verifies a gender string/value.
 * @param g String containing the gender.
 * @return 1 if valid, 0 otherwise.
 */
int verifica_gender(char *g);

/**
 * @brief Writes a validation error message for a given input line into a file.
 * @param file File pointer where the error should be printed.
 * @param line The input line that caused the error.
 */
void print_error_in_file(FILE *file, char *line);

#endif // VALIDACOES_H