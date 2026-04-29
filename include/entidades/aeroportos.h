#ifndef AEROPORTOS_H
#define AEROPORTOS_H

#include <glib.h>
#include "utils/string_pool.h"

/**
 * @brief Struct that represents an aeroporto and Aeroporto is a pointer for that struct.
 */
typedef struct aeroporto *Aeroporto;

typedef char aeroporto_type;
#define SMALL_AIRPORT 'S'
#define MEDIUM_AIRPORT 'M'
#define LARGE_AIRPORT 'L'
#define HELIPORT 'H'
#define SEAPLANE_BASE 'B'
#define ERROR_TYPE 'E'

/**
 * @brief Initializes a new aeroporto with all fields set to NULL or 0.0.
 * @return A pointer to the newly created Aeroporto struct.
 */
Aeroporto initialize_aeroporto();

/**
 * @brief Frees the memory allocated for an Aeroporto struct and its fields.
 * @param a Pointer to the Aeroporto struct to be freed.
 */
void free_aeroporto(void *a);

/**
 * @brief Get function for the IATA code of the aeroporto.
 * @param aeroporto Pointer to the aeroporto struct.
 * @return The int version of the requested attribute.
 */
int get_aeroporto_code(Aeroporto aeroporto);

/**
 * @brief Get function for the name of the aeroporto.
 * @param aeroporto Pointer to the aeroporto struct.
 * @return A copy of the requested attribute.
 */
char *get_aeroporto_name(Aeroporto aeroporto);

/**
 * @brief Get function for the city of the aeroporto.
 * @param aeroporto Pointer to the aeroporto struct.
 * @return A copy of the requested attribute.
 */
char *get_aeroporto_city(Aeroporto aeroporto);

/**
 * @brief Get function for the country of the aeroporto.
 * @param aeroporto Pointer to the aeroporto struct.
 * @return A copy of the requested attribute.
 */
char *get_aeroporto_country(Aeroporto aeroporto);

/**
 * @brief Get the number of passengers that have landed at this aeroporto.
 * @param aeroporto Pointer to the aeroporto struct.
 * @return Integer count of passengers that have landed.
 */
int get_aeroporto_passageiros_aterram(Aeroporto aeroporto);

/**
 * @brief Get the number of passengers that have departed from this aeroporto.
 * @param aeroporto Pointer to the aeroporto struct.
 * @return Integer count of passengers that have departed.
 */
int get_aeroporto_passageiros_partem(Aeroporto aeroporto);

/**
 * @brief Get function for the type of the aeroporto.
 * @param aeroporto Pointer to the aeroporto struct.
 * @return The aeroporto type.
 */
aeroporto_type get_aeroporto_type(Aeroporto aeroporto);

/**
 * @brief Set function for the IATA code of the aeroporto.
 * @param aeroporto Pointer to the aeroporto struct.
 * @param code New value for the attribute.
 */
void set_aeroporto_code(Aeroporto aeroporto, char *code);

/**
 * @brief Set function for the name of the aeroporto.
 * @param aeroporto Pointer to the aeroporto struct.
 * @param name New value for the attribute.
 * @param sp String Pool
 */
void set_aeroporto_name(Aeroporto aeroporto, char *name, String_Pool sp);

/**
 * @brief Set function for the city of the aeroporto.
 * @param aeroporto Pointer to the aeroporto struct.
 * @param city New value for the attribute.
 * @param sp String Pool
 */
void set_aeroporto_city(Aeroporto aeroporto, char *city, String_Pool sp);

/**
 * @brief Set function for the country of the aeroporto.
 * @param aeroporto Pointer to the aeroporto struct.
 * @param country New value for the attribute.
 * @param sp String Pool.
 */
void set_aeroporto_country(Aeroporto aeroporto, char *country, String_Pool sp);

/**
 * @brief Set function for the type of the aeroporto.
 * @param aeroporto Pointer to the aeroporto struct.
 * @param type New value for the attribute.
 */
void set_aeroporto_type(Aeroporto aeroporto, aeroporto_type type);

/**
 * @brief Set the number of passengers that have landed at this aeroporto.
 * @param aeroporto Pointer to the aeroporto struct.
 * @param passageiros_aterram New total number of landed passengers.
 */
void set_aeroporto_passageiros_aterram(Aeroporto aeroporto, int passageiros_aterram);

/**
 * @brief Set the number of passengers that have departed from this aeroporto.
 * @param aeroporto Pointer to the aeroporto struct.
 * @param passageiros_partem New total number of departing passengers.
 */
void set_aeroporto_passageiros_partem(Aeroporto aeroporto, int passageiros_partem);

/**
 * @brief Increment the count of passengers that have landed by one.
 * @param aeroporto Pointer to the aeroporto struct.
 */
void incrementa_aeroporto_passageiros_aterram(Aeroporto aeroporto);

/**
 * @brief Increment the count of passengers that have departed by one.
 * @param aeroporto Pointer to the aeroporto struct.
 */
void incrementa_aeroporto_passageiros_partem(Aeroporto aeroporto);

/**
 * @brief Inserts a departure date into the aeroporto's departure dates array.
 * @param aeroporto Pointer to the aeroporto struct.
 * @param date Departure date to be inserted (in integer format, e.g., YYYYMMDD).
 */
void insert_aeroporto_departure_date(Aeroporto aeroporto, int date);

/**
 * @brief Comparison function for integers, used for sorting.
 * @param a Pointer to the first integer.
 * @param b Pointer to the second integer.
 * @return Negative value if a < b, zero if a == b, positive value if a > b.
 */
int compare_ints(gconstpointer a, gconstpointer b);

/**
 * @brief Sorts the departure dates array of the given aeroporto in ascending order.
 * @param aeroporto Pointer to the aeroporto struct.
 */
void sort_aeroporto_departure_dates(Aeroporto aeroporto);

/**
 * @brief Function to get the number of departures between two dates.
 * @param aeroporto Pointer to the aeroporto struct.
 * @param start_date Start date of the interval (inclusive).
 * @param end_date End date of the interval (inclusive).
 * @return Number of departures between the two dates.
 */
int get_number_of_departures_between_dates(Aeroporto aeroporto, int start_date, int end_date);

/**
 * @brief Function to create an aeroporto by setting all its attributes.
 * @param code IATA code of the aeroporto.
 * @param name Name of the aeroporto.
 * @param city City where the aeroporto is located.
 * @param country Country where the aeroporto is located.
 * @param type Type of the aeroporto.
 * @param sp String Pool.
 * @return A pointer to the created aeroporto struct.
 */
Aeroporto create_aeroporto(char *code, char *name, char *city, char *country, aeroporto_type type, String_Pool sp);

/**
 * @brief Converts an aeroporto_type value to its corresponding string representation.
 * @param type The aeroporto_type value to be converted.
 * @return A string representation of the aeroporto_type.
 */
char *aeroporto_type_to_string(aeroporto_type type);

#endif // AEROPORTOS_H