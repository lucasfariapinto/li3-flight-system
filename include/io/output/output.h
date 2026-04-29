#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>

/**
 * @brief Build a formatted result string from given values and formats.
 * @param result Array of pointers to values to format.
 * @param format Array of format strings.
 * @param n Number of fields.
 * @param separator Character used to separate fields in the output line.
 * @return Newly allocated C string containing the formatted line.
 */
char *generate_result_string(void *result[], char *format[], int n, char separator);

/**
 * @brief Convert an integer date YYYYMMDD to a string "YYYY-MM-DD".
 * @param date Date as integer in YYYYMMDD format.
 * @return Newly allocated C string with the formatted date.
 */
char *convert_date_to_string(int date);

/**
 * @brief Generate the string used when a query has no results.
 * @return Newly allocated C string representing an empty result.
 */
char *generate_empty_result_string();

/**
 * @brief Write a C string to the given FILE stream.
 * @param file FILE pointer where the string will be written.
 * @param string C string to write.
 */
void print_string_to_file(FILE *file, char *string);;

#endif /* OUTPUT_H */