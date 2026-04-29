#ifndef GESTOR_VOOS_H
#define GESTOR_VOOS_H

#include <stdlib.h>
#include "entidades/voos.h"
#include "gestor_entidades/gestor_aeronaves.h"
#include "gestor_entidades/gestor_aeroportos.h"
#include "gestor_entidades/gestor.h"

/**
 * @brief Struct that contains all the voos
 */
typedef struct gestor_voos *Gestor_Voos;

typedef struct airline_result *AirlineResult;

/**
 * @brief Initializes the voos manager
 * @return Pointer to the initialized voos manager
 */
Gestor_Voos initialize_gestor_voos();

/**
 * @brief Frees the memory allocated for the voos manager
 * @param gestor Pointer to the voos manager to be freed
 */
void free_gestor_voos(Gestor_Voos gestor);

/**
 * @brief Inserts a voo into the voos manager.
 * @param gv Pointer to the voos manager.
 * @param voo Pointer to the Voo to be inserted (ownership transferred).
 * @param voo_id Voo identifier string (will be duplicated internally).
 */
void insert_voo(Gestor_Voos gv, Voo voo, char *voo_id);

/**
 * @brief Retrieves a voo from the voos manager by its code
 * @param g Pointer to the voos manager
 * @param code Pointer to the voo code
 * @return The voo associated with the given code
 */
Voo get_voo(Gestor_Voos g, char *code);

/**
 * @brief Compare function variant for internal use.
 * @param a Pointer to first entry.
 * @param b Pointer to second entry.
 * @return Comparator result as per GLib convention.
 */
gint compare_airlines_result(gconstpointer a, gconstpointer b);

/**
 * @brief Record delay information for a delayed voo of an airline.
 * @param g_voos Pointer to the Gestor_Voos.
 * @param airline Airline identifier string.
 * @param delay_minutes Delay in minutes for this voo.
 * @param sp String Pool.
 */
void insert_airline(Gestor_Voos g_voos, char *airline, float delay_minutes, String_Pool sp);

/**
 * @brief Callback used to convert airline statistics into AirlineResult entries.
 * @param key Airline name string.
 * @param value Pointer to AirlineStats.
 * @param user_data Pointer to a BuildContext structure.
 */

void build_q5(gpointer key, gpointer value, gpointer user_data);

/**
 * @brief Build the internal ordered list of most delayed airlines.
 * @param g_voos Pointer to the Gestor_Voos.
 */
void build_most_delayed(Gestor_Voos g_voos);

/**
 * @brief Sort the internal airlines-by-delay array.
 * @param g_voos Pointer to the Gestor_Voos.
 */
void sort_atraso_companhias(Gestor_Voos g_voos);

/**
 * @brief Produce the result string for the top-n airlines.
 * @param g_voos Pointer to the Gestor_Voos.
 * @param n Number of top entries to include.
 * @param separator Character used to separate fields in the generated string.
 * @return Newly allocated string with the formatted result.
 */
char *result_top_n(Gestor_Voos g_voos, int n, char separator);

#endif