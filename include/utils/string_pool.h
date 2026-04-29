#ifndef STRING_POOL_H
#define STRING_POOL_H

#include <stdint.h>

/**
 * @brief Opaque struct representing a string pool.
 */
typedef struct string_pool *String_Pool;

/**
 * @brief Initializes a new string pool.
 * @return A pointer to the newly created StringPool struct.
 */
String_Pool initialize_string_pool();

/**
 * @brief Frees the memory allocated for a StringPool struct and its contents.
 * @param sp Pointer to the StringPool struct to be freed.
 */
void free_string_pool(String_Pool sp);

/**
 * @brief Inserts a string into the string pool if it doesn't already exist.
 * @param s The string to be inserted.
 * @param sp The string pool.
 * @return A pointer to the interned string in the pool.
 */
const char *insert_string_in_pool(char const *s, String_Pool sp);

/**
 * @brief Updates the pointer value to obfuscate the actual memory address
 * @param ptr The original string pointer.
 * @return An obfuscated uintptr_t value representing the string pointer. The value returned is treated as a unique number for each distinct string.
 */
uintptr_t pointer_to_num(const char *ptr);

/**
 * @brief Converts an obfuscated uintptr_t value back to the original string pointer.
 * @param obfuscated_id The obfuscated uintptr_t value.
 * @return The original string pointer but with const char* type to prevent modification.
 */
const char *num_to_const_ptr(uintptr_t obfuscated_id);

/**
 * @brief Retrieves a copy of the string from the pool.
 * @param s The string pointer from the pool.
 * @return A newly allocated copy of the string.
 */
char *get_string_from_pool(const char *s);

#endif // STRING_POOL_H
