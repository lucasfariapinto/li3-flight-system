#include "validacoes/validacoes_aeroportos.h"
#include "validacoes/validacoes.h"
#include <stdio.h>
#include "entidades/aeroportos.h"

int valida_aeroporto(FILE *f_erros_aeroportos, char *line, char *aeroporto_code, char *aeroporto_latitude, char *aeroporto_longitude, aeroporto_type aeroporto_tipo)
{
    if (verifica_tipo_aeroporto(aeroporto_tipo) &&
        verifica_aeroporto_code(aeroporto_code) &&
        verifica_latitude(aeroporto_latitude) &&
        verifica_longitude(aeroporto_longitude))
        return 1;
    else
    {
        print_error_in_file(f_erros_aeroportos, line);
        return 0;
    }
}