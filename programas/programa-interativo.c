#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <sys/stat.h>
#include <unistd.h>

#include "gestor_entidades/gestor.h"
#include "io/graphical/terminal.h"
#include "io/graphical/ui.h"
#include "io/parsers/aeronaves_parser.h"
#include "io/parsers/aeroportos_parser.h"
#include "io/parsers/parser.h"
#include "io/parsers/passageiros_parser.h"
#include "io/parsers/reservas_parser.h"
#include "io/parsers/voos_parser.h"
#include "queries/query1.h"
#include "queries/query2.h"
#include "queries/query3.h"
#include "queries/query4.h"
#include "queries/query5.h"
#include "queries/query6.h"
#include "validacoes/validacoes.h"
#include "gestor_entidades/gestor_reservas.h"
#include "utils/utils.h"

typedef struct
{
    char dataset_path[256];
    int data_loaded;
    Gestor_Global g_global;
} AppState;

void draw_header(Terminal *term)
{
    WINDOW *win = get_main_window(term);
    int width = get_terminal_width(term);

    wattron(win, COLOR_PAIR(2) | A_BOLD);
    mvwprintw(win, 1, (width - 50) / 2,
              "╔════════════════════════════════════════════════╗");
    mvwprintw(win, 2, (width - 50) / 2,
              "║     Sistema de Gestão de Voos e Aeroportos     ║");
    mvwprintw(win, 3, (width - 50) / 2,
              "╚════════════════════════════════════════════════╝");
    wattroff(win, COLOR_PAIR(2) | A_BOLD);

    wrefresh(win);
}

int load_datasets(AppState *state, Terminal *term)
{
    int height = get_terminal_height(term);
    int width = get_terminal_width(term);
    WINDOW *win = get_main_window(term);

    // --- CÁLCULO PARA CENTRAR ---
    // A tua linha separadora tem +- 39 caracteres. Vamos usar 40 como referência.
    int content_width = 40;
    int start_x = (width - content_width) / 2;
    if (start_x < 0)
        start_x = 0; // Proteção para ecrãs muito pequenos
    // ----------------------------

    Vector pos = create_vector(height / 2, width / 2 - 30);
    char input[256] = "";

    // ... (parte do input box mantém-se igual) ...
    if (text_input_box(pos, 60, 255, "Caminho para o dataset", input, 1))
    {
        free(pos);
        return 0;
    }

    if (strlen(input) == 0)
    {
        free(pos);
        modal_error("Caminho não pode estar vazio!", 40, height, width);
        return 0;
    }

    struct stat st;
    if (stat(input, &st) != 0 || !S_ISDIR(st.st_mode))
    {
        free(pos);
        modal_error("Caminho inválido ou não existe!", 45, height, width);
        return 0;
    }

    strcpy(state->dataset_path, input);

    clear();
    draw_header(term);

    int current_line = 8; // Podes ajustar a altura se quiseres mais abaixo

    // AQUI USAMOS O start_x EM VEZ DE 5
    wattron(win, COLOR_PAIR(2) | A_BOLD);
    mvwprintw(win, current_line++, start_x, "═══════════════════════════════════════"); // <--- ALTERADO
    mvwprintw(win, current_line++, start_x, "    CARREGAMENTO DE DATASETS");            // <--- ALTERADO
    mvwprintw(win, current_line++, start_x, "═══════════════════════════════════════"); // <--- ALTERADO
    wattroff(win, COLOR_PAIR(2) | A_BOLD);
    current_line++;
    wrefresh(win);

    if (state->g_global != NULL)
    {
        free_gestor_global(state->g_global);
        state->g_global = NULL;
    }

    state->g_global = initialize_gestor_global();
    if (!state->g_global)
    {
        modal_error("Erro ao inicializar gestor!", 40, height, width);
        free(pos);
        return 0;
    }

    int sucesso = 1;
    char erro_msg[100] = "";

    // ===== AEROPORTOS =====
    wattron(win, COLOR_PAIR(3) | A_BOLD);
    mvwprintw(win, current_line++, start_x, "➤ Aeroportos..."); // <--- ALTERADO
    wattroff(win, COLOR_PAIR(3) | A_BOLD);
    wrefresh(win);

    aeroportos_parser(state->dataset_path, 1, state->g_global);

    if (get_gestor_aeroportos(state->g_global) == NULL)
    {
        sucesso = 0;
        strcpy(erro_msg, "Erro ao carregar aeroportos!");
        wattron(win, COLOR_PAIR(1) | A_BOLD);
        mvwprintw(win, current_line++, start_x, "✗ FALHOU!"); // <--- ALTERADO
        wattroff(win, COLOR_PAIR(1) | A_BOLD);
    }
    else
    {
        wattron(win, COLOR_PAIR(2) | A_BOLD);
        mvwprintw(win, current_line - 1, start_x, "✓ Aeroportos concluído"); // <--- ALTERADO
        wattroff(win, COLOR_PAIR(2) | A_BOLD);
    }
    current_line++;
    wrefresh(win);

    // ===== AERONAVES =====
    if (sucesso)
    {
        wattron(win, COLOR_PAIR(3) | A_BOLD);
        mvwprintw(win, current_line++, start_x, "➤ Aeronaves..."); // <--- ALTERADO
        wattroff(win, COLOR_PAIR(3) | A_BOLD);
        wrefresh(win);

        aeronaves_parser(state->dataset_path, 1, state->g_global);

        if (get_gestor_aeronaves(state->g_global) == NULL)
        {
            sucesso = 0;
            strcpy(erro_msg, "Erro ao carregar aeronaves!");
            wattron(win, COLOR_PAIR(1) | A_BOLD);
            mvwprintw(win, current_line++, start_x, "✗ FALHOU!"); // <--- ALTERADO
            wattroff(win, COLOR_PAIR(1) | A_BOLD);
        }
        else
        {
            wattron(win, COLOR_PAIR(2) | A_BOLD);
            mvwprintw(win, current_line - 1, start_x, "✓ Aeronaves concluído"); // <--- ALTERADO
            wattroff(win, COLOR_PAIR(2) | A_BOLD);
        }
        current_line++;
        wrefresh(win);
    }

    // ===== VOOS =====
    if (sucesso)
    {
        wattron(win, COLOR_PAIR(3) | A_BOLD);
        mvwprintw(win, current_line++, start_x, "➤ Voos..."); // <--- ALTERADO
        wattroff(win, COLOR_PAIR(3) | A_BOLD);
        wrefresh(win);

        voos_parser(state->dataset_path, 1, state->g_global);

        if (get_gestor_voos(state->g_global) == NULL)
        {
            sucesso = 0;
            strcpy(erro_msg, "Erro ao carregar voos!");
            wattron(win, COLOR_PAIR(1) | A_BOLD);
            mvwprintw(win, current_line++, start_x, "✗ FALHOU!"); // <--- ALTERADO
            wattroff(win, COLOR_PAIR(1) | A_BOLD);
        }
        else
        {
            wattron(win, COLOR_PAIR(2) | A_BOLD);
            mvwprintw(win, current_line - 1, start_x, "✓ Voos concluído"); // <--- ALTERADO
            wattroff(win, COLOR_PAIR(2) | A_BOLD);
        }
        current_line++;
        wrefresh(win);
    }

    // ===== PASSAGEIROS =====
    if (sucesso)
    {
        wattron(win, COLOR_PAIR(3) | A_BOLD);
        mvwprintw(win, current_line++, start_x, "➤ Passageiros..."); // <--- ALTERADO
        wattroff(win, COLOR_PAIR(3) | A_BOLD);
        wrefresh(win);

        passageiros_parser(state->dataset_path, 1, state->g_global);

        if (get_gestor_passageiros(state->g_global) == NULL)
        {
            sucesso = 0;
            strcpy(erro_msg, "Erro ao carregar passageiros!");
            wattron(win, COLOR_PAIR(1) | A_BOLD);
            mvwprintw(win, current_line++, start_x, "✗ FALHOU!"); // <--- ALTERADO
            wattroff(win, COLOR_PAIR(1) | A_BOLD);
        }
        else
        {
            wattron(win, COLOR_PAIR(2) | A_BOLD);
            mvwprintw(win, current_line - 1, start_x, "✓ Passageiros concluído"); // <--- ALTERADO
            wattroff(win, COLOR_PAIR(2) | A_BOLD);
        }
        current_line++;
        wrefresh(win);
    }

    // ===== RESERVAS =====
    if (sucesso)
    {
        wattron(win, COLOR_PAIR(3) | A_BOLD);
        mvwprintw(win, current_line++, start_x, "➤ Reservas..."); // <--- ALTERADO
        wattroff(win, COLOR_PAIR(3) | A_BOLD);
        wrefresh(win);

        reserva_parser(state->dataset_path, 1, state->g_global);

        if (get_gestor_reservas(state->g_global) == NULL)
        {
            sucesso = 0;
            strcpy(erro_msg, "Erro ao carregar reservas!");
            wattron(win, COLOR_PAIR(1) | A_BOLD);
            mvwprintw(win, current_line++, start_x, "✗ FALHOU!"); // <--- ALTERADO
            wattroff(win, COLOR_PAIR(1) | A_BOLD);
        }
        else
        {
            wattron(win, COLOR_PAIR(2) | A_BOLD);
            mvwprintw(win, current_line - 1, start_x, "✓ Reservas concluído"); // <--- ALTERADO
            wattroff(win, COLOR_PAIR(2) | A_BOLD);
        }
        current_line++;
        wrefresh(win);
    }

    // Resultado final
    if (!sucesso)
    {
        napms(1500);

        current_line++;
        wattron(win, COLOR_PAIR(1) | A_BOLD);
        mvwprintw(win, current_line++, start_x, "═══════════════════════════════════════"); // <--- ALTERADO
        mvwprintw(win, current_line++, start_x, "✗ ERRO: %s", erro_msg);                    // <--- ALTERADO
        mvwprintw(win, current_line++, start_x, "═══════════════════════════════════════"); // <--- ALTERADO
        wattroff(win, COLOR_PAIR(1) | A_BOLD);
        wrefresh(win);
        napms(2000);

        if (state->g_global)
        {
            free_gestor_global(state->g_global);
            state->g_global = NULL;
        }

        state->data_loaded = 0;
        state->dataset_path[0] = '\0';

        modal_error(erro_msg, 50, height, width);
        free(pos);
        return 0;
    }

    // Sucesso!
    current_line++;
    wattron(win, COLOR_PAIR(2) | A_BOLD);
    mvwprintw(win, current_line++, start_x, "═══════════════════════════════════════"); // <--- ALTERADO
    mvwprintw(win, current_line++, start_x, "✓ TODOS OS DATASETS CARREGADOS!");         // <--- ALTERADO
    mvwprintw(win, current_line++, start_x, "═══════════════════════════════════════"); // <--- ALTERADO
    wattroff(win, COLOR_PAIR(2) | A_BOLD);
    wrefresh(win);

    napms(1500);
    state->data_loaded = 1;
    modal_ok("Datasets carregados com sucesso!", 40, height, width);
    free(pos);

    return 1;
}

void execute_query_interactive(AppState *state, Terminal *term)
{
    if (!state->data_loaded)
    {
        modal_error("Por favor carregue os datasets primeiro!", 45,
                    get_terminal_height(term), get_terminal_width(term));
        return;
    }

    int height = get_terminal_height(term);
    int width = get_terminal_width(term);

    // PASSO 1: Escolher a query
    char *query_options[] = {"Query 1 - Informação de Aeroporto",
                             "Query 2 - Top N Aeronaves por Voos",
                             "Query 3 - Aeroporto com Mais Partidas",
                             "Query 4 - Passageiro Mais Vezes no Top 10",
                             "Query 5 - Top N Companhias por Atraso",
                             "Query 6 - Aeroporto Mais Popular",
                             "Voltar"};

    int query_choice = menu_select(7, query_options, 60, 8, (width - 60) / 2);

    if (query_choice == 6)
        return;

    // PASSO 2: Escolher formato (Normal ou S)
    char *format_options[] = {
        "Formato Normal (separador: ;)",
        "Formato S (separador: =)",
        "Voltar"};

    int format_choice = menu_select(3, format_options, 60, 8, (width - 60) / 2);

    if (format_choice == 2)
        return;

    // Determinar separador baseado na escolha
    char separator = (format_choice == 0) ? ';' : '=';

    Vector pos = create_vector(height / 2, width / 2 - 30);
    char args[256] = "";
    char *result = NULL;
    switch (query_choice)
    {
    case 0:
    {
        if (text_input_box(pos, 60, 255, "Código do aeroporto (ex: LIS)",
                           args, 1))
        {
            free(pos);
            return;
        }

        char *arg_ptr = args;
        // aeroporto existe
        if (get_aeroporto(get_gestor_aeroportos(state->g_global), arg_ptr) == NULL)
        {
            modal_error("Aeroporto não existe!", 30, height, width);
            free(pos);
            return;
        }
        result = query1(&arg_ptr, get_gestor_aeroportos(state->g_global), separator);

        break;
    }
    case 1:
    {
        if (text_input_box(pos, 60, 255, "N [fabricante] (ex: 5 Boeing)", args, 1))
        {
            free(pos);
            return;
        }

        char *arg_ptr = args;
        char *dup = strdup(arg_ptr);
        char *init = dup;
        char *N = parse_string(&dup, ' ');
        // verificar se N é um numero
        if (!N || N[0] == '\0' || !is_number(N))
        {
            modal_error("N deve ser um número!", 30, height, width);
            free(pos);
            free(init);
            return;
        }
        result = query2(&arg_ptr, get_gestor_aeronaves(state->g_global), separator);
        free(init);
        break;
    }
    case 2:
    {
        if (text_input_box(pos, 70, 255,
                           "Datas (YYYY-MM-DD YYYY-MM-DD)",
                           args, 1))
        {
            free(pos);
            return;
        }

        char *arg_ptr = args;
        char data1[11], data2[11];

        // separar as datas para testar
        if (*arg_ptr != '\0')
        { // 2025-03-25 2025-03-30

            // primeira data
            for (int i = 0; i < 10; i++)
                data1[i] = arg_ptr[i];
            data1[10] = '\0';

            // segunda data
            for (int i = 0, j = 11; i < 10; i++, j++)
                data2[i] = arg_ptr[j];
            data2[10] = '\0';
        }

        // testar as datas
        if (*arg_ptr == '\0' || !verifica_data(data1) || !verifica_data(data2))
        {
            modal_error("Datas inválidas!", 30, height, width);
            free(pos);
            return;
        }
        result = query3(&arg_ptr, get_gestor_aeroportos(state->g_global), separator);

        break;
    }
    case 3:
    {
        if (text_input_box(pos, 70, 255, "Datas (YYYY-MM-DD YYYY-MM-DD)", args, 1))
        {
            free(pos);
            return;
        }

        char *arg_ptr = args;
        char data1[11], data2[11];

        // separar as datas para testar
        if (*arg_ptr != '\0')
        { // 2025-03-25 2025-03-30

            // primeira data
            for (int i = 0; i < 10; i++)
                data1[i] = arg_ptr[i];
            data1[10] = '\0';

            // segunda data
            for (int i = 0, j = 11; i < 10; i++, j++)
                data2[i] = arg_ptr[j];
            data2[10] = '\0';

            // testar as datas
            if (!verifica_data(data1))
            {
                modal_error("Primeira data inválida!", 30, height, width);
                free(pos);
                return;
            }
            if (!verifica_data(data2))
            {
                modal_error("Segunda data invalida!", 30, height, width);
                free(pos);
                return;
            }
        }
        result = query4(&arg_ptr, get_gestor_passageiros(state->g_global), separator);

        break;
    }
    case 4:
    {
        if (text_input_box(pos, 60, 255,
                           "N (ex: 10)",
                           args, 1))
        {
            free(pos);
            return;
        }

        char *arg_ptr = args;
        if (!is_number(arg_ptr))
        {
            modal_error("N deve ser um número!", 30, height, width);
            free(pos);
            return;
        }
        result = query5(&arg_ptr, get_gestor_voos(state->g_global), separator);

        break;
    }
    case 5:
    {
        if (text_input_box(pos, 60, 255, "Nacionalidade (ex: France)", args, 1))
        {
            free(pos);
            return;
        }

        char *arg_ptr = args;
        // verificar se a nacionalidade existe
        if (get_nacionalidade(get_gestor_reservas(state->g_global), arg_ptr, get_string_pool(state->g_global)) == -1)
        {
            modal_error("Nacionalidade sem passageiros!", 35, height, width);
            free(pos);
            return;
        }
        result = query6(&arg_ptr, get_gestor_reservas(state->g_global), separator, get_string_pool(state->g_global));

        break;
    }
    }
    display_results(result, height, width);
    free(pos);
    free(result);
}

int main_menu(AppState *state, Terminal *term)
{
    // int height = get_terminal_height(term);
    int width = get_terminal_width(term);

    char *main_options[] = {"Carregar Datasets", "Executar Query", "Sair"};

    clear();
    draw_header(term);

    if (state->data_loaded)
    {
        wattron(get_main_window(term), COLOR_PAIR(2));
        mvwprintw(get_main_window(term), 5, 5, "✓ Dataset carregado: %s",
                  state->dataset_path);
        wattroff(get_main_window(term), COLOR_PAIR(2));
    }
    else
    {
        wattron(get_main_window(term), A_DIM);
        mvwprintw(get_main_window(term), 5, 5, "⚠ Nenhum dataset carregado");
        wattroff(get_main_window(term), A_DIM);
    }

    refresh();

    return menu_select(3, main_options, 50, 8, (width - 50) / 2);
}

int main()
{
    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);     // Erros
        init_pair(2, COLOR_GREEN, COLOR_BLACK);   // Sucesso
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);  // Loading
        init_pair(4, COLOR_CYAN, COLOR_BLACK);    // Info
        init_pair(5, COLOR_MAGENTA, COLOR_BLACK); // Destaque
        init_pair(6, COLOR_BLUE, COLOR_BLACK);    // Output dos parsers
    }

    Terminal *term = initialize_terminal(stdscr);

    AppState state = {.data_loaded = 0, .g_global = NULL};

    int running = 1;
    while (running)
    {
        int choice = main_menu(&state, term);

        switch (choice)
        {
        case 0:
            load_datasets(&state, term);
            break;
        case 1:
            execute_query_interactive(&state, term);
            break;
        case 2:
            running = 0;
            break;
        }
    }

    if (state.data_loaded)
    {
        free_gestor_global(state.g_global);
    }

    free_terminal(term);
    endwin();

    return 0;
}