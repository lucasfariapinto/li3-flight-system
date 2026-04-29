#ifndef AERONAVES_H
#define AERONAVES_H
#include "utils/string_pool.h"

/**
 * @brief Pointer to structure that represents a aeronave record.
 */
typedef struct aeronave *Aeronave;

/**
 * @brief Allocates and initializes an empty aeronave record.
 * @return Pointer to a newly allocated Aeronave.
 */
Aeronave initialize_aeronave();

/**
 * @brief Creates a new aeronave record.
 * @param id Aeronave ID.
 * @param manufacturer Aeronave manufacturer.
 * @param model Aeronave model.
 * @param sp String Pool.
 * @return Aeronave.
 */
Aeronave create_aeronave(char *id, char *manufacturer, char *model, String_Pool sp);

/**
 * @brief Frees the memory allocated for a Aeronave record.
 * @param a Pointer to the Aeronave struct to be freed.
 */
void free_aeronave(void *a);

// getters

/**
 * @brief Gets the ID of a Aeronave record.
 * @param aeronave pointer to the Aeronave record.
 * @return A string representing the ID of the Aeronave.
 */
char *get_aeronave_identifier(Aeronave aeronave);

/**
 * @brief Gets the manufacturer of a Aeronave record.
 * @param aeronave pointer to the Aeronave record.
 * @return A string representing the manufacturer of the Aeronave.
 */
char *get_aeronave_manufacturer(Aeronave aeronave);

/**
 * @brief Gets the model of a aeronave record.
 * @param aeronave pointer to the Aeronave record.
 * @return A string representing the model of the Aeronave.
 */
char *get_aeronave_model(Aeronave aeronave);

/**
 * @brief Gets the number of flights of a Aeronave record.
 * @param aeronave pointer to the Aeronave record.
 * @return An integer representing the number of flights of the Aeronave.
 */
int get_aeronave_num_flights(Aeronave aeronave);

// setters

/**
 * @brief Set function for the ID of a Aeronave record.
 * @param aeronave pointer to the Aeronave struct.
 * @param id string representing the new ID of the Aeronave.
 */
void set_aeronave_identifier(Aeronave aeronave, char *id);

/**
 * @brief Set function for the manufacturer of a Aeronave record.
 * @param aeronave pointer to the Aeronave struct.
 * @param manufacturer string representing the new manufacturer of the Aeronave.
 * @param sp String Pool.
 */
void set_aeronave_manufacturer(Aeronave aeronave, char *manufacturer, String_Pool sp);

/**
 * @brief Set function for the model of a Aeronave record.
 * @param aeronave pointer to the Aeronave struct.
 * @param model string representing the new model of the Aeronave.
 * @param sp String Pool
 */
void set_aeronave_model(Aeronave aeronave, char *model, String_Pool sp);

/**
 * @brief Set function for the number of flights of a Aeronave record.
 * @param aeronave pointer to the Aeronave struct.
 * @param num_flights integer representing the new number of flights of the Aeronave.
 */
void set_aeronave_num_flights(Aeronave aeronave, int num_flights);

#endif
