#ifndef GESTOR_PASSAGEIROS_H
#define GESTOR_PASSAGEIROS_H

#include <stdlib.h>
#include "entidades/passageiros.h"
#include <glib.h>

/**
 * @brief Struct that manages all passageiros records
 */
typedef struct gestor_passageiros *Gestor_Passageiros;

/**
 * @brief Initializes the passageiro manager
 * @return Pointer to the initialized passageiro manager
 */
Gestor_Passageiros initialize_gestor_passageiros();

/**
 * @brief Frees the memory allocated for the passageiro manager
 * @param gestor Pointer to the passageiro manager to be freed
 */
void free_gestor_passageiros(Gestor_Passageiros gestor);

/**
 * @brief Inserts a passageiro into the manager
 * @param gestor Pointer to the passageiro manager
 * @param document_number Integer document number used as key
 * @param p Pointer to the Passageiro structure to store
 */
void insert_passageiro(Gestor_Passageiros gestor, int document_number, Passageiro p);

/**
 * @brief Checks if a passageiro exists in the manager
 * @param g Pointer to the passageiro manager
 * @param code Document number to check
 * @return 1 if the passageiro exists, 0 otherwise
 */
int passageiro_exists(Gestor_Passageiros g, int code);

/**
 * @brief Retrieve a passageiro by document number.
 * @param g Pointer to the Gestor_Passageiros.
 * @param code Document number of the passageiro.
 * @return Pointer to the Passageiro if found, or NULL if not present.
 */
Passageiro get_passageiro(Gestor_Passageiros g, int code);

/**
 * @brief Record a weekly expense for a passageiro.
 * @param gestor Pointer to the Gestor_Passageiros.
 * @param date Date in YYYYMMDD format.
 * @param document_number Passageiro document number.
 * @param price Expense amount.
 */
void insert_week_expense(Gestor_Passageiros gestor, int date, int document_number, float price);

/**
 * @brief Comparison function used to sort or compare passageiro expenses.
 * @param a Pointer to the first element.
 * @param b Pointer to the second element.
 * @param user_data Optional user data passed through GLib sorting APIs.
 * @return Negative if a < b, zero if equal, positive if a > b.
 */
gint compare_despesa_pessoa(gconstpointer a, gconstpointer b, gpointer user_data);

/**
 * @brief Callback used with g_hash_table_foreach to maintain a top-10 ranking.
 * @param key Document number (int, via gpointer).
 * @param value Expense amount (int, via gpointer).
 * @param user_data Pointer to a GSequence holding DespesaPessoa entries.
 */
void select_top_10(gpointer key, gpointer value, gpointer user_data);

/**
 * @brief Build the top-10 passageiros by some weekly metric.
 * @param g_passageiros Pointer to the Gestor_Passageiros to analyze.
 */
void build_top_10_by_week(Gestor_Passageiros g_passageiros);

/**
 * @brief Compute which passageiro appeared most often in the weekly top-10 across a date range.
 * @param g_passageiros Pointer to the Gestor_Passageiros (must not be NULL).
 * @param init_date Pointer to the end date (inclusive). If NULL, uses the latest available week.
 * @param end_date Pointer to the start date (inclusive). If NULL, uses the earliest available week.
 * @param times_in_top_10 Output pointer that will receive how many times the returned passageiro appeared in the top-10 (must not be NULL).
 * @return Document number of the passageiro that appeared most often in the top-10 within the date range, or -1 if no passenger is found.
 */
int get_most_times_in_top_10(Gestor_Passageiros g_passageiros, int *init_date, int *end_date, int *times_in_top_10);

#endif // GESTOR_PASSAGEIROS_H
