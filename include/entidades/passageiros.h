#ifndef PASSAGEIROS_H
#define PASSAGEIROS_H

#include "utils/string_pool.h"

/**
 * @brief Struct representing a passageiro.
 */
typedef struct passageiro *Passageiro;

/**
 * @brief Creates a new passageiro reservation.
 * @param first_name The first name of the passageiro.
 * @param last_name The last name of the passageiro.
 * @param dob The date of birth of the passageiro.
 * @param nationality The nationality of the passageiro.
 * @param sp String Pool.
 * @return A pointer to the newly created passageiro reservation.
 */
Passageiro create_passageiro(char *first_name,
                             char *last_name, int dob,
                             char *nationality, String_Pool sp);

/**
 * @brief Frees the memory allocated for a passageiro reservation.
 * @param passageiro Pointer to the passageiro reservation to be freed.
 */
void free_passageiro(void *passageiro);

/**
 * @brief Initializes a new passageiro reservation with default values.
 * @return A pointer to the initialized passageiro reservation.
 */
Passageiro initialize_passageiro();

/**
 * @brief Get function for the first name of the passageiro.
 * @param p Pointer to the passageiro struct.
 * @return A copy of the first name of the passageiro.
 */
char *get_passageiro_first_name(Passageiro p);

/**
 * @brief Get function for the last name of the passageiro.
 * @param p Pointer to the passageiro struct.
 * @return A copy of the last name of the passageiro.
 */
char *get_passageiro_last_name(Passageiro p);

/**
 * @brief Get function for the date of birth of the passageiro.
 * @param p Pointer to the passageiro struct.
 * @return A copy of the date of birth of the passageiro.
 */
int get_passageiro_dob(Passageiro p);

/**
 * @brief Get function for the nationality of the passageiro.
 * @param p Pointer to the passageiro struct.
 * @return A copy of the nationality of the passageiro.
 */
const char *get_passageiro_nationality(Passageiro p);

/**
 * @brief Set function for the first name of the passageiro.
 * @param p Pointer to the passageiro struct.
 * @param first_name The new first name to set.
 * @param sp String Pool.
 */
void set_passageiro_first_name(Passageiro p, char *first_name, String_Pool sp);

/**
 * @brief Set function for the last name of the passageiro.
 * @param p Pointer to the passageiro struct.
 * @param last_name The new last name to set.
 * @param sp String Pool.
 */
void set_passageiro_last_name(Passageiro p, char *last_name, String_Pool sp);

/**
 * @brief Set function for the date of birth of the passageiro.
 * @param p Pointer to the passageiro struct.
 * @param dob The new date of birth to set.
 */
void set_passageiro_dob(Passageiro p, int dob);

/**
 * @brief Set function for the nationality of the passageiro.
 * @param p Pointer to the passageiro struct.
 * @param nationality The new nationality to set.
 * @param sp String Pool.
 */
void set_passageiro_nationality(Passageiro p, char *nationality, String_Pool sp);

#endif