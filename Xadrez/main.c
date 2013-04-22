/* ----------------------------------------------------

    Dev-Group
    Projeto Xadrez

    ----------------------------------------------------

    Estrutura de Dados

    Engenharia da Computacao, 3o semestre

    ----------------------------------------------------

    Grupo:  Luan Lopes da Silva
            Guilherme Francisco Nogueira
            Joao Evaristo
            Guilherme Dakuzaku

    Professor: Giulliano Paes Carnielli

    ----------------------------------------------------


    Arquivo main.c


---------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include "Xadrez.h"

int main()
{
    iniciarJogo();
    PrintTabuleiro(jogoTabuleiro);

    flagJogoAtivo = 1;

    int turnoContador = 0;

    // Turno par = jogador 01, turno impar = jogador 02
    do {

        recebeJogada(turnoContador);
        turnoContador++;

    } while(flagJogoAtivo == 1);

    return 0;
}
