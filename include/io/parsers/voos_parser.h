#ifndef VOOS_PARSER_H
#define VOOS_PARSER_H

#include "entidades/voos.h"
#include "gestor_entidades/gestor_voos.h"
#include "gestor_entidades/gestor.h"
#include <stdio.h>

/**
 * @brief Parses the flights dataset
 * @param dataset_path Path to the dataset directory
 * @param is_used Flag indicating whether to store flights in memory
 * @param g_global Pointer to the global entity manager
 */
void voos_parser(char *dataset_path, int is_used, Gestor_Global g_global);

/**
 * @brief Parses a line from the flights dataset and inserts a valid Voo object into the corresponding gestor
 * @param line Line from the dataset
 * @param is_used Flag indicating whether to create the Flight object
 * @param f_erros_voos File pointer for logging errors
 * @param g_global Pointer to the global entity manager
 */
void voo_parse_line(char *line, int is_used, FILE *f_erros_voos, Gestor_Global g_global, size_t line_size);

#endif // VOOS_PARSER_H