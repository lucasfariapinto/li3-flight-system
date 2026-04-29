#include "io/graphical/terminal.h"
#include <stdlib.h>
#include <locale.h> // suportar caracteres especiais

struct terminal
{
    int y_max;
    int x_max;
    WINDOW *main_window;
};

Terminal *initialize_terminal(WINDOW *window)
{
    setlocale(LC_ALL, ""); // Configurar locale para suportar caracteres especiais

    Terminal *terminal = malloc(sizeof(Terminal));
    terminal->main_window = window;
    getmaxyx(window, terminal->y_max, terminal->x_max);
    return terminal;
}

void free_terminal(Terminal *terminal)
{
    if (terminal)
        free(terminal);
}

/* Para já nao utilizei esta funçao ja que get_terminal_width e get_terminal_height atualizam as dimensoes
// Atualizar dimensões (chamar quando necessário)
void update_terminal_size(Terminal* terminal) {
    if (terminal && terminal->main_window) {
        getmaxyx(terminal->main_window, terminal->y_max, terminal->x_max);
    }
}
*/
int get_terminal_width(Terminal *terminal)
{
    if (terminal && terminal->main_window)
    {
        getmaxyx(terminal->main_window, terminal->y_max, terminal->x_max);
    }
    return terminal->x_max;
}

int get_terminal_height(Terminal *terminal)
{
    // Atualizar dimensões antes de retornar
    if (terminal && terminal->main_window)
    {
        getmaxyx(terminal->main_window, terminal->y_max, terminal->x_max);
    }
    return terminal->y_max;
}

WINDOW *get_main_window(Terminal *terminal)
{
    return terminal->main_window;
}