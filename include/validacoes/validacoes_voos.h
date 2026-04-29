#ifndef VALIDACOES_VOOS_H
#define VALIDACOES_VOOS_H

#include <stdio.h>
#include "gestor_entidades/gestor_aeronaves.h"
#include "gestor_entidades/gestor_aeroportos.h"
#include "entidades/voos.h"

/**
 * @brief Validates all fields of a flight record and writes an error to a file if invalid.
 * @param f_erros_voos File where validation errors will be written.
 * @param line Original CSV line.
 * @param voo_id Flight identifier.
 * @param voo_departure Scheduled departure date/time string.
 * @param voo_actual_departure Actual departure date/time string.
 * @param voo_arrival Scheduled arrival date/time string.
 * @param voo_actual_arrival Actual arrival date/time string.
 * @param voo_estado Flight status (voo_status).
 * @param voo_origin IATA code of the origin airport.
 * @param voo_destination IATA code of the destination airport.
 * @param voo_aircraft Aircraft identifier associated with the flight.
 * @param g_aeronaves Aircraft manager used to validate the aircraft id.
 * @param g_aeroportos Airports manager used to validate airport codes.
 * @return 1 if the flight record is valid, 0 otherwise (and an error is written to f_erros_voos).
 */
int valida_voo(FILE *f_erros_voos, char *line, char *voo_id, char *voo_departure, char *voo_actual_departure, char *voo_arrival, char *voo_actual_arrival, voo_status voo_estado, char *voo_origin, char *voo_destination, char *voo_aircraft, Gestor_Aeronaves g_aeronaves, Gestor_Aeroportos g_aeroportos);

/**
 * @brief Checks logically that origin and destination are different.
 * @param origem IATA code of the origin airport.
 * @param destino IATA code of the destination airport.
 * @return 1 if origin != destination, 0 if they are equal.
 */
int valida_logica_voo_dest(char *origem, char *destino);

/**
 * @brief Compares two datetime strings in the project's expected format.
 * @param departure Departure datetime string.
 * @param arrival Arrival datetime string.
 * @return positive if departure > arrival, negative if departure < arrival, 0 if equal.
 */
int compare_datas(char *departure, char *arrival);

/**
 * @brief Checks if an aircraft identifier exists in the aircraft manager.
 * @param id Aircraft identifier to validate.
 * @param g_aeronaves Aircraft manager where to look up the id.
 * @return 1 if the aircraft exists, 0 otherwise.
 */
int valida_aircraft_id(char *id, Gestor_Aeronaves g_aeronaves);

/**
 * @brief Validates rules specific to cancelled flights.
 * @param estado Flight status.
 * @param actual_departure actual_departure string from the record.
 * @param actual_arrival actual_arrival string from the record.
 * @return 1 if valid, 0 otherwise.
 */
int valida_logica_voo_cancelado(voo_status estado, char *actual_departure, char *actual_arrival);

/**
 * @brief Validates rules specific to delayed flights (DELAYED).
 * @param estado Flight status.
 * @param departure Scheduled departure datetime.
 * @param arrival Scheduled arrival datetime.
 * @param actual_departure Actual departure datetime.
 * @param actual_arrival Actual arrival datetime.
 * @return 1 if valid or 0 if invalid.
 */
int valida_logica_voo_atrasado(voo_status estado, char *departure, char *arrival, char *actual_departure, char *actual_arrival);

/**
 * @brief Validates that origin and destination airport codes exist in the airports manager.
 * @param origin IATA code of the origin airport.
 * @param destination IATA code of the destination airport.
 * @param g_aeroportos Airports manager to check against.
 * @return 1 if both exist, 0 if any does not exist.
 */
int valida_aeroportos_ids(char *origin, char *destination, Gestor_Aeroportos g_aeroportos);

#endif // VALIDACOES_VOOS_H
