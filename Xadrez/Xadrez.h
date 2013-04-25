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


    Arquivo Xadrez.h


---------------------------------------------------- */
#ifndef XADREX_H_INCLUDED
#define XADREX_H_INCLUDED

#define TOTAL_PECAS 32

#define COR_BRANCA 1
#define COR_PRETA 2

typedef struct pecaInfo {
    char nomePeca[25];
    char caracPeca[3];
    int corPeca;
    int posX;
    int posY;
} Peca;

typedef struct tabuleiroInfo {
    Peca *pecasCoordenadas[8][8]; // Tem as coordenadas do tabuleiro, da esquerda pra direita, de baixo pra cima
    // pecasCoordenadas[LINHA][COLUNA]
} Tabuleiro;

typedef struct sessionInfo {
    char nomeJogador[30];
    int corJogador;
} Session;

Peca jogoPecas[TOTAL_PECAS];
Tabuleiro jogoTabuleiro;
Session jogadoresSession[2];
int flagJogoAtivo; // Variavel para definir o fim do jogo

void iniciarJogo(); // Inicia um novo jogo
void recebeJogada(int turnoJogador);
int validaJogada(int jogador, int linhaInicial, int colunaInicial, int linhaDestino, int colunaDestino);
void movePeca(int linhaInicial, int colunaInicial, int linhaDestino, int colunaDestino);
int validaPadroes ( int linhaInicial, int colunaInicial, int linhaDestino, int colunaDestino, char tipoPeca[2] );

#endif // XADREX_H_INCLUDED
