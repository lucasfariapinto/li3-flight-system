#ifndef UI_H
#define UI_H

/**
 * @brief 2D integer vector for UI positions/sizes.
 */
typedef struct vector *Vector;

/**
 * @brief Create a Vector with given y and x components.
 * @param y Y component.
 * @param x X component.
 * @return The created Vector.
 */
Vector create_vector(int y, int x);

/**
 * @brief Display a vertical menu and let the user select an option.
 * @param options Number of options available.
 * @param texts Array of C-strings with the option labels.
 * @param width Width of the menu window in columns.
 * @param y Top row where the menu window should be placed.
 * @param x Left column where the menu window should be placed.
 * @return Index of the selected option.
 */
int menu_select(int options, char *texts[], int width, int y, int x);

/**
 * @brief Show a small input box and capture a single-line text from the user.
 * @param pos Position where the box will be centered.
 * @param width Width of the input box in columns.
 * @param input_size Maximum number of characters the input buffer can hold.
 * @param text Prompt/title text to display in the box.
 * @param input Buffer provided by the caller where the entered text will be stored.
 * @param can_exit If non-zero, allow the user to cancel input with ESC.
 * @return 0 on successful confirm (ENTER), 1 if cancelled (ESC) when can_exit is true.
 */
int text_input_box(Vector pos, int width, int input_size, char *text, char *input, int can_exit);

/**
 * @brief Show a modal dialog with a single "OK" acknowledgement.
 * @param text Message text to display.
 * @param width Width of the modal window in columns.
 * @param screen_y_max Terminal height in rows.
 * @param screen_x_max Terminal width in columns.
 */
void modal_ok(char text[], int width, int screen_y_max, int screen_x_max);

/**
 * @brief Show a modal error dialog with a highlighted error header and "OK".
 * @param text Error message to display.
 * @param width Width of the modal window in columns.
 * @param screen_y_max Terminal height in rows.
 * @param screen_x_max Terminal width in columns.
 */
void modal_error(char text[], int width, int screen_y_max, int screen_x_max);

/**
 * @brief Display a multi-line results buffer in a scrollable window.
 * @param file_path Buffer containing the results text with '\n' separated lines.
 * @param screen_y_max Terminal height in rows.
 * @param screen_x_max Terminal width in columns.
 */
void display_results(char *file_path, int screen_y_max, int screen_x_max);

/**
 * @brief Count newline characters in a C-string.
 * @param text Input null-terminated string.
 * @return Number of '\n' characters found.
 */
int get_newlines(char text[]);

#endif