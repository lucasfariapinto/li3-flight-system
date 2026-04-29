#ifndef VALIDACOES_RESERVAS
#define VALIDACOES_RESERVAS

#include <stdio.h>
#include <glib.h>
#include "entidades/reservas.h"
#include "gestor_entidades/gestor_passageiros.h"
#include "gestor_entidades/gestor_voos.h"

/**
 * @brief Validates a reservation record and writes validation errors to a file.
 * @param f_erros_reservas File pointer where validation errors will be written.
 * @param line Original CSV line (used when reporting the error).
 * @param reservation_id Reservation identifier string.
 * @param flight_ids GPtrArray of flight identifier strings associated with the reservation.
 * @param document_number Document number (passenger id) string.
 * @param g_passageiros Manager of passengers, used to validate document numbers.
 * @param g_voos Manager of flights, used to validate flight identifiers.
 * @return 1 if the reservation record is valid, 0 otherwise (and errors are written to f_erros_reservas).
 */
int valida_reserva(FILE *f_erros_reservas, char *line, char *reservation_id, char *first, char *second, char *document_number, Gestor_Passageiros g_passageiros, Gestor_Voos g_voos, Gestor_Reservas g_reservas);

/**
 * @brief Validates that all flight IDs in a reservation exist in the flights manager.
 * @param ids GPtrArray of flight identifier strings to validate.
 * @param g_voos Manager of flights where each id should be found.
 * @return 1 if all flight IDs exist, 0 if any id is missing or invalid.
 */
int valida_logica_reserva_fids(char *first, char *second, Gestor_Voos g_voos);

/**
 * @brief Validates that the document number corresponds to an existing passenger.
 * @param document_number Document number string to validate.
 * @param g Gestor_Passageiros used to verify existence of the passenger.
 * @return 1 if the document number exists in g, 0 otherwise.
 */
int valida_logica_reserva_docnum(char *document_number, Gestor_Passageiros g);

#endif // VALIDACOES_RESERVAS
