#include "io/output/output.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *generate_result_string(void *result[], char *format[], int n, char separator)
{
    int total_size = 0;

    for (int i = 0; i < n; i++)
    {
        if (format[i][1] == 's')
        {
            char *str = (char *)result[i];
            total_size += strlen(str);
        }
        else if (strcmp(format[i], "%.3f") == 0)
        {
            total_size += 20; // Espaço suficiente para float com 3 casas decimais
        }
        else
        {
            total_size += 20; // Espaço suficiente para int
        }

        if (i != n - 1)
            total_size += 1; // Para o separador
    }

    total_size += 1; // Para \n final

    char *output = malloc(total_size * sizeof(char));
    output[0] = '\0'; // Inicializar string vazia

    // Construir string
    for (int i = 0; i < n; i++)
    {
        char temp_buffer[100];

        if (format[i][1] == 's')
        {
            sprintf(temp_buffer, format[i], result[i]);
        }
        else if (strcmp(format[i], "%.3f") == 0)
        {
            double result_double = *(double *)(result[i]);
            sprintf(temp_buffer, format[i], result_double);
        }
        else
        {
            int result_int = *(int *)(result[i]);
            sprintf(temp_buffer, format[i], result_int);
        }

        strcat(output, temp_buffer);

        if (i != n - 1)
        {
            char sep_str[2] = {separator, '\0'};
            strcat(output, sep_str);
        }
    }

    strcat(output, "\n");
    return output;
}

char *generate_empty_result_string()
{
    char *output = malloc(2 * sizeof(char));
    output[0] = '\n';
    output[1] = '\0';
    return output;
}

char *convert_date_to_string(int date)
{
    int day = date % 100;
    int month = (date / 100) % 100;
    int year = date / 10000;
    char *data = malloc(sizeof(char) * 50); // YYYY/MM/DD + '\n'
    sprintf(data, "%d-%02d-%02d", year, month, day);
    return data;
}

void print_string_to_file(FILE *file, char *string)
{
    fprintf(file, "%s", string);
}