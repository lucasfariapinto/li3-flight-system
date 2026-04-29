#include <stdio.h>
#include <time.h>
#include <sys/resource.h>

#include "gestor_entidades/gestor_aeroportos.h"
#include "gestor_entidades/gestor_voos.h"
#include "gestor_entidades/gestor_aeronaves.h"
#include "gestor_entidades/gestor_passageiros.h"
#include "gestor_entidades/gestor.h"
#include "io/parsers/passageiros_parser.h"
#include "io/parsers/aeroportos_parser.h"
#include "io/parsers/voos_parser.h"
#include "io/parsers/aeronaves_parser.h"
#include "io/parsers/reservas_parser.h"
#include "io/parsers/parser.h"
#include <sys/stat.h>
#include <sys/resource.h>
#include "queries/interpreter.h"
#include "queries/query1.h"
#include "queries/query2.h"
#include "queries/query3.h"
#include "queries/query4.h"
#include "queries/query5.h"
#include "queries/query6.h"
#include "io/output/output.h"
#include "glib.h"
#include "stdlib.h"
#include "utils/utils.h"
#include "utils/string_pool.h"

// cores em ansi
#define BG_GREEN "\x1b[42m"   // fundo verde
#define BG_RED "\x1b[41m"     // fundo vermelho
#define COLOR_RESET "\x1b[0m" // reset às cores

// Estrutura para guardar as estatísticas dos testes
// Cada tipo de querie tem um em TestStatistics (na primeira fase só existem 3 tipos de queries)
typedef struct test_statistics
{
    GArray *total_queries; // array que contem o número de cada query na sequencia total de queries, mas apenas das queries que teem erros (1,2,3,4,5,6,7,8,9,10, ...). Assim quando se adiciona em \erros também se adiciona aqui o número da query ficando ambas no mesmo index
    GPtrArray *error_line;
    GPtrArray *expected_output;
    int num_queries_tipo;   // quantas queries deste tipo foram feitas
    int successful_queries; // número de queries corretas deste tipo
    double query_time;      // tempo total gasto em queries deste tipo
    GArray *erros;          // array que contem o número da linha do ficheiro de output onde houve erro
} *TestStatistics;

void free_test_statistics(TestStatistics *stats, int number_of_queries)
{
    for (int i = 0; i < number_of_queries; i++)
    {
        g_ptr_array_free(stats[i]->error_line, TRUE);
        g_ptr_array_free(stats[i]->expected_output, TRUE);
        g_array_free(stats[i]->total_queries, TRUE);
        g_array_free(stats[i]->erros, TRUE);
        free(stats[i]);
    }
}

void initialize_test_statistics(TestStatistics *stats, int number_of_queries)
{
    for (int i = 0; i < number_of_queries; i++)
    {
        TestStatistics stat = malloc(sizeof(struct test_statistics));
        stat->total_queries = g_array_new(FALSE, FALSE, sizeof(int));
        stat->error_line = g_ptr_array_new_with_free_func(free);
        stat->expected_output = g_ptr_array_new_with_free_func(free);
        stat->successful_queries = 0;
        stat->num_queries_tipo = 0;
        stat->query_time = 0.0;
        stat->erros = g_array_new(FALSE, FALSE, sizeof(int));
        stats[i] = stat;
    }
}

char *get_different_line(const char *str, int pos)
{
    // encontra o início da linha
    int start = pos;
    while (start > 0 && str[start - 1] != '\n')
    {
        start--;
    }

    // encontra o fim da linha
    int end = pos;
    while (str[end] && str[end] != '\n')
    {
        end++;
    }

    // aloca string para a linha
    int len = end - start;
    char *line = malloc(len + 1);
    if (!line)
        return NULL;

    memcpy(line, &str[start], len);
    line[len] = '\0';
    return line;
}

char *read_entire_file(char *filename, size_t *file_size)
{
    struct stat st;
    if (stat(filename, &st) != 0)
    { // atualiza st com as caracteristicas do ficheiro
        return NULL;
    }

    FILE *file = fopen(filename, "r");
    if (!file)
        return NULL;

    char *content = malloc(st.st_size + 1);
    if (!content)
    {
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(content, 1, st.st_size, file);
    content[bytes_read] = '\0';

    fclose(file);

    if (file_size)
        *file_size = bytes_read;
    return content;
}

// Retorna -2 se houver erros a ler ficheiros, -1 se o query estiver correto, caso contrário, retorna o numero da primeira linha que houver diferenças
int is_correct(int command_number, char *output_path, char *correct_output_path, char **expected_line, char **output_line)
{
    char correct_output_filename[30];
    sprintf(correct_output_filename, "/command%d_output.txt", command_number);
    char *correct_path = create_path(correct_output_path, correct_output_filename);
    size_t expected_file_size, output_file_size;
    char *expected = read_entire_file(correct_path, &expected_file_size);
    char *output = read_entire_file(output_path, &output_file_size);
    if (expected == NULL || output == NULL)
    {
        free(correct_path);
        free(expected);
        free(output);
        return -2; // erro ao ler ficheiros
    }
    int linha = 1;
    int i = 0;
    while (expected[i] && output[i] && expected[i] == output[i])
    {
        if (expected[i] == '\n')
            linha++;
        i++;
    }
    int result = expected[i] == '\0' && output[i] == '\0' ? -1 : linha;
    if (result != -1)
    {
        *expected_line = get_different_line(expected, i);
        *output_line = get_different_line(output, i);
    }
    free(correct_path);
    free(expected);
    free(output);
    return result;
}

// função que imprime a linha com diferenças a verde e vermelho
void print_diff_line(char *expected, char *output)
{
    int i = 0;
    printf("    Output: ");
    while (output[i])
    {
        if (expected[i] && expected[i] == output[i])
        {
            printf(BG_GREEN "%c" COLOR_RESET, output[i] ? output[i] : ' ');
        }
        else
        {
            printf(BG_RED "%c" COLOR_RESET, output[i]);
        }
        i++;
    }
    printf("\n");
    printf("    Expected: %s\n\n", expected);
}

// teste_query(command_number, l, aeroporto_gestor, aeronove_gestor, stats, file_path, file, command_number, line[0] - '0');
void teste_query(int command_number, char **l, Gestor_Global g_global, TestStatistics *stats, char *file_path, FILE *file, int num_line, int type_query, char *correct_output_path, char separator)
{
    String_Pool sp = get_string_pool(g_global);
    Gestor_Aeroportos aeroporto_gestor = get_gestor_aeroportos(g_global);
    Gestor_Aeronaves aeronave_gestor = get_gestor_aeronaves(g_global);
    Gestor_Passageiros passageiros_gestor = get_gestor_passageiros(g_global);
    Gestor_Voos voos_gestor = get_gestor_voos(g_global);
    Gestor_Reservas reservas_gestor = get_gestor_reservas(g_global);
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    char *result;
    if (type_query == 1)
        result = query1(l, aeroporto_gestor, separator);
    else if (type_query == 2)
        result = query2(l, aeronave_gestor, separator);
    else if (type_query == 3)
        result = query3(l, aeroporto_gestor, separator);
    else if (type_query == 4)
        result = query4(l, passageiros_gestor, separator);
    else if (type_query == 5)
        result = query5(l, voos_gestor, separator);
    else if (type_query == 6)
        result = query6(l, reservas_gestor, separator, sp);
    else
        return;
    print_string_to_file(file, result);
    free(result);
    fclose(file);
    clock_gettime(CLOCK_REALTIME, &end);

    int index = type_query - 1;
    double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    stats[index]->query_time += time;
    stats[index]->num_queries_tipo++;
    char *expected_line = NULL;
    char *output_line = NULL;
    num_line = is_correct(command_number, file_path, correct_output_path, &expected_line, &output_line);
    if (num_line == -2)
    {
        printf("Erro a pasta %s ou não existe ou não tem o ficheiro command%d_output.txt\n", correct_output_path, command_number);
        return;
    }
    else if (num_line != -1)
    { // se houver erros
        g_array_append_val(stats[index]->erros, num_line);
        g_array_append_val(stats[index]->total_queries, command_number);
        g_ptr_array_add(stats[index]->error_line, output_line);
        g_ptr_array_add(stats[index]->expected_output, expected_line);
    }
    else
        stats[index]->successful_queries++;
}

void programa_testes(char *csv_path, char *queries_path, char *correct_output_path)
{
    struct timespec start_aeroportos, end_aeroportos, start_aeronaves, end_aeronaves, start_voos, end_voos, start_passageiros, end_passageiros, start_reservas, end_reservas;
    double time_aeroportos, time_aeronaves, time_voos, time_passageiros, time_reservas;

    Gestor_Global g_global = initialize_gestor_global();

    // Medir tempo de parse do aeroportos
    clock_gettime(CLOCK_REALTIME, &start_aeroportos);
    aeroportos_parser(csv_path, 1, g_global);
    clock_gettime(CLOCK_REALTIME, &end_aeroportos);
    time_aeroportos = (end_aeroportos.tv_sec - start_aeroportos.tv_sec) + (end_aeroportos.tv_nsec - start_aeroportos.tv_nsec) / 1e9;

    // Medir uso de memória no parse dos aeroportos
    struct rusage memory_parse_aeroportos;
    getrusage(RUSAGE_SELF, &memory_parse_aeroportos);
    printf("\nMemory usage for airports parse and validation: %ld KB\n\n", memory_parse_aeroportos.ru_maxrss);

    // Medir tempo de parse das aeronaves
    clock_gettime(CLOCK_REALTIME, &start_aeronaves);
    aeronaves_parser(csv_path, 1, g_global);
    clock_gettime(CLOCK_REALTIME, &end_aeronaves);
    time_aeronaves = (end_aeronaves.tv_sec - start_aeronaves.tv_sec) + (end_aeronaves.tv_nsec - start_aeronaves.tv_nsec) / 1e9;

    // Medir uso de memória no parse das aeronaves
    struct rusage memory_parse_aeronaves;
    getrusage(RUSAGE_SELF, &memory_parse_aeronaves);
    printf("Memory usage for aricrafts parse and validation: %ld KB\n\n", memory_parse_aeronaves.ru_maxrss - memory_parse_aeroportos.ru_maxrss);

    // Medir tempo de parse dos voos
    clock_gettime(CLOCK_REALTIME, &start_voos);
    voos_parser(csv_path, 1, g_global);
    clock_gettime(CLOCK_REALTIME, &end_voos);
    time_voos = (end_voos.tv_sec - start_voos.tv_sec) + (end_voos.tv_nsec - start_voos.tv_nsec) / 1e9;

    // Medir uso de memória no parse dos voos
    struct rusage memory_parse_voos;
    getrusage(RUSAGE_SELF, &memory_parse_voos);
    printf("Memory usage for flights parse and validation: %ld KB\n\n", memory_parse_voos.ru_maxrss - memory_parse_aeronaves.ru_maxrss);

    // Medir tempo de parse dos passageiros
    clock_gettime(CLOCK_REALTIME, &start_passageiros);
    passageiros_parser(csv_path, 1, g_global); // Apenas para validação com criação de uma hash table sem values (só para ver se existem)
    clock_gettime(CLOCK_REALTIME, &end_passageiros);
    time_passageiros = (end_passageiros.tv_sec - start_passageiros.tv_sec) + (end_passageiros.tv_nsec - start_passageiros.tv_nsec) / 1e9;

    // Medir uso de memória no parse dos passageiros
    struct rusage memory_parse_passageiros;
    getrusage(RUSAGE_SELF, &memory_parse_passageiros);
    printf("Memory usage for passengers parse and validation: %ld KB\n\n", memory_parse_passageiros.ru_maxrss - memory_parse_voos.ru_maxrss);

    // Medir tempo de parse das reservas
    clock_gettime(CLOCK_REALTIME, &start_reservas);
    reserva_parser(csv_path, 1, g_global);
    clock_gettime(CLOCK_REALTIME, &end_reservas);
    time_reservas = (end_reservas.tv_sec - start_reservas.tv_sec) + (end_reservas.tv_nsec - start_reservas.tv_nsec) / 1e9;

    // Medir uso de memória no parse das reservas
    struct rusage memory_parse_reservas;
    getrusage(RUSAGE_SELF, &memory_parse_reservas);
    printf("Memory usage for reservations parse and validation: %ld KB\n\n", memory_parse_reservas.ru_maxrss - memory_parse_passageiros.ru_maxrss);

    printf("\n\n############ Tempos de execução do parse ############:\n");
    printf("Tempo de parse dos aeroportos: %.6f s\n", time_aeroportos);
    printf("Tempo de parse das aeronaves: %.6f s\n", time_aeronaves);
    printf("Tempo de parse dos voos: %.6f s\n", time_voos);
    printf("Tempo de parse dos passageiros: %.6f s\n", time_passageiros);
    printf("Tempo de parse das reservas: %.6f s\n", time_reservas);

    // Medir tempo das queries
    int number_of_queries = 6;

    TestStatistics stats[number_of_queries];
    initialize_test_statistics(stats, number_of_queries);

    FILE *queries_file = open_file(queries_path, "", "r", 1);
    if (queries_file == NULL)
    {
        free_gestor_global(g_global);
        printf("Erro ao abrir o ficheiro de queries\n");
        return;
    }
    int acabou = 0;
    int command_number = 1;
    while (!acabou)
    {
        char *line = get_line(queries_file, &acabou);
        if (line)
        {
            char *l = parse_string(&line, ' '); // avança o ponteiro para depois do '1 ' para ficar apenas com o argumento da query
            char separator = ';';
            if (l[1] == 'S')
                separator = '=';
            char file_path[50];
            sprintf(file_path, "resultados/command%d_output.txt", command_number); // permite formartar o caminho do ficheiro ja com o número correto
            FILE *file = open_file(file_path, "", "w", 1);
            if (file)
            {
                teste_query(command_number, &line, g_global, stats, file_path, file, command_number, l[0] - '0', correct_output_path, separator);
                command_number++;
            }
            else
                printf("Erro ao criar o ficheiro de output da query %d\n", command_number);
            free(l);
        }
    }
    fclose(queries_file);

    struct timespec end_total;
    clock_gettime(CLOCK_REALTIME, &end_total);
    double total_time = (end_total.tv_sec - start_aeroportos.tv_sec) + (end_total.tv_nsec - start_aeroportos.tv_nsec) / 1e9;

    for (int i = 0; i < number_of_queries; i++)
    {
        printf("\n\nTestes da Query %d\n", i + 1);
        printf("%d testes corretos de %d\n", stats[i]->successful_queries, stats[i]->num_queries_tipo);
        int num_erros = stats[i]->erros->len;
        if (num_erros != 0)
        {
            for (int j = 0; j < (int)stats[i]->erros->len; j++) // erros-> len coincide com total_queries->len pois sempre que se insere num tambe se insere no outro
            {
                int n_query = g_array_index(stats[i]->total_queries, int, j);
                printf("Discrepância na query %d: linha %d de resultados/command%d_output.txt\n", n_query, g_array_index(stats[i]->erros, int, j), n_query);
                print_diff_line(g_ptr_array_index(stats[i]->expected_output, j), g_ptr_array_index(stats[i]->error_line, j));
            }
        }
        printf("Tempo médio de execução da query %d: %.6f ms\n", i + 1, stats[i]->query_time * 1000 / stats[i]->num_queries_tipo);
    }
    free_test_statistics(stats, number_of_queries);
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    printf("\n\nTotal Memory usage: %ld KB\n", r_usage.ru_maxrss);
    printf("Tempo total de execução: %.6f s\n", total_time);

    free_gestor_global(g_global);
}

int main(int n, char **args)
{
    switch (n)
    {
    case 4:
        // modo do programa principal
        programa_testes(args[1], args[2], args[3]);
        break;
    default:
        printf("Comando inválido\n");
        return 1;
    }
    return 0;
}
