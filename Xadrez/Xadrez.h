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
    //pecaInfo *ant;
} Peca;

typedef struct tabuleiroInfo {
    Peca pecasCoordenadas[8][8]; // Tem as coordenadas do tabuleiro, da esquerda pra direita, de baixo pra cim,
    // pecasCoordenadas[LINHA][COLUNA]
} Tabuleiro;

Peca jogoPecas[TOTAL_PECAS];
Tabuleiro jogoTabuleiro;

void iniciarJogo(); // Inicia um novo jogo
void testePrintTabuleiro(Tabuleiro jogo);
void recebeJogada();
int validaJogada(char linhaInicial[2], char colunaInicial[2], char linhaDestino[2], char colunaDestino[2] );
//void limparTabuleiro(); // Limpa o tabuleiro, zerando a posicao das pecas
//void lerJogada(); // Recebe a jogada do usuario
//void verificarJogada(); // Valida a jogada recebida do usuario
//void executaJogada();

void new_Tabuleiro();

#endif // XADREX_H_INCLUDED
