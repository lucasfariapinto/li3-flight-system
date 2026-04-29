#ifndef RESERVAS_PARSER_H
#define RESERVAS_PARSER_H

#include "entidades/reservas.h"
#include "gestor_entidades/gestor_reservas.h"
#include "gestor_entidades/gestor.h"
#include <stdio.h>

/**
 * @brief Parses the reservations dataset and returns a manager containing all reservations
 * @param dataset_path Path to the dataset directory
 * @param is_used Flag indicating whether to store reservations in memory
 * @param g_global Pointer to the global entity manager
 */
void reserva_parser(char *dataset_path, int is_used, Gestor_Global g_global);

/**
 * @brief Parses a line from the reservations dataset and inserts a valid Reserva object into the corresponding gestor
 * @param line Line from the dataset
 * @param is_used Flag indicating whether to create the Reserva object
 * @param f_erros_reservas File pointer for logging errors
 * @param g_global Pointer to the global entity manager
 */
void reserva_parse_line(char *line, int is_used, FILE *f_erros_reservas, Gestor_Global g_global, size_t line_size);

#endif // RESERVAS_PARSER_H