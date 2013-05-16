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


    Arquivo Xadrez.c


---------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Xadrez.h"

char *nomeTodasPecas[16] = { "Torre Esquerda", "Cavalo Esquerdo", "Bispo Esquerdo", "Rainha", "Rei", "Bispo Direito", "Cavalo Direito", "Torre Direita", "Peao", "Peao", "Peao", "Peao", "Peao", "Peao", "Peao", "Peao" };
char *tipoPecasBranca[16] = { "T", "C", "B", "Q", "K", "B", "C", "T", "P", "P", "P", "P", "P", "P", "P", "P"};
char *tipoPecasPreta[16] = {  "p", "p", "p", "p", "p", "p", "p", "p" ,"t", "c", "b", "q", "k", "b", "c", "t"};

