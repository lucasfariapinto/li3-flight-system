#ifndef GESTOR_RESERVAS_H
#define GESTOR_RESERVAS_H

#include <stdlib.h>
#include "entidades/reservas.h"

/**
 * @brief Struct that contains all the reservations
 */
typedef struct gestor_reservas *Gestor_Reservas;

/**
 * @brief Initializes the reservations manager
 * @return Pointer to the initialized reservations manager
 */
Gestor_Reservas initialize_gestor_reserva();

/**
 * @brief Frees the memory allocated for the reservations manager.
 * @param gestor Pointer to the reservations manager to be freed.
 */
void free_gestor_reservas(Gestor_Reservas gestor);

/**
 * @brief Insert a reservation id into the manager's id set.
 * @param g_reservas Pointer to the reservations manager.
 * @param reservation_id String reservation identifier.
 */
void insert_id_reserva(Gestor_Reservas g_reservas, char *reservation_id);

/**
 * @brief Insert a nationality / IATA association used by query 6.
 * @param g_reservas Pointer to the reservations manager.
 * @param nacionalidade Nationality string.
 * @param iata IATA code string.
 */
void insert_nacionalidade(Gestor_Reservas g_reservas, const char *nacionalidade, int iata);

/**
 * @brief Check whether a reservation id exists in the manager.
 * @param g_reservas Pointer to the reservations manager.
 * @param reservation_id Reservation id string to check.
 * @return Non-zero if the id exists, zero otherwise.
 */
int id_reserva_exists(Gestor_Reservas g_reservas, char *reservation_id);

/**
 * @brief Struct that counts reservations by nationality
 */
typedef struct contador_nacionalidade *Contador_Nacionalidade;

/**
 * @brief Builds the data structure for query 6
 * @param g Pointer to the reservations manager
 */
void build_q6(Gestor_Reservas g_reservas);

/**
 * @brief Callback used with g_hash_table_foreach to select the IATA with maximum count for a nationality.
 * @param key Pointer to the nationality key.
 * @param value Pointer to the GTree containing Contador_Nacionalidade entries.
 * @param user_data Pointer to a GHashTable where the chosen Contador_Nacionalidade will be inserted.
 */
void select_max_iata(gpointer key, gpointer value, gpointer user_data);

/**
 * @brief Gets the maximum IATA code from a tree.
 * @param key Pointer to the IATA code.
 * @param value Pointer to the associated value.
 * @param user_data Pointer to user data.
 */
void get_max_iata(gpointer key, gpointer value, gpointer user_data);

/**
 * @brief Return the most frequent IATA code for a given nationality.
 * @param g Pointer to the reservations manager.
 * @param nacionalidade Nationality string to query.
 * @param contador Output pointer that will receive the count of occurrences for the returned IATA.
 * @param sp String Pool
 * @return Int version of the IATA string or -1 if none found.
 */
int get_q6(Gestor_Reservas g, char *nacionalidade, int *contador, String_Pool sp);

/**
 * @brief Gets the IATA code for a given nationality
 * @param g_reservas Pointer to the reservations manager
 * @param nacionalidade Pointer to the nationality string
 * @param sp String Pool
 * @return Integer version of the IATA code if found, -1 otherwise
 */
int get_nacionalidade(Gestor_Reservas g_reservas, char *nacionalidade, String_Pool sp);

#endif // GESTOR_RESERVAS_H