#ifndef AEROPORTOS_PARSER_H
#define AEROPORTOS_PARSER_H

#include "entidades/aeroportos.h"
#include "gestor_entidades/gestor.h"
#include "entidades/aeronaves.h"
#include <stdio.h>

/**
 * @brief Parses the airports dataset
 * @param dataset_path Path to the dataset directory
 * @param is_used Flag indicating whether to store airports in memory
 * @param g_global Pointer to the global entity manager
 */
void aeroportos_parser(char *dataset_path, int is_used, Gestor_Global g_global);

/**
 * @brief Parses a line from the airports dataset and inserts a valid Aeroporto object into the corresponding gestor
 * @param line Line from the dataset
 * @param is_used Flag indicating whether to create the Aeroporto object
 * @param f_erros_aeroportos File pointer for logging errors
 * @return Parsed Aeroporto object
 */
void aeroporto_parse_line(char *line, int is_used, FILE *f_erros_aeroportos, Gestor_Global g_global, size_t line_size);

#endif // AEROPORTOS_PARSER_H