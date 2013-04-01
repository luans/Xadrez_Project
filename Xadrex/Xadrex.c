/*
 *
 * Arquivo com as funcoes utilizadas no Xadrex
 *
 *
 *
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include "Xadrex.h"

void new_Tabuleiro() {
    int i, j;
    char simbolo;

    printf("\n\t  |---|---|---|---|---|---|---|---|\n");

    for (i = 0; i <= 8; i++) {
        printf("\t%d | ", (i + 1));
        for (j = 0; j < 8; j++) {
            //IMPRIMIR CARACTERE SEM ESPAÇO ANTES E 1 DEPOIS
            printf("  | ");
        }

        printf("\n\t  |---|---|---|---|---|---|---|---|\n");
    }
    printf(  "\t    A   B   C   D   E   F   G   H  \n");
}
