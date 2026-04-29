#ifndef VOOS_H
#define VOOS_H

#include <stdio.h>
#include "entidades/aeroportos.h"
#include "gestor_entidades/gestor_aeroportos.h"

typedef char voo_status;
#define ON_TIME 'O'
#define DELAYED 'D'
#define CANCELLED 'C'
#define ERROR_STATUS 'E'

/**
 * @brief Struct that represents a voo and Voo is a pointer for that struct.
 */
typedef struct voo *Voo;

/**
 * @brief Initializes a new voo with all fields set to NULL.
 * @return A pointer to the newly created Voo struct.
 */
Voo initialize_voo();

/**
 * @brief Frees the memory allocated for a voo.
 * @param voo Pointer to the voo struct to be freed.
 */
void free_voo(void *v);

/**
 * @brief Get function for the departure of the voo.
 * @param voo Pointer to the voo struct.
 * @return A copy of the requested attribute.
 */
int get_voo_acutal_departure_date(Voo voo);

/**
 * @brief Get function for the actual departure of the voo.
 * @param voo Pointer to the voo struct.
 * @return A copy of the requested attribute.
 */
int get_voo_departure_date(Voo voo);

/**
 * @brief Get function for the status of the voo.
 * @param voo Pointer to the voo struct.
 * @return A copy of the requested attribute.
 */
voo_status get_voo_status(Voo voo);

/**
 * @brief Get function for the origin of the voo.
 * @param voo Pointer to the voo struct.
 * @return A copy of the requested attribute.
 */
Aeroporto get_voo_origin(Voo voo);

/**
 * @brief Get function for the destination of the voo.
 * @param voo Pointer to the voo struct.
 * @return A copy of the requested attribute.
 */
Aeroporto get_voo_destination(Voo voo);

/**
 * @brief Set function for the actual departure of the voo.
 * @param voo Pointer to the voo struct.
 * @param actual_departure New value for the attribute.
 */
void set_voo_departure_date(Voo voo, int departure);

/**
 * @brief Set function for the status of the voo.
 * @param voo Pointer to the voo struct.
 * @param status New value for the attribute.
 */
void set_voo_status(Voo voo, voo_status status);

/**
 * @brief Set function for the origin of the voo.
 * @param voo Pointer to the voo struct.
 * @param origin New value for the attribute.
 * @param gestor_aeroportos Pointer to the gestor_aeroportos struct.
 */
void set_voo_origin(Voo voo, char *origin, Gestor_Aeroportos gestor_aeroportos);

/**
 * @brief Set function for the destination of the voo.
 * @param voo Pointer to the voo struct.
 * @param destination New value for the attribute.
 * @param gestor_aeroportos Pointer to the gestor_aeroportos struct.
 */
void set_voo_destination(Voo voo, char *destination, Gestor_Aeroportos gestor_aeroportos);

/**
 * @brief Function to create a voo with all its attributes.
 * @param status voo status.
 * @param origin Origin airport.
 * @param destination Destination airport.
 * @param departure_date Scheduled departure time.
 * @param gestor_aeroportos Pointer to the gestor_aeroportos struct.
 * @return A pointer to the newly created Voo struct.
 */
Voo create_voo(voo_status status, char *origin, char *destination, int departure_date, Gestor_Aeroportos gestor_aeroportos);
#endif // VOOS_H