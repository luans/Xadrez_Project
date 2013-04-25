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
                jogoTabuleiro.pecasCoordenadas[flagcoordLINHA][flagcoordCOL] = &jogoPecas[flagcoordLINHA * 8 + flagcoordCOL];
            }
            if (flagcoordLINHA > 5 ){
                jogoTabuleiro.pecasCoordenadas[flagcoordLINHA][flagcoordCOL] = &jogoPecas[(flagcoordLINHA * 8 + flagcoordCOL) - 32];
            }
            if (flagcoordLINHA >= 2 && flagcoordLINHA <= 5){
                jogoTabuleiro.pecasCoordenadas[flagcoordLINHA][flagcoordCOL] = NULL;
            }
        }
    }

    printf("\nPecas brancas e pretas inicializadas com sucesso!");
    printf("\nPosicoes restauradas para padrao!\n");

    printf("\nQual o nome do jogador 01?\n");
    scanf( "%s", jogadoresSession[0].nomeJogador );
    jogadoresSession[0].corJogador = COR_BRANCA;

    printf("\nQual o nome do jogador 02?\n");
    scanf( "%s", jogadoresSession[1].nomeJogador );
    jogadoresSession[1].corJogador = COR_PRETA;
    system("cls");
}

void PrintTabuleiro(Tabuleiro jogo) {
    int coluna, linhatabul;
    char simbolo;

    printf("\n\t  |---|---|---|---|---|---|---|---|\n");

    for (linhatabul = 0; linhatabul < 8; linhatabul++) {
        printf("\t%d | ", (linhatabul + 1));
        for (coluna = 0; coluna < 8; coluna++) {

            if ( jogoTabuleiro.pecasCoordenadas[linhatabul][coluna] == NULL ) {
                printf("  | ");
            }
            else {
                printf("%s | ", jogoTabuleiro.pecasCoordenadas[linhatabul][coluna]->caracPeca);
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
void recebeJogada(int turnoJogador) {
    char playerJogadaInicial[4]; // Vetor para armazenar a peca que o jogador deseja mover
    char playerJogadaDestino[4]; // Vetor para armazenar o destino da peca
    int flagValidaJogada; // Flag para armazenar se a jogada foi validada!
    int flagValidaPadroes; // Flag para armazenar se os padroes foram validados!

    // Verificando qual e' o jogador ativo
    turnoJogador = turnoJogador % 2;

    printf("\n%s, qual a peca que voce deseja mover? Por exemplo: 7a\n", jogadoresSession[turnoJogador].nomeJogador);
    scanf("%s", playerJogadaInicial); // Recebe e armazena no vetor, nao esqueca do /0!
    printf("\nQual o destino dessa peca? Por exemplo: 8a\n");
    scanf("%s", playerJogadaDestino); // Recebe e armazena no vetor

    // Passa os parametros para o valida jogada
    flagValidaJogada = validaJogada( turnoJogador, ((int)playerJogadaInicial[0]-48)-1, (tolower(playerJogadaInicial[1]) - 97), ((int)playerJogadaDestino[0]-48)-1, (tolower(playerJogadaDestino[1]) - 97));

    // Tratando o retorno
    if ( flagValidaJogada == 0 ) {
        // Jogada nao permitida
        // Retorna a jogada do jogador!
        PrintTabuleiro(jogoTabuleiro);
        recebeJogada(turnoJogador);
    }

    else if ( flagValidaJogada >= 1 ) {
        flagValidaPadroes = validaPadroes ( ((int)playerJogadaInicial[0]-48)-1, (tolower(playerJogadaInicial[1]) - 97), ((int)playerJogadaDestino[0]-48)-1, (tolower(playerJogadaDestino[1]) - 97), jogoTabuleiro.pecasCoordenadas[((int)playerJogadaInicial[0]-48)-1][(tolower(playerJogadaInicial[1]) - 97)]->caracPeca );
        //printf("Flagzinha Valida Padroes: %i", flagValidaPadroes );

        if ( flagValidaPadroes == 0 ) {
            // Jogada invalida!
            system("cls");
            printf("Essa jogada eh invalida!\n");
            PrintTabuleiro(jogoTabuleiro);
            recebeJogada(turnoJogador);

        }

        else if ( flagValidaPadroes == 1 && flagValidaJogada == 1 ) {
            // Foi uma jogada normal, na qual o movimento pode ser executado!
            system("cls");
            movePeca( ((int)playerJogadaInicial[0]-48)-1, (tolower(playerJogadaInicial[1]) - 97), ((int)playerJogadaDestino[0]-48)-1, (tolower(playerJogadaDestino[1]) - 97));
            PrintTabuleiro(jogoTabuleiro);
        }

        else if ( flagValidaPadroes == 1 && flagValidaJogada == 3 ) {
            // Peca adversaria capturada!
            movePeca( ((int)playerJogadaInicial[0]-48)-1, (tolower(playerJogadaInicial[1]) - 97), ((int)playerJogadaDestino[0]-48)-1, (tolower(playerJogadaDestino[1]) - 97));
            system("cls");
            printf("\nPeca adversaria capturada!\n");
            PrintTabuleiro(jogoTabuleiro);
        }
        else if ( flagValidaPadroes == 1 && flagValidaJogada == 2 ) {
            // Cheque mate!
            movePeca( ((int)playerJogadaInicial[0]-48)-1, (tolower(playerJogadaInicial[1]) - 97), ((int)playerJogadaDestino[0]-48)-1, (tolower(playerJogadaDestino[1]) - 97));
            system("cls");
            PrintTabuleiro(jogoTabuleiro);
            printf("\nParabens %s, voce capturou o rei do outro jogador e venceu a partida!", jogadoresSession[turnoJogador].nomeJogador);
            flagJogoAtivo = 0;
            getch();
        }
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
int validaJogada(int jogador, int linhaInicial, int colunaInicial, int linhaDestino, int colunaDestino) {
    if ( linhaInicial >= 8 || linhaDestino >= 8 || colunaInicial >= 8 || colunaDestino >= 8 ) {
        // Valor extrapola os limites do tabuleiro...
        system("cls");
        printf("\nOs valores extrapolam o limite do tabuleiro!\n");
        return 0;
    }
    else if ( (linhaInicial == linhaDestino) && (colunaInicial == colunaDestino) ) {
        // Os valores são os mesmo, nao deixa executar a jogada
        system("cls");
        printf("\nVoce nao pode mover uma peca para a mesma posicao!\n");
        return 0;
    }

    else if ( jogoTabuleiro.pecasCoordenadas[linhaInicial][colunaInicial] == NULL ) {
        system("cls");
        printf("\nNao existe peca na posicao informada!\n");
        return 0;
    }

    else if ( jogoTabuleiro.pecasCoordenadas[linhaInicial][colunaInicial]->corPeca != jogadoresSession[jogador].corJogador ) {
        system("cls");
        printf("\nVoce nao pode mover pecas do adversario!\n");
        return 0;
    }

    // Se existe uma peca na posicao da matriz && essa peca eh da mesma cor!
    else if ( jogoTabuleiro.pecasCoordenadas[linhaDestino][colunaDestino] != NULL ) {

        if ( jogoTabuleiro.pecasCoordenadas[linhaInicial][colunaInicial]->corPeca == jogoTabuleiro.pecasCoordenadas[linhaDestino][colunaDestino]->corPeca ) {
            system("cls");
            printf("\nEssa posicao ja esta ocupada por uma peca sua!\n");
            return 0;
        }

        else if ( jogoTabuleiro.pecasCoordenadas[linhaInicial][colunaInicial]->corPeca != jogoTabuleiro.pecasCoordenadas[linhaDestino][colunaDestino]->corPeca ) {

            // Checagem para ver se o Rei nao foi capturado!
            if ( strcmp( jogoTabuleiro.pecasCoordenadas[linhaDestino][colunaDestino]->caracPeca, "K") == 0 || strcmp( jogoTabuleiro.pecasCoordenadas[linhaDestino][colunaDestino]->caracPeca, "k" ) == 0 ) {
                // O rei foi capturado!
                return 2;
            }

            else {
                // PECA CAPTURADA!
                system("cls");
                printf("\nPeca adversaria capturada!\n");
                return 3;
            }
        }
    } else {
        return 1;
    }
}
/*
 *
 *	Funcao movePeca
 *	Essa funcao vai ser utilizada para mover as pecas
 *	Data de criacao: 21/04/13
 *	Luan Lopes
 *
 */
void movePeca(int linhaInicial, int colunaInicial, int linhaDestino, int colunaDestino) {
    jogoTabuleiro.pecasCoordenadas[linhaDestino][colunaDestino] = jogoTabuleiro.pecasCoordenadas[linhaInicial][colunaInicial];
    jogoTabuleiro.pecasCoordenadas[linhaInicial][colunaInicial] = NULL;
}

int validaPadroes ( int linhaInicial, int colunaInicial, int linhaDestino, int colunaDestino, char tipoPeca[2] )
{
    int flagValidaPadroes; // 0 invalido 1 valido
    int linhaVal = 0;
    int colunaVal = 0;

    linhaInicial = sqrt ( ( linhaInicial*linhaInicial));
    colunaInicial = sqrt (( colunaInicial*colunaInicial ));
    linhaDestino = sqrt (( linhaDestino*linhaDestino ));
    colunaDestino = sqrt (( colunaDestino*colunaDestino ));

    tolower(tipoPeca);

    // Comparacoes!

    // **********************************//
    //      Comparacoes para a TORRE    //
    // ********************************//
    if ( strcmp(tipoPeca,"t") == 0 || strcmp(tipoPeca,"T") == 0) {
        if ( ( linhaInicial - linhaDestino ) == 0 || ( colunaInicial - colunaDestino ) == 0 ) {
            // Movimento válido!
            // Checar se as linhas que passaram estão vazias! Só o cavalo pula as pecas!

            int resultLinha = (linhaInicial-linhaDestino);
            resultLinha = sqrt ( resultLinha*resultLinha );

            //if ( resultLinha == 0 ) resultLinha = 1;

            int resultColuna = (colunaInicial-colunaDestino);
            resultColuna = sqrt ( resultColuna*resultColuna );

            if ( resultColuna == 0 ) {
                for (linhaVal = 0; linhaVal < resultLinha; linhaVal++) {
                    if ( jogoTabuleiro.pecasCoordenadas[linhaVal][resultColuna] != NULL ) {
                        printf("\nVoce nao pode pular pecas com a torre!\n");
                        flagValidaPadroes = 0;
                    } else {
                        flagValidaPadroes = 1;
                        break;
                    }
                }
            }

            else if ( resultLinha > 0 ) {
                for ( colunaVal = 0; colunaVal < resultColuna; colunaVal++) {
                    if ( jogoTabuleiro.pecasCoordenadas[resultLinha][colunaVal] != NULL ) {
                        printf("\nVoce nao pode pular pecas com a torre!\n");
                        flagValidaPadroes = 0;
                    } else {
                        flagValidaPadroes = 1;
                        break;
                    }
                }
            }
        }
    }
    // **********************************//
    //      Comparacoes para a Cavalo   //
    // ********************************//
    else if ( strcmp(tipoPeca,"c") == 0 || strcmp(tipoPeca,"C")  == 0) {
        if  ( ( (linhaInicial - linhaDestino) == -2 || (linhaInicial - linhaDestino) == 2 && ((colunaInicial - colunaDestino) == 1 || ((colunaInicial - colunaDestino) == -1))) || ((linhaInicial - linhaDestino) == 1 || (linhaInicial - linhaDestino) == -1) && ((colunaInicial - colunaDestino) == 2 || (colunaInicial - colunaDestino) == -2 )) {
            flagValidaPadroes = 1;
        } else {
            flagValidaPadroes = 0;
        }
    }

    // **********************************//
    //      Comparacoes para o Peao     //
    // ********************************//
    else if ( strcmp(tipoPeca, "p") == 0 || strcmp(tipoPeca, "P") == 0) {
        flagValidaPadroes = 1;
    }

    // **********************************//
    //      Comparacoes para o Bispo    //
    // ********************************//
    else if ( strcmp(tipoPeca,"b") == 0 || strcmp(tipoPeca,"B") == 0) {
        if ( ( linhaInicial - linhaDestino ) == ( colunaInicial - colunaDestino ) ) {
            // Valores vao ser sempre iguais! PORRA!
            // Movimento válido!

            int resultLinha = linhaInicial - linhaDestino;
            int resultColuna = colunaInicial - colunaDestino;

            // Lógica pro bispo! COMOFAS?
            flagValidaPadroes = 1;
        } else {
           flagValidaPadroes = 0;
        }
    }
    // **********************************//
    //      Comparacoes para a Rainha   //
    // ********************************//
    else if ( strcmp(tipoPeca,"q") == 0 || strcmp(tipoPeca,"Q") == 0) {
        flagValidaPadroes = 1;
    }
    // **********************************//
    //      Comparacoes para o Rei      //
    // ********************************//
    else if ( strcmp(tipoPeca,"k") == 0 || strcmp(tipoPeca,"K") == 0) {
        // Rei anda 1 casa apenas!
        if ( ((linhaInicial - linhaDestino) <= 1) && ((colunaInicial - colunaDestino) <= 1)) {
            flagValidaPadroes = 1;
        } else {
            flagValidaPadroes = 0;
        }
    }
    return flagValidaPadroes;
}
