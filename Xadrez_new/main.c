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
    /*
    RecebeDadosUsuario(); // Quais dados: NomeJogador01, NomeJogador02
    PassaDadosPraTabuleiro
    InicializaTabuleiro(NomeJogador01xNomeJogador02)
    CriaEInstanciaAsPecas
    */
    Tabuleiro* newgame; // Instancia um novo jogo
    Peca newpecas[32]; // Instancia um objeto Peca, com 32 pecas
    newgame = CriarJogo();

    RecebeDadosUsuario(newgame);
    GerarObjetos(newgame, &newpecas); // Cria as pecas, posicoes, tudo utilizado no jogo
    //DisplayTabuleiro(newgame);
   // CriarPecas, para retornar um ponteiro para todas as pecas



    return 0;
}
