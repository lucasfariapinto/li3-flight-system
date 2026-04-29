#include "validacoes/validacoes_passageiros.h"
#include "validacoes/validacoes.h"
#include <stdio.h>

int valida_passageiro(FILE *f_erros_aeronaves, char *line, char *document_number, char *dob, char *gender, char *email)
{
    if (verifica_document_number(document_number) &&
        verifica_data(dob) &&
        verifica_gender(gender) &&
        verifica_email(email))
        return 1;
    else
    {
        print_error_in_file(f_erros_aeronaves, line);
        return 0;
    }
}