#include <stdlib.h>
#include <stdio.h>
#include "utils/utils.h"
#include <string.h>
#include <time.h>
#include "io/parsers/parser.h"

char *create_path(char *path, char *file_name)
{
    int size_path = strlen(path);
    int size_file_name = strlen(file_name);
    char *result = malloc(size_path + size_file_name + 1);

    memcpy(result, path, size_path);
    memcpy(result + size_path, file_name, size_file_name);

    result[size_path + size_file_name] = '\0';

    return result;
}

int date_to_absolute_days(int date)
{
    int dia = date % 100;
    int mes = (date / 100) % 100;
    int ano = date / 10000;
    if (mes < 3)
    {
        ano--;
        mes += 12;
    }
    return 365 * ano + ano / 4 - ano / 100 + ano / 400 + (153 * mes - 457) / 5 + dia - 306;
}

int date_to_week(int date)
{
    //    int day_of_today = date_to_absolute_days(20251004); // ultimo dia da semana que contem o dia atual: 20250930
    int day_of_today = 739528; // equivalente a 20251004 para não estar sempre a repetir a conta
    int absolute_days = date_to_absolute_days(date);
    return (day_of_today - absolute_days) / 7;
}

float datetime_diff_minutes(int date1, int hour1, int date2, int hour2)
{
    // converter datas YYYYMMDD para dias absolutos
    int days1 = date_to_absolute_days(date1);
    int days2 = date_to_absolute_days(date2);

    // 2. Extrair horas e minutos
    int h1 = hour1 / 100;
    int m1 = hour1 % 100;

    int h2 = hour2 / 100;
    int m2 = hour2 % 100;

    // converter tudo para minutos totais desde o "dia zero"
    // usa-se long long para garantir que não há overflow
    long long total_min1 = (long long)days1 * 1440 + h1 * 60 + m1;
    long long total_min2 = (long long)days2 * 1440 + h2 * 60 + m2;

    // 4. Retornar a diferença
    return (float)(total_min1 - total_min2);
}

int is_number(char *str)
{
    if (*str == '\0')
        return 0;

    while (*str) // verifica todos os caracteres
    {
        if (*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

int flight_id_to_int(char *code)
{
    // Formato: L L N N N N N [N]

    // converter letras: usa-se como se fosse base 26 (porque existem 26 letras) e multiplica-se por 26 e soma-se o valor da próxima letra obtendo um valor único para as duas letras
    int l1 = code[0] - 'A';
    int l2 = code[1] - 'A';
    int letter_val = (l1 * 26) + l2;

    // converter números
    int number_part = string_to_int(code + 2);

    // Como os números podem ir até 999.999 (podem ser ate 6 digitos)
    return (letter_val * 1000000) + number_part;
}

int iata_to_int(char *code)
{
    // Formato: L L L
    if (!code || code[0] < 'A' || code[0] > 'Z' || code[1] < 'A' || code[1] > 'Z' || code[2] < 'A' || code[2] > 'Z' || code[3] != '\0')
        return -1;

    // converter letras: usa-se como se fosse base 26 (porque existem 26 letras) e multiplica-se por 26 e soma-se o valor da próxima letra obtendo um valor único para as três letras
    int l1 = code[0] - 'A';
    int l2 = code[1] - 'A';
    int l3 = code[2] - 'A';
    return (l1 * 26 * 26) + (l2 * 26) + l3;
}

char *int_to_iata(int code)
{
    char *iata = malloc(4 * sizeof(char));
    iata[3] = '\0';

    int l1 = code / (26 * 26);
    int l2 = (code / 26) % 26;
    int l3 = code % 26;

    iata[0] = (char)(l1 + 'A');
    iata[1] = (char)(l2 + 'A');
    iata[2] = (char)(l3 + 'A');

    return iata;
}