#ifndef GESTOR_H
#define GESTOR_H

#include "gestor_entidades/gestor_aeroportos.h"
#include "gestor_entidades/gestor_aeronaves.h"
#include "gestor_entidades/gestor_voos.h"
#include "gestor_entidades/gestor_passageiros.h"
#include "gestor_entidades/gestor_reservas.h"
#include "utils/string_pool.h"

/**
 * @file gestor.h
 * @brief Header file for the global entity manager (Gestor_Global)
 */
typedef struct gestor_global *Gestor_Global;

/**
 * @brief Initializes a new global entity manager
 * @return Pointer to the newly created Gestor_Global struct
 */
Gestor_Global initialize_gestor_global();

/**
 * @brief Frees the memory allocated for a Gestor_Global struct and its fields
 * @param gestor Pointer to the Gestor_Global struct to be freed
 */
void free_gestor_global(Gestor_Global gestor);

/**
 * @brief Sets the airport manager in the global entity manager
 * @param gg Pointer to the Gestor_Global struct
 * @param ga Pointer to the Gestor_Aeroportos struct to be set
 */
void set_gestor_aeroportos(Gestor_Global gg, Gestor_Aeroportos ga);

/**
 * @brief Sets the aircraft manager in the global entity manager
 * @param gg Pointer to the Gestor_Global struct
 * @param ga Pointer to the Gestor_Aeronaves struct to be set
 */
void set_gestor_aeronaves(Gestor_Global gg, Gestor_Aeronaves ga);

/**
 * @brief Sets the flight manager in the global entity manager
 * @param gg Pointer to the Gestor_Global struct
 * @param gv Pointer to the Gestor_Voos struct to be set
 */
void set_gestor_voos(Gestor_Global gg, Gestor_Voos gv);

/**
 * @brief Sets the passenger manager in the global entity manager
 * @param gg Pointer to the Gestor_Global struct
 * @param gp Pointer to the Gestor_Passageiros struct to be set
 */
void set_gestor_passageiros(Gestor_Global gg, Gestor_Passageiros gp);

/**
 * @brief Sets the reservation manager in the global entity manager
 * @param gg Pointer to the Gestor_Global struct
 * @param gr Pointer to the Gestor_Reservas struct to be set
 */
void set_gestor_reservas(Gestor_Global gg, Gestor_Reservas gr);

/**
 * @brief Sets the string pool in the global entity manager
 * @param gg Pointer to the Gestor_Global struct
 * @param sp Pointer to the String_Pool struct to be set
 */
void set_string_pool(Gestor_Global gg, String_Pool sp);

/**
 * @brief Gets the airport manager from the global entity manager
 * @param gg Pointer to the Gestor_Global struct
 * @return Pointer to the Gestor_Aeroportos struct
 */
Gestor_Aeroportos get_gestor_aeroportos(Gestor_Global gg);

/**
 * @brief Gets the aircraft manager from the global entity manager
 * @param gg Pointer to the Gestor_Global struct
 * @return Pointer to the Gestor_Aeronaves struct
 */
Gestor_Aeronaves get_gestor_aeronaves(Gestor_Global gg);

/**
 * @brief Gets the flight manager from the global entity manager
 * @param gg Pointer to the Gestor_Global struct
 * @return Pointer to the Gestor_Voos struct
 */
Gestor_Voos get_gestor_voos(Gestor_Global gg);

/**
 * @brief Gets the passenger manager from the global entity manager
 * @param gg Pointer to the Gestor_Global struct
 * @return Pointer to the Gestor_Passageiros struct
 */
Gestor_Passageiros get_gestor_passageiros(Gestor_Global gg);

/**
 * @brief Gets the reservation manager from the global entity manager
 * @param gg Pointer to the Gestor_Global struct
 * @return Pointer to the Gestor_Reservas struct
 */
Gestor_Reservas get_gestor_reservas(Gestor_Global gg);

/**
 * @brief Gets the string pool from the global entity manager
 * @param gg Pointer to the Gestor_Global struct
 * @return Pointer to the String_Pool struct
 */
String_Pool get_string_pool(Gestor_Global gg);

#endif // GESTOR_H