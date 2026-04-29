
#ifndef RESERVAS_H
#define RESERVAS_H

#include <stdbool.h>
#include <glib.h>
#include "entidades/passageiros.h"
#include "entidades/voos.h"

typedef struct gestor_voos *Gestor_Voos;
typedef struct gestor_passageiros *Gestor_Passageiros;

/**
 * @brief Struct representing a reserva.
 */
typedef struct reserva *Reserva;

/**
 * @brief Create a new reserva.
 * @param reservation_id Reserva identifier string.
 * @param flight_id1 First flight identifier string.
 * @param flight_id2 Second flight identifier string (may be NULL).
 * @param document_number Passenger document number.
 * @param price Reserva price (integer, cents or project convention).
 * @param gestor_passageiros Pointer to passengers manager (used to resolve document_number).
 * @param gestor_voos Pointer to flights manager (used to resolve flight ids).
 * @return Newly allocated Reserva object (caller owns and must free with free_reserva).
 */
Reserva create_reserva(char *reservation_id, char *flight_id1, char *flight_id2,
                       int document_number,
                       int price, Gestor_Passageiros gestor_passageiros, Gestor_Voos gestor_voos);
/**
 * @brief Frees the memory allocated for a reserva.
 * @param reserva Pointer to the reserva to be freed.
 */
void free_reserva(void *reserva);

/**
 * @brief Initializes a new reserva with default values.
 * @return A pointer to the initialized reserva.
 */
Reserva initialize_reserva();

/**
 * @brief Get function for the reserva ID.
 * @param r Pointer to the reserva struct.
 * @return The reserva ID.
 */
char *get_reserva_id(Reserva r);

/**
 * @brief Get function for the flight IDs associated with the reserva.
 * @param r Pointer to the reserva struct.
 * @return A copy of the flight IDs.
 */
Voo get_reserva_flight1(Reserva r);

/**
 * @brief Get function for the flight IDs associated with the reserva.
 * @param r Pointer to the reserva struct.
 * @return A copy of the flight IDs.
 */
Voo get_reserva_flight2(Reserva r);

/**
 * @brief Get function for the document number of the passenger.
 * @param r Pointer to the reserva struct.
 * @return The document number of the passenger.
 */
Passageiro get_reserva_document_number(Reserva r);

/**
 * @brief Get function for the price of the reserva.
 * @param r Pointer to the reserva struct.
 * @return The price of the reserva.
 */
int get_reserva_price(Reserva r);

/**
 * @brief Set function for the reserva ID.
 * @param r Pointer to the reserva struct.
 * @param reservation_id The new reserva ID to set.
 */
void set_reserva_id(Reserva r, char *reservation_id);

/**
 * @brief Set the first flight id (resolves to Voo via gestor_voos).
 * @param r Pointer to the Reserva.
 * @param flight_id1 Flight id string to set.
 * @param g_voos Pointer to the flights manager used to resolve the id.
 * @return void
 */
void set_reserva_flights_id1(Reserva r, char *flight_id1, Gestor_Voos g_voos);

/**
 * @brief Set the second flight id (resolves to Voo via gestor_voos).
 * @param r Pointer to the Reserva.
 * @param flight_id2 Flight id string to set.
 * @param g_voos Pointer to the flights manager used to resolve the id.
 * @return void
 */
void set_reserva_flights_id2(Reserva r, char *flight_id2, Gestor_Voos g_voos);

/**
 * @brief Set function for the document number of the passenger.
 * @param r Pointer to the reserva struct.
 * @param document_number The new document number to set.
 */
void set_reserva_document_number(Reserva r, int document_number, Gestor_Passageiros g_passageiros);

/**
 * @brief Set function for the price of the reserva.
 * @param r Pointer to the reserva struct.
 * @param price The new price to set.
 */
void set_reserva_price(Reserva r, int price);

#endif