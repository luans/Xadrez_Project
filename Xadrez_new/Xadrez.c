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
char *tipoPecasPreta[16] = { "T", "C", "B", "Q", "K", "B", "C", "T", "P", "P", "P", "P", "P", "P", "P", "P"};
char *tipoPecasBranca[16] = {  "p", "p", "p", "p", "p", "p", "p", "p" ,"t", "c", "b", "q", "k", "b", "c", "t"};


/**
 *
 *  Recebe os nomes dos usuarios
 *
 **/
void RecebeDadosUsuario(Tabuleiro* newgame) {
    printf("\nQual o nome do jogador 01? <Pecas Brancas>\n");
    scanf("%s", newgame->NomeJogador01);
    printf("\nQual o nome do jogador 02? <Pecas Pretas>\n");
    scanf("%s", newgame->NomeJogador02);
    printf("\nNovo jogo criado, boa sorte %s x %s !\n", newgame->NomeJogador01, newgame->NomeJogador02 );
}


/**
 *
 *  Inicializa uma nova posicao na memoria e zera todas as variáveis
 *  Passa esse ponteiro para uma outra função, que cria as peças
 *
 **/
Tabuleiro* CriarJogo() {
    // Aloca posicao na memoria para a tad
    Tabuleiro *newgame = (Tabuleiro*) malloc(sizeof(Tabuleiro));
    return newgame;
}

/**
 *
 *  Gera todos os objetos utilizados no jogo
 *
 **/
void GerarObjetos( Tabuleiro* newgame, Peca* newpecas[]) {
    // Inicializando as pecas
    int i = 0;
    int flagcoordLINHA,flagcoordCOL =0;

    for ( i = 0; i < 16; i ++ ) {
        newpecas[i] = (Peca*) malloc(sizeof(Peca));
        strcpy( newpecas[i]->NomePeca, nomeTodasPecas[i] );
        strcpy( newpecas[i]->SimboloPeca, tipoPecasPreta[i] );
        newpecas[i]->Lado = COR_PRETA;
    }

    int auxcont = 0;
    for ( i = 16; i < 32; i++ ) {
        auxcont++;
        newpecas[i] = (Peca*) malloc(sizeof(Peca));
        strcpy( newpecas[i]->NomePeca, nomeTodasPecas[auxcont] );
        strcpy( newpecas[i]->SimboloPeca, tipoPecasBranca[auxcont] );
        newpecas[i]->Lado = COR_BRANCA;
    }

    for ( flagcoordLINHA = 0; flagcoordLINHA < 8; flagcoordLINHA ++ ) {
        for ( flagcoordCOL = 0; flagcoordCOL < 8; flagcoordCOL ++ ) {
            if (flagcoordLINHA < 2) {
                newgame->JogoPecas[flagcoordLINHA][flagcoordCOL] = newpecas[flagcoordLINHA * 8 + flagcoordCOL];
            }
            if (flagcoordLINHA > 5 ) {
                newgame->JogoPecas[flagcoordLINHA][flagcoordCOL] = newpecas[flagcoordLINHA * 8 + flagcoordCOL];
            }
            if (flagcoordLINHA >= 2 && flagcoordLINHA <= 5) {
                newgame->JogoPecas[flagcoordLINHA][flagcoordCOL] = newpecas[flagcoordLINHA * 8 + flagcoordCOL];
            }
        }
    }
}

void DisplayTabuleiro(Tabuleiro* newgame) {
    char simbolo;
    int coluna, linhatabul;

    printf("\n\t  |---|---|---|---|---|---|---|---|\n");
    for (linhatabul = 0; linhatabul < 8; linhatabul++) {
        printf("\t%d | ", (linhatabul + 1));
        for (coluna = 0; coluna < 8; coluna++) {

            if ( newgame->JogoPecas[linhatabul][coluna] == NULL ) {
                printf("  | ");
            }
            else {
                printf("%s | ", newgame->JogoPecas[linhatabul][coluna]->SimboloPeca);
            }
        }
        printf("\n\t  |---|---|---|---|---|---|---|---|\n");
    }
    printf(  "\t    A   B   C   D   E   F   G   H  \n");
}
