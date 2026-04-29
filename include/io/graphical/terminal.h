#ifndef TERMINAL_H
#define TERMINAL_H

#include <ncurses.h>


/**
 * @brief Opaque type representing the UI terminal/viewport (uses ncurses).
 * The internal structure is opaque to API users. All operations must be
 * performed through the functions below.
 */
typedef struct terminal Terminal;

/**
 * @brief Initialize a Terminal associated with the provided ncurses WINDOW.
 * @param window Pointer to a WINDOW already created by the caller.
 * @return Pointer to a newly allocated Terminal.
 */
Terminal* initialize_terminal(WINDOW* window);

/**
 * @brief Free all resources associated with the Terminal.
 * @param terminal Pointer to the Terminal to free.
 */
void free_terminal(Terminal* terminal);

/**
 * @brief Return the width of the terminal area.
 * @param terminal Pointer to the Terminal.
 * @return Width in columns, or -1 if terminal is NULL.
 */
int get_terminal_width(Terminal* terminal);

/**
 * @brief Return the height of the terminal area.
 * @param terminal Pointer to the Terminal.
 * @return Height in rows, or -1 if terminal is NULL.
 */
int get_terminal_height(Terminal* terminal);

/**
 * @brief Access the main WINDOW* managed by the Terminal.
 * @param terminal Pointer to the Terminal.
 * @return WINDOW* managed by the Terminal.
 */
WINDOW* get_main_window(Terminal* terminal);

#endif // TERMINAL_H