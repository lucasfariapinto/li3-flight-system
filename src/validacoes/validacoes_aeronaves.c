#include "validacoes/validacoes_aeronaves.h"
#include "validacoes/validacoes.h"
#include <stdio.h>

int valida_aeronave(FILE *f_erros_aeronaves, char *line, char *aeronave_year)
{  
    if (verifica_year(aeronave_year))
    return 1;
    else {
        print_error_in_file(f_erros_aeronaves, line);
        return 0;
    }
}