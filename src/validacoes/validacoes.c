#include "validacoes/validacoes.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "entidades/aeroportos.h"
#include "gestor_entidades/gestor_reservas.h"
// #include "validacoes/validacoes.h"

int verifica_datahora(char *datahora)
{
    // yyyy-mm-dd hh:mm
    // verificar a estrutura geral
    if ((unsigned)(datahora[0] - '0') > 9 ||  // Dígito Ano 1
        (unsigned)(datahora[1] - '0') > 9 ||  // Dígito Ano 2
        (unsigned)(datahora[2] - '0') > 9 ||  // Dígito Ano 3
        (unsigned)(datahora[3] - '0') > 9 ||  // Dígito Ano 4
        datahora[4] != '-' ||                 // Separador
        (unsigned)(datahora[5] - '0') > 9 ||  // Dígito Mês 1
        (unsigned)(datahora[6] - '0') > 9 ||  // Dígito Mês 2
        datahora[7] != '-' ||                 // Separador
        (unsigned)(datahora[8] - '0') > 9 ||  // Dígito Dia 1
        (unsigned)(datahora[9] - '0') > 9 ||  // Dígito Dia 2
        datahora[10] != ' ' ||                // Separador (Espaço)
        (unsigned)(datahora[11] - '0') > 9 || // Dígito Hora 1
        (unsigned)(datahora[12] - '0') > 9 || // Dígito Hora 2
        datahora[13] != ':' ||                // Separador
        (unsigned)(datahora[14] - '0') > 9 || // Dígito Minuto 1
        (unsigned)(datahora[15] - '0') > 9 || // Dígito Minuto 2
        datahora[16] != '\0')                 // Terminador
    {
        return 0; // Inválido
    }
    unsigned int m1 = datahora[5] - '0';
    unsigned int m2 = datahora[6] - '0';
    int mes = m1 * 10 + m2;

    if (mes < 1 || mes > 12)
        return 0;

    // Dia
    unsigned int d1 = datahora[8] - '0';
    unsigned int d2 = datahora[9] - '0';
    int dia = d1 * 10 + d2;

    if (dia < 1 || dia > 31)
        return 0;

    // Hora e Minutos

    unsigned int h1 = datahora[11] - '0';
    unsigned int h2 = datahora[12] - '0';
    int hora = h1 * 10 + h2;

    if (hora > 23)
        return 0;

    // minutos
    unsigned int min1 = datahora[14] - '0';
    unsigned int min2 = datahora[15] - '0';
    int minuto = min1 * 10 + min2;

    if (minuto > 59)
        return 0;

    // Precisamos do Ano para comparar com 2025
    unsigned int y1 = datahora[0] - '0';
    unsigned int y2 = datahora[1] - '0';
    unsigned int y3 = datahora[2] - '0';
    unsigned int y4 = datahora[3] - '0';

    int ano = y1 * 1000 + y2 * 100 + y3 * 10 + y4;

    int data_atual_int = ano * 10000 + mes * 100 + dia;

    // Limite: 2025-09-30 (20250930)
    // basta verificar se o dia é menor ou igual. Não precisamos de comparar a hora.
    return data_atual_int <= 20250930;
}

int verifica_data(char *data)
{
    // yyyy-mm-dd hh:mm
    // verificar a estrutura geral
    if ((unsigned)(data[0] - '0') > 9 || // Dígito Ano 1
        (unsigned)(data[1] - '0') > 9 || // Dígito Ano 2
        (unsigned)(data[2] - '0') > 9 || // Dígito Ano 3
        (unsigned)(data[3] - '0') > 9 || // Dígito Ano 4
        data[4] != '-' ||                // Separador
        (unsigned)(data[5] - '0') > 9 || // Dígito Mês 1
        (unsigned)(data[6] - '0') > 9 || // Dígito Mês 2
        data[7] != '-' ||                // Separador
        (unsigned)(data[8] - '0') > 9 || // Dígito Dia 1
        (unsigned)(data[9] - '0') > 9 || // Dígito Dia 2
        data[10] != '\0')                // Terminador
    {
        return 0; // Inválido
    }
    unsigned int m1 = data[5] - '0';
    unsigned int m2 = data[6] - '0';
    int mes = m1 * 10 + m2;

    if (mes < 1 || mes > 12)
        return 0;

    // Dia
    unsigned int d1 = data[8] - '0';
    unsigned int d2 = data[9] - '0';
    int dia = d1 * 10 + d2;

    if (dia < 1 || dia > 31)
        return 0;

    // Precisamos do Ano para comparar com 2025
    unsigned int y1 = data[0] - '0';
    unsigned int y2 = data[1] - '0';
    unsigned int y3 = data[2] - '0';
    unsigned int y4 = data[3] - '0';

    int ano = y1 * 1000 + y2 * 100 + y3 * 10 + y4;

    int data_int = ano * 10000 + mes * 100 + dia;

    // Limite: 2025-09-30 (20250930)
    // basta verificar se o dia é menor ou igual. Não precisamos de comparar a hora.
    return data_int <= 20250930;
}

int verifica_year(char *year)
{
    if (!year)
        return 0;

    // Validação Estrutural
    if ((unsigned)(year[0] - '0') > 9 ||
        (unsigned)(year[1] - '0') > 9 ||
        (unsigned)(year[2] - '0') > 9 ||
        (unsigned)(year[3] - '0') > 9 ||
        year[4] != '\0')
        return 0;

    int y = (year[0] - '0') * 1000 +
            (year[1] - '0') * 100 +
            (year[2] - '0') * 10 +
            (year[3] - '0');

    // 4. Comparação Numérica (Instantânea)
    return y <= 2025;
}

int verifica_tipo_aeroporto(aeroporto_type s)
{
    if (s == ERROR_TYPE)
        return 0;
    return 1;
}

// exatamente 3 carateres, todos eles do intervalo [A-Z]
int verifica_aeroporto_code(char *code)
{
    if ((unsigned)(code[0] - 'A') > 25 ||
        (unsigned)(code[1] - 'A') > 25 ||
        (unsigned)(code[2] - 'A') > 25 ||
        code[3] != '\0') // Garante que tem exatamente 3 chars
    {
        return 0;
    }

    return 1;
}

int verifica_email(char *email)
{
    int i = 0;
    int has_at = 0;
    int has_dot = 0;
    int dominio2_count = 0;

    while (email[i] != '\0')
    {
        // parte do username (antes do @)
        if (!has_at)
        {
            if (email[i] == '@')
            {
                if (i == 0)
                    return 0; // não pode começar com @
                has_at = 1;
            }
            else
            {
                if (!((email[i] >= 'a' && email[i] <= 'z') || (email[i] >= '0' && email[i] <= '9') || email[i] == '.'))
                    return 0; // retorna log se  username invalido
            }
        }

        // após o @ e antes do .
        else if (has_at && !has_dot)
        {
            if (email[i] == '.')
            {
                if (email[i - 1] == '@')
                    return 0; // domínio não pode estar vazio
                has_dot = 1;
            }
            else
            {
                if (email[i] < 'a' || email[i] > 'z')
                    return 0; // domínio só letras minúsculas
            }
        }

        // após o .
        else if (has_at && has_dot)
        {
            if (email[i] < 'a' || email[i] > 'z')
                return 0;
            dominio2_count++;
            if (dominio2_count > 3)
                return 0; // não pode ter mais de 3 chars
        }

        i++;
    }

    // verificações finais
    if (!has_at || !has_dot)
        return 0; // faltou @ ou .
    if (dominio2_count < 2 || dominio2_count > 3)
        return 0; // dominio2 deve ter 2–3 letras
    if (email[i - 1] == '.' || email[i - 1] == '@')
        return 0;

    return 1;
}

void print_error_in_file(FILE *file, char *line)
{
    fprintf(file, "%s\n", line);
}

// [-90,90], tipo [-]dd.dddddddd  d corresponde a um numero entre 0 e 9 com no máximo 8 casas decimais
int verifica_latitude(char *latitude)
{
    int i = 0;
    int int_count = 0; // digitos antes do ponto
    int dec_count = 0; // digitos depois do ponto

    if (latitude[i] && latitude[i] == '-')
        i++;

    while (latitude[i] >= '0' && latitude[i] <= '9') // conta os digitos até antes do ponto
    {
        int_count++;
        i++;
    }
    if (int_count < 1 || int_count > 2)
        return 0;
    if (latitude[i] != '.')
        return 0;
    int is_max = 0;
    if (int_count == 2 && latitude[i - 2] == '9')
    {
        if (latitude[i - 1] > '0')
            return 0;
        else
            is_max = 1;
    }
    i++; // salta o '.'

    while (latitude[i] >= '0' && latitude[i] <= '9')
    {
        if (is_max && latitude[i] != '0')
            return 0;
        dec_count++;
        i++;
    }
    if (dec_count < 1 || dec_count > 8)
        return 0;

    if (latitude[i] != '\0')
        return 0;
    return 1; // se chear aqui é porque está válido
}

/* Longitude [-180,180], formato [-]ddd.dddddddd (até 8 decimais) */
int verifica_longitude(char *longitude)
{
    int i = 0;
    int int_count = 0;
    int dec_count = 0;

    if (longitude[i] == '-')
        i++;

    while (longitude[i] >= '0' && longitude[i] <= '9')
    {
        int_count++;
        i++;
    }
    if (int_count < 1 || int_count > 3)
        return 0;

    if (longitude[i] != '.')
        return 0;

    int is_max = 0;
    if (int_count == 3)
    {
        if (longitude[i - 3] > '1')
            return 0;
        else
        {
            if (longitude[i - 2] > '8')
                return 0;
            else if (longitude[i - 2] == '8')
            {
                if (longitude[i - 1] > '0')
                    return 0;
                else
                    is_max = 1;
            }
        }
    }
    i++;

    while (longitude[i] >= '0' && longitude[i] <= '9')
    {
        if (is_max && longitude[i] != '0')
            return 0;
        dec_count++;
        i++;
    }
    if (dec_count < 1 || dec_count > 8)
        return 0;

    if (longitude[i] != '\0')
        return 0;
    return 1;
}

/* 3 caracteres [A-Z] */
int verifica_IATA(char *iata)
{
    if ((unsigned)(iata[0] - 'A') > 25 ||
        (unsigned)(iata[1] - 'A') > 25 ||
        (unsigned)(iata[2] - 'A') > 25 ||
        iata[3] != '\0')
    {
        return 0;
    }

    return 1;
}

/* Flight id: ccddddd -> 2 letras + 5 ou 6 dígitos */
int verifica_flight_id(char *id)
{
    int i = 0;
    if ((unsigned)(id[0] - 'A') > 25 || (unsigned)(id[1] - 'A') > 25)
        return 0;

    // Loop para os dígitos (Indices 2 a 7)
    for (i = 2; id[i] && i < 8; i++)
    {
        if ((unsigned)(id[i] - '0') > 9)
            return 0;
    }
    if ((i != 7 && i != 8) || id[i] != '\0')
        return 0;

    return 1;
}

int verifica_reservation_id(char *id, Gestor_Reservas g_reserva)
{
    if (!id)
        return 0;

    // valida  a estrutura
    if (id[0] != 'R' ||
        (unsigned)(id[1] - '0') > 9 ||
        (unsigned)(id[2] - '0') > 9 ||
        (unsigned)(id[3] - '0') > 9 ||
        (unsigned)(id[4] - '0') > 9 ||
        (unsigned)(id[5] - '0') > 9 ||
        (unsigned)(id[6] - '0') > 9 ||
        (unsigned)(id[7] - '0') > 9 ||
        (unsigned)(id[8] - '0') > 9 ||
        (unsigned)(id[9] - '0') > 9 ||
        id[10] != '\0')
    {
        return 0;
    }

    return id_reserva_exists(g_reserva, id) == 0;
}

int verifica_document_number(char *dn)
{
    if ((unsigned)(dn[0] - '0') > 9 ||
        (unsigned)(dn[1] - '0') > 9 ||
        (unsigned)(dn[2] - '0') > 9 ||
        (unsigned)(dn[3] - '0') > 9 ||
        (unsigned)(dn[4] - '0') > 9 ||
        (unsigned)(dn[5] - '0') > 9 ||
        (unsigned)(dn[6] - '0') > 9 ||
        (unsigned)(dn[7] - '0') > 9 ||
        (unsigned)(dn[8] - '0') > 9 ||
        dn[9] != '\0') // Garante que termina exatamente aqui
    {
        return 0;
    }

    return 1;
}

/* Gender: M, F, O */
int verifica_gender(char *g)
{
    if ((g[0] == 'M' || g[0] == 'F' || g[0] == 'O') && g[1] == '\0')
        return 1;
    return 0;
}
