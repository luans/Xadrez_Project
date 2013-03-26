#ifndef XADREZ_H_INCLUDED
#define XADREZ_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#define DIM_TABULEIRO 8

/*************************************************************************************************
 * Declaracao de Variaveis de Dados                                                              *
 *************************************************************************************************/
/* Melhoria futura: carregar situacao inicial de um arquivo de configuracao */
extern char* nome_pecas[8];
extern char  simb_pecas[8];
extern char*  nome_lado[2];

/*************************************************************************************************
 * Declaracao das Estruturas                                                                     *
 *************************************************************************************************/
typedef enum e_lado_peca {
    BRANCA = 0,
    PRETA
} LadoPeca;

typedef struct s_peca {
    char nome[32];
    char simbolo;
    LadoPeca lado;
    int linha;
    int coluna;
    int jogada;
    int (*chkMov)(void*);
} Peca;

typedef struct s_jogo {
    /* Titulo do jogo */
    char titulo[64];

    /* Tabuleiro do Jogo */
    Peca* tabuleiro[DIM_TABULEIRO][DIM_TABULEIRO];

    /* Pecas do Jogo */
    Peca pecas[32];

    /* Mensagem */
    char mensagem[256];

    /* Jogada em andamento */
    Peca* peca_movida;
    int to_lin;
    int to_col;

    /* Indica de que eh a vez de jogar: Brancas ou Pretas */
    LadoPeca turno;
} Jogo;

/*************************************************************************************************
 * Declaracao das Funcoes                                                                        *
 *************************************************************************************************/
void display(Jogo *jogo);
Jogo* novoJogo(char titulo[64]);
void inicializaTabuleiro(Jogo *jogo);
void imprimeTabuleiro(Jogo *jogo);
void limpaTabuleiro(Peca* tabuleiro[DIM_TABULEIRO][DIM_TABULEIRO]);
void movePeca(Jogo *jogo, char from[3], char to[3]);

int checkMovTorre(void *aux_jogo);
int checkMovBispo(void *aux_jogo);
int checkMovPeao(void *aux_jogo);
int checkMovSTUB(void *aux_jogo);

#endif // XADREZ_H_INCLUDED
