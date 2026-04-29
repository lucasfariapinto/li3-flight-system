#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

/**
 * @brief Build a filesystem path by concatenating a directory path and a file name.
 * @param path Directory path.
 * @param file_name File name to append to path.
 * @return Newly allocated string containing the combined path.
 */
char *create_path(char *path, char *file_name);

/**
 * @brief Convert a date in YYYYMMDD integer format to absolute days since a fixed epoch.
 * @param date Date represented as integer YYYYMMDD.
 * @return Number of absolute days corresponding to the given date.
 */
int date_to_absolute_days(int date);

/**
 * @brief Convert a date in YYYYMMDD to a week index relative to a fixed reference.
 * @param date Date represented as integer YYYYMMDD.
 * @return Week index. Value computed as (reference_day - date_days) / 7.
 */
int date_to_week(int date);

/**
 * @brief Compute the difference in minutes between two datetimes.
 * @param date1 First date (YYYYMMDD) used as the later datetime.
 * @param hour1 First time (HHMM) used as the later datetime.
 * @param date2 Second date (YYYYMMDD) used as the earlier datetime.
 * @param hour2 Second time (HHMM) used as the earlier datetime.
 * @return Difference in minutes. Positive if (date1/hour1) is later than (date2/hour2).
 */
float datetime_diff_minutes(int date1, int hour1, int date2, int hour2);

/**
 * @brief Checks if a given string represents a valid number.
 * @param str The string to check.
 * @return 1 if the string is a number, 0 otherwise.
 */
int is_number(char *str);

/**
 * @brief Converts a flight code (format: LLNNNNN[N]) to a unique integer.
 * @param code Flight code string.
 * @return Unique integer representation of the flight code.
 */
int flight_id_to_int(char *code);

/**
 * @brief Converts an IATA airport code (3-letter string) to a unique integer.
 * @param code IATA airport code string.
 * @return Unique integer representation of the IATA code.
 */
int iata_to_int(char *code);

/**
 * @brief Converts a unique integer back to its corresponding IATA airport code (3-letter string).
 * @param code Unique integer representation of the IATA code.
 * @return Newly allocated string with the IATA code.
 */
char *int_to_iata(int code);

#endif // UTILS_H
