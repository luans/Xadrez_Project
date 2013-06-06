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


typedef struct tad_jogo {
    char NomeJogo[20];
    int CurrentTurn; // Turno corrente, indica pecas brancas ou pretas
} Jogo;

typedef struct tad_peca {
    char NomePeca[128];
    char SimboloPeca[10];
    int Lado; // Indica se a peca é preta ou branca
    int CoordenadaLinha;
    int CoordenadaColuna;
} Peca;

typedef struct tad_tabuleiro {
   Peca *JogoPecas[8][8]; // Para armazenar a peca
   char NomeJogador01[10];
   char NomeJogador02[10];
} Tabuleiro;

Tabuleiro* CriarJogo(); // Retonar as memorias alocadas para uma estrutura Jogo
void RecebeDadosUsuario(Tabuleiro* newgame); // Recebe os nomes dos jogadores
void GerarObjetos( Tabuleiro* newgame, Peca* newpecas[] );
void DisplayTabuleiro(Tabuleiro* newgame);
/*DisplayTabuleiro();
ExecutarJogada();
GetCasa();
SetCasa();
MoverPeca();*/


#endif // XADREX_H_INCLUDED
