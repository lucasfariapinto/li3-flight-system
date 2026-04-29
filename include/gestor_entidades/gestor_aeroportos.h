#ifndef GESTOR_AEROPORTOS_H
#define GESTOR_AEROPORTOS_H

#include <stdlib.h>
#include "entidades/aeroportos.h"
#include <glib.h>

/**
 * @brief Struct that contains all the aeroportos
 */
typedef struct gestor_aeroportos *Gestor_Aeroportos;

/**
 * @brief Initializes the aeroporto manager
 * @return Pointer to the initialized aeroporto manager
 */
Gestor_Aeroportos initialize_gestor_aeroportos();

/**
 * @brief Frees the memory allocated for the aeroporto manager
 * @param gestor Pointer to the aeroporto manager to be freed
 */
void free_gestor_aeroportos(Gestor_Aeroportos gestor);

/**
 * @brief Gets the size of the aeroportos array
 * @param gestor Pointer to the aeroporto manager
 * @return Size of the aeroportos array
 */
int get_aeroportos_array_size(Gestor_Aeroportos gestor);

/**
 * @brief Checks if the aeroportos array is sorted
 * @param gestor Pointer to the aeroporto manager
 * @return 1 if sorted, 0 otherwise
 */
int get_aeroportos_is_sorted(Gestor_Aeroportos gestor);

/**
 * @brief Inserts an aeroporto into the aeroporto manager
 * @param gestor Pointer to the aeroporto manager
 * @param aeroportos Airport to be inserted
 */
void insert_aeroporto(Gestor_Aeroportos gestor, Aeroporto aeroportos);

/**
 * @brief Gets the aeroporto with the most departures between two dates
 * @param gestor Pointer to the aeroporto manager
 * @param start_date Start date of the interval (inclusive)
 * @param end_date End date of the interval (inclusive)
 * @return Airport with the most departures between the two dates
 */
Aeroporto get_aeroporto_with_most_departures(Gestor_Aeroportos gestor, int start_date, int end_date, int *num_departures);

/**
 * @brief Retrieves an aeroporto from the aeroporto manager by its IATA code
 * @param g Pointer to the aeroporto manager
 * @param code Pointer to the IATA code of the aeroporto
 * @return The aeroporto associated with the given IATA code
 */
Aeroporto get_aeroporto(Gestor_Aeroportos g, char *code);
#endif // GESTOR_AEROPORTOS_H
