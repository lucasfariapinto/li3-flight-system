#ifndef PARSER_H
#define PARSER_H
#include "entidades/reservas.h"
#include "entidades/aeroportos.h"
#include "entidades/voos.h"
#include "gestor_entidades/gestor.h"
#include <stdio.h>

/**
 * @brief Parses a dataset file line by line using the provided line parsing function
 * @param file Pointer to the dataset file
 * @param f_erros Pointer to the error logging file
 * @param parse_line Function pointer to the line parsing function
 * @param is_used Flag indicating whether to store parsed entities in memory
 * @param g_global Pointer to the global entity manager
 */
void parse_dataset(FILE *file, FILE *f_erros, void (*parse_line)(char *, int, FILE *, Gestor_Global, size_t line_size), int is_used, Gestor_Global g_global);

/**
 * @brief Opens a file for reading
 * @param dataset_path Path to the dataset folder
 * @param file_name Name of the file to open
 * @param mode Mode to open the file ("r" for read, "w" for write)
 * @param path_has_file Flag indicating if dataset_path already includes the file name
 * @return Pointer to the opened file or NULL in case of error
 */
FILE *open_file(char *dataset_path, char *file_name, char *mode, int path_has_file_name);

/**
 * @brief Reads a line from a file
 * @param file Pointer to the file
 * @param acabou Pointer to an integer that indicates if the end of the file has been reached
 * @return The line read or NULL in case of end of file
 */
char *get_line(FILE *file, int *acabou);

/**
 * @brief Parses a string until the next comma
 * @param ptr Pointer to the string to parse
 * @param separator Character that separates the string (e.g., comma or quote)
 * @return Copy of the parsed string or NULL in case of error
 */
char *parse_string(char **ptr, char separator);

/**
 * @brief Parses a list of IDs
 * @param ptr Pointer to the string to parse
 * @return GArray containing the parsed IDs
 */
void parse_ids_list(char **ptr, char **first, char **second);

/**
 * @brief Converts a string to an integer
 * @param num The string with an integer
 * @return The converted integer
 */
int string_to_int(char *num);

/**
 * @brief Converts a string to a float
 * @param num The string with a float
 */
float string_to_float(char *num);

/**
 * @brief Parses a boolean until the next comma
 * @param ptr Pointer to the string to parse
 * @return Parsed boolean value
 */
bool parse_bool(char **ptr);

/**
 * @brief Parses an aeroporto_type until the next comma
 * @param ptr Pointer to the string to parse
 * @return Parsed aeroporto_type
 */
aeroporto_type parse_aeroporto_type(char **ptr);

/**
 * @brief Parses a voo_status until the next comma
 * @param ptr Pointer to the string to parse
 * @return Parsed voo_status
 */
voo_status parse_voo_status(char **ptr);

/**
 * @brief Converts a datetime string to separate date and time integers
 * @param datahora The string with a datetime in the format "YYYY-MM-DD HH:MM"
 * @param data Pointer to store the converted date as an integer (YYYYMMDD), or NULL if not needed
 * @param hora Pointer to store the converted time as an integer (HHMM), or NULL if not needed
 */
void string_to_datetime(char *datahora, int *data, int *hora);

/**
 *  @brief Converts a date string to an integer
 * @param date The string with a int in the format YYYYMMDD
 */
int string_to_data(char *date);

/**
 * @brief Skips the current field in the string
 * @param ptr Pointer to the string to parse
 */
void skip(char **ptr);

#endif // PARSER_H
