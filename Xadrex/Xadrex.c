/*
 *
 * Arquivo com as funcoes utilizadas no Xadrex
 *
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Xadrex.h"

char *nomeTodasPecas[16] = { "Torre Esquerda", "Cavalo Esquerdo", "Bispo Esquerdo", "Rainha", "Rei", "Bispo Direito", "Cavalo Direito", "Torre Direita", "Peao", "Peao", "Peao", "Peao", "Peao", "Peao", "Peao", "Peao" };
char *tipoPecasBranca[16] = { "T", "C", "B", "Q", "K", "B", "C", "T", "P", "P", "P", "P", "P", "P", "P", "P"};
char *tipoPecasPreta[16] = {  "p", "p", "p", "p", "p", "p", "p", "p" ,"t", "c", "b", "q", "k", "b", "c", "t"};

void iniciarJogo() {
    int i = 0;
    int flagcoordLINHA,flagcoordCOL =0;

    // Loop de inicializacao das pecas
    for ( i = 0; i < 16; i ++ ) {
        strcpy( jogoPecas[i].nomePeca, nomeTodasPecas[i] );
        strcpy( jogoPecas[i].caracPeca, tipoPecasBranca[i] );
        jogoPecas[i].corPeca = COR_BRANCA;

        strcpy( jogoPecas[i+16].nomePeca, nomeTodasPecas[i] );
        strcpy( jogoPecas[i+16].caracPeca, tipoPecasPreta[i] );
        jogoPecas[i+16].corPeca = COR_PRETA;
    }

    for ( flagcoordLINHA = 0; flagcoordLINHA < 8; flagcoordLINHA ++ ) {
        for ( flagcoordCOL = 0; flagcoordCOL < 8; flagcoordCOL ++ ) {
             if (flagcoordLINHA < 2){
                /**< Salva a peça na pos "x" e "y" e atribui a peça na posição no vetor jogopecas ex: linha 0 coluna 0 (0 * 8 = 0 + 0 = 0) linha 0 coluna 1 (0 * 8 = 0 + 1 = 1)*/
                jogoTabuleiro.pecasCoordenadas[flagcoordLINHA][flagcoordCOL] = jogoPecas[flagcoordLINHA * 8 + flagcoordCOL];
            }
            if (flagcoordLINHA > 5 ){
                jogoTabuleiro.pecasCoordenadas[flagcoordLINHA][flagcoordCOL] = jogoPecas[(flagcoordLINHA * 8 + flagcoordCOL) - 32];
            }
        }
    }

    printf("\nPecas brancas e pretas inicializadas com sucesso!");
    printf("\nPosicoes restauradas para padrao!\n");
}

void new_Tabuleiro() {
    int i, j;
    char simbolo;

    printf("\n\t|---|---|---|---|---|---|---|---|\n");

    for (i = 0; i < 8; i++) {
        printf("\t%d | ", (i + 1));
        for (j = 0; j < 8; j++) {
            //IMPRIMIR CARACTERE SEM ESPAÇO ANTES E 1 DEPOIS
            printf(" | ");
        }

        printf("\n\t|---|---|---|---|---|---|---|---|\n");
    }
    printf(  "\t  A   B   C   D   E   F   G   H  \n");
}



void PrintTabuleiro(Tabuleiro jogo) {
    int coluna, linhatabul;
    char simbolo;

    printf("\n\t  |---|---|---|---|---|---|---|---|\n");

    for (linhatabul = 0; linhatabul < 8; linhatabul++) {
        printf("\t%d | ", (linhatabul + 1));
        for (coluna = 0; coluna < 8; coluna++) {
            //IMPRIMIR CARACTERE SEM ESPAÇO ANTES E 1 DEPOIS
            if (linhatabul < 2){
                printf("%s | ", jogoTabuleiro.pecasCoordenadas[linhatabul][coluna].caracPeca);
            }
            if (linhatabul > 5 ){
                printf("%s | ", jogoTabuleiro.pecasCoordenadas[linhatabul][coluna].caracPeca);
            }
            if (linhatabul >= 2 && linhatabul <= 5){
                printf("  | ");
            }
        }
        printf("\n\t  |---|---|---|---|---|---|---|---|\n");
    }
    printf(  "\t    A   B   C   D   E   F   G   H  \n");
}

/*
 *
 *	Funcao recebeJogada
 *	Essa funcao vai ser utilizada dentro de um loop no arquivo principal
 *	Recebe a jogada e joga para uma outra funcao, a fim de validar se a jogada e' valida!
 *	Data de criacao: 17/04/13
 *	Luan Lopes
 *
 */
void recebeJogada() {
    char playerJogadaInicial[3]; // Vetor para armazenar a peca que o jogador deseja mover
    char playerJogadaDestino[3]; // Vetor para armazenar o destino da peca
    int flagValidaJogada; // Flag para armazenar se a jogada foi validada!
    printf("Qual a peca que voce deseja mover? Por exemplo: 7a");
    gets(playerJogadaInicial); // Recebe e armazena no vetor, nao esqueca do /0!
    printf("Qual o destino dessa peca? Por exemplo: 8a");
    gets(playerJogadaDestino); // Recebe e armazena no vetor
    // Passa os parametros para o valida jogada
    flagValidaJogada = validaJogada(playerJogadaInicial[0], playerJogadaInicial[1], playerJogadaDestino[0], playerJogadaDestino[1]);
    // Tratando o retorno
    if ( flagValidaJogada == 0 ) {
        // Caso a jogada nao eh permitida
        system("cls");
        printf("Jogada invalida!");
    }

    else if ( flagValidaJogada == 1 ) {
        // Caso a peca for movida corretamente
    }

    else if ( flagValidaJogada == 2 ) {
        // Caso a peca tiver roubado alguma outra
    }


}

/*
 *
 *	Funcao validaJogada
 *	Essa funcao vai ser utilizada em uma chamada pela funcao recebeJogada
 *	Ela analisa se a jogada e' valida, e volta um valor inteiro para a funcao recebe jogada tratar esse retorno
 *	Retorno 0: Jogada invalida, Retorno 1: Jogada executada normal, Retorno 2: Peca do outro jogador roubada
 *	Data de criacao: 17/04/13
 *	Luan Lopes
 *
 */
int validaJogada(char linhaInicial[2], char colunaInicial[2], char linhaDestino[2], char colunaDestino[2] ) {
	return 1;
}
