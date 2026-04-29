#ifndef AERONAVES_PARSER_H
#define AERONAVES_PARSER_H

#include "entidades/aeronaves.h"
#include "gestor_entidades/gestor.h"
#include <stdio.h>

/**
 * @brief Parses the aeronaves dataset
 * @param dataset_path Path to the dataset directory
 * @param is_used Flag indicating whether to store aeronaves in memory
 * @return Pointer to the aeronaves manager
 */
void aeronaves_parser(char *dataset_path, int is_used, Gestor_Global g_global);

/**
 * @brief Parses a line from the aeronaves dataset and inserts a valid Aeronave object into the corresponding gestor
 * @param line Line from the dataset
 * @param is_used Flag indicating whether to create the Aeronave object
 * @param f_erros_aeronaves File pointer for logging errors
 * @param g_global Pointer to the global entity manager
 */
void aeronave_parse_line(char *line, int is_used, FILE *f_erros_aeronaves, Gestor_Global g_global, size_t line_size);

#endif // AERONAVES_PARSER_H