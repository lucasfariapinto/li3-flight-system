#include "io/graphical/ui.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

struct vector
{
    int y;
    int x;
};

Vector create_vector(int y, int x)
{
    Vector v = malloc(sizeof(struct vector));
    v->y = y;
    v->x = x;
    return v;
}

int menu_select(int options, char *texts[], int width, int y, int x)
{
    int selection = 0, key = 0;
    int lines = options + 4;

    WINDOW *select_window = newwin(lines, width, y, x);

    keypad(select_window, TRUE);
    noecho();
    curs_set(0);

    box(select_window, 0, 0);
    wrefresh(select_window); // REMOVER refresh() global

    while (key != 10)
    {
        // Limpar área de conteúdo
        for (int i = 1; i < lines - 1; i++)
        {
            mvwhline(select_window, i, 1, ' ', width - 2);
        }

        wattron(select_window, A_DIM);
        mvwprintw(select_window, 1, 2, "Use [↑/↓] to navigate, [ENTER] to select:");
        wattroff(select_window, A_DIM);

        for (int i = 0; i < options; i++)
        {
            if (i == selection)
            {
                mvwprintw(select_window, i + 3, 3, "> "); // Usar > em vez de ▶
                wattron(select_window, A_BOLD | COLOR_PAIR(2));
                wprintw(select_window, "%s", texts[i]);
                wattroff(select_window, A_BOLD | COLOR_PAIR(2));
            }
            else
            {
                mvwprintw(select_window, i + 3, 3, "  %s", texts[i]);
            }
        }

        box(select_window, 0, 0); // Redesenhar borda
        wrefresh(select_window);

        key = wgetch(select_window);

        switch (key)
        {
        case KEY_UP:
            selection = (selection > 0) ? selection - 1 : options - 1;
            break;
        case KEY_DOWN:
            selection = (selection < options - 1) ? selection + 1 : 0;
            break;
        }
    }

    wclear(select_window);
    wrefresh(select_window);
    delwin(select_window);
    return selection;
}

int text_input_box(Vector pos, int width, int input_size, char *text, char *input, int can_exit)
{
    if (can_exit && width < 32)
    {
        pos->x = pos->x + width / 2 - (32 / 2);
        width = 32;
    }

    pos->y -= 3;

    WINDOW *input_window = newwin(6, width, pos->y, pos->x);
    box(input_window, 0, 0);
    refresh();
    wrefresh(input_window);

    wattron(input_window, COLOR_PAIR(2));
    mvwprintw(input_window, 0, 2, "%s", text);
    wattroff(input_window, COLOR_PAIR(2));

    mvwprintw(input_window, 3, 1, "➤");

    wattron(input_window, A_DIM);
    if (can_exit)
    {
        mvwprintw(input_window, 4, 1, "[ENTER] Confirm • [ESC] Cancel");
    }
    else
    {
        mvwprintw(input_window, 4, 1, "[ENTER] Confirm");
    }
    wattroff(input_window, A_DIM);

    int cursor = 0;
    int ch;

    wmove(input_window, 3, 3);
    curs_set(1);

    while ((ch = wgetch(input_window)) != '\n' && cursor < input_size - 1)
    {
        if (can_exit && ch == 27)
        {
            wclear(input_window);
            wrefresh(input_window);
            delwin(input_window);
            curs_set(0);
            return 1;
        }
        else if (ch == KEY_BACKSPACE || ch == 127)
        {
            if (cursor > 0)
            {
                cursor--;
                input[cursor] = ' ';
                mvwprintw(input_window, 3, 3, "%s", input);
                input[cursor] = '\0';
                wmove(input_window, 3, 3 + cursor);
                wrefresh(input_window);
            }
        }
        else if (ch >= 32 && ch <= 126)
        {
            input[cursor] = ch;
            input[cursor + 1] = '\0';
            mvwprintw(input_window, 3, 3, "%s", input);
            cursor++;
            wmove(input_window, 3, 3 + cursor);
            wrefresh(input_window);
        }
    }

    curs_set(0);
    wclear(input_window);
    wrefresh(input_window);
    delwin(input_window);
    return 0;
}

void modal_ok(char text[], int width, int screen_y_max, int screen_x_max)
{
    int key = 0;
    int necessary_lines = get_newlines(text) + 1 + 4;
    int posY = (screen_y_max - necessary_lines) / 2;
    int posX = (screen_x_max - width) / 2;

    WINDOW *modal_window = newwin(necessary_lines, width, posY, posX);
    box(modal_window, 0, 0);
    refresh();
    wrefresh(modal_window);
    keypad(modal_window, true);

    mvwprintw(modal_window, 1, 2, "%s", text);

    wattron(modal_window, COLOR_PAIR(2));
    mvwprintw(modal_window, necessary_lines - 2, width - 4, "OK");
    wattroff(modal_window, COLOR_PAIR(2));

    while (key != 10)
    {
        key = wgetch(modal_window);
    }

    wclear(modal_window);
    wrefresh(modal_window);
    delwin(modal_window);
}

void modal_error(char text[], int width, int screen_y_max, int screen_x_max)
{
    int key = 0;
    int necessary_lines = get_newlines(text) + 1 + 4;
    int posY = (screen_y_max - necessary_lines) / 2;
    int posX = (screen_x_max - width) / 2;

    WINDOW *modal_window = newwin(necessary_lines, width, posY, posX);
    box(modal_window, 0, 0);
    refresh();
    wrefresh(modal_window);
    keypad(modal_window, true);

    wattron(modal_window, COLOR_PAIR(1));
    mvwprintw(modal_window, 0, 2, " ERROR ");
    wattroff(modal_window, COLOR_PAIR(1));

    mvwprintw(modal_window, 2, 2, "%s", text);

    wattron(modal_window, COLOR_PAIR(1));
    mvwprintw(modal_window, necessary_lines - 2, width - 4, "OK");
    wattroff(modal_window, COLOR_PAIR(1));

    while (key != 10)
    {
        key = wgetch(modal_window);
    }

    wclear(modal_window);
    wrefresh(modal_window);
    delwin(modal_window);
}

void display_results(char *result_text, int screen_y_max, int screen_x_max)
{
    if (!result_text)
    {
        modal_error("Erro: resultado nulo", 50, screen_y_max, screen_x_max);
        return;
    }

    int width = screen_x_max - 10;
    int height = screen_y_max - 10;
    int posY = 5;
    int posX = 5;

    WINDOW *results_window = newwin(height, width, posY, posX);
    box(results_window, 0, 0);

    wattron(results_window, COLOR_PAIR(2) | A_BOLD);
    mvwprintw(results_window, 0, 2, " Resultados ");
    wattroff(results_window, COLOR_PAIR(2) | A_BOLD);

    keypad(results_window, true);

    //  Dividir a string em linhas
    char **lines = malloc(1000 * sizeof(char *));
    int line_count = 0;

    //  Fazer uma cópia da string para poder modificar
    char *text_copy = strdup(result_text);
    char *line = strtok(text_copy, "\n");

    while (line != NULL && line_count < 1000)
    {
        lines[line_count] = strdup(line);
        line_count++;
        line = strtok(NULL, "\n");
    }

    free(text_copy);

    // Se não há resultados
    if (line_count == 0 || (line_count == 1 && strlen(lines[0]) == 0))
    {
        wclear(results_window);
        box(results_window, 0, 0);
        wattron(results_window, COLOR_PAIR(1) | A_BOLD);
        mvwprintw(results_window, 0, 2, " Resultados ");
        wattroff(results_window, COLOR_PAIR(1) | A_BOLD);

        mvwprintw(results_window, height / 2, (width - 20) / 2, "Nenhum resultado encontrado");

        wattron(results_window, A_DIM);
        mvwprintw(results_window, height - 1, 2, "[ESC] Fechar");
        wattroff(results_window, A_DIM);

        wrefresh(results_window);

        int key = 0;
        while (key != 27)
        {
            key = wgetch(results_window);
        }

        for (int i = 0; i < line_count; i++)
        {
            free(lines[i]);
        }
        free(lines);
        delwin(results_window);
        return;
    }

    int scroll = 0;
    int max_display = height - 4;
    int key = 0;

    while (key != 27)
    {
        wclear(results_window);
        box(results_window, 0, 0);

        wattron(results_window, COLOR_PAIR(2) | A_BOLD);
        mvwprintw(results_window, 0, 2, " Resultados ");
        wattroff(results_window, COLOR_PAIR(2) | A_BOLD);

        // Mostrar linhas com truncagem se necessário
        for (int i = 0; i < max_display && (scroll + i) < line_count; i++)
        {
            int line_y = i + 2;
            int max_line_width = width - 4; // Margem de segurança

            // Se a linha é muito longa, truncar
            if ((int)strlen(lines[scroll + i]) > max_line_width)
            {
                char truncated[1024];
                strncpy(truncated, lines[scroll + i], max_line_width - 3);
                truncated[max_line_width - 3] = '\0';
                mvwprintw(results_window, line_y, 2, "%s...", truncated);
            }
            else
            {
                mvwprintw(results_window, line_y, 2, "%s", lines[scroll + i]);
            }
        }

        wattron(results_window, A_DIM);
        mvwprintw(results_window, height - 1, 2, "[↑/↓] Scroll • [ESC] Fechar • Linha %d/%d",
                  scroll + 1, line_count);
        wattroff(results_window, A_DIM);

        wrefresh(results_window);
        key = wgetch(results_window);

        switch (key)
        {
        case KEY_UP:
            if (scroll > 0)
                scroll--;
            break;
        case KEY_DOWN:
            if (scroll < line_count - max_display)
                scroll++;
            break;
        case KEY_PPAGE: // Page Up
            scroll = (scroll > max_display) ? scroll - max_display : 0;
            break;
        case KEY_NPAGE: // Page Down
            scroll = (scroll + max_display < line_count - max_display) ? scroll + max_display : line_count - max_display;
            if (scroll < 0)
                scroll = 0;
            break;
        }
    }

    for (int i = 0; i < line_count; i++)
    {
        free(lines[i]);
    }
    free(lines);

    wclear(results_window);
    wrefresh(results_window);
    delwin(results_window);
}

int get_newlines(char text[])
{
    int newlines = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '\n')
        {
            newlines++;
        }
    }
    return newlines;
}