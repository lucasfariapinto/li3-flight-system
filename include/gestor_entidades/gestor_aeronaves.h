#ifndef GESTOR_AERONAVES_H
#define GESTOR_AERONAVES_H

#include <stdlib.h>
#include "entidades/aeronaves.h"
#include <glib.h>

/**
 * @brief Struct that contains all the aeronaves.
 */
typedef struct gestor_aeronaves *Gestor_Aeronaves;

/**
 * @brief Initializes the aeronaves manager.
 * @return Pointer to the initialized aeronaves manager.
 */
Gestor_Aeronaves initialize_gestor_aeronaves();

/**
 * @brief Frees the memory allocated for the aeronaves manager.
 * @param gestor Pointer to the aeronaves manager to be freed.
 */
void free_gestor_aeronaves(Gestor_Aeronaves gestor);

/**
 * @brief Inserts aeronaves into the aeronaves manager.
 * @param gestor Pointer to the aeronaves manager.
 * @param aeronave aeronaves to be inserted.
 */
void insert_aeronave(Gestor_Aeronaves gestor, Aeronave aeronave);

/**
 * @brief Comparison function for sorting aeronaves by number of voos in descending order, in case of a tie, by identifier.
 * @param a Pointer to the first aeronave.
 * @param b Pointer to the second aeronave.
 * @return An integer representing the comparison result.
 */
int compare_aeronaves_by_num_flights(gconstpointer a, gconstpointer b);

/**
 * @brief Sorts the aeronaves by number of voos in descending order.
 * @param gestor Pointer to the aeronaves manager.
 */
void sort_aeronaves_by_num_flights(Gestor_Aeronaves gestor);

/**
 * @brief Retrieves the top N aeronaves with the most voos, optionally filtered by manufacturer.
 * @param a_gestor Pointer to the aeronave manager.
 * @param n The number of top aeronaves to retrieve.
 * @param manufacturer Optional manufacturer filter. If NULL, all manufacturers are considered.
 * @param airplanes Output array to store the identifiers of the top N aeronaves.
 * @param count Pointer to an integer to store the actual number of aeronaves retrieved.
 */
void get_n_mais_voos(Gestor_Aeronaves a_gestor, int n, char *manufacturer, char **airplanes, int *count);

/**
 * @brief Gets a Aeronave from the gestor by its identifier.
 * @param g Pointer to the Aeronaves manager.
 * @param code Identifier of the Aeronave to be retrieved.
 * @return Pointer to the Aeronave record.
 */
Aeronave get_aeronave(Gestor_Aeronaves g, char *code);

#endif // GESTOR_AERONAVES_H
