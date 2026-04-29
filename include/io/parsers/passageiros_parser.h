#ifndef PASSAGEIROS_PARSER_H
#define PASSAGEIROS_PARSER_H

#include "entidades/passageiros.h"
#include "gestor_entidades/gestor.h"
#include <stdio.h>

/**
 * @brief Parses a dataset of passengers
 * @param dataset_path The path to the dataset file.
 * @param is_used Flag indicating whether to store passengers in memory.
 * @param g_global Pointer to the global entity manager.
 */
void passageiros_parser(char *dataset_path, int is_used, Gestor_Global g_global);

/**
 * @brief Parses a single CSV line into a Passageiro and inserts it into the gestor if valid.
 * @param line The CSV line to parse.
 * @param is_used Flag indicating whether to create the Passageiro object.
 * @param f_erros_aeronaves File pointer for logging errors.
 * @param g_global Pointer to the global entity manager.
 */
void passageiro_parse_line(char *line, int is_used, FILE *f_erros_aeronaves, Gestor_Global g_global, size_t line_size);

#endif // PASSAGEIROS_PARSER_H