#include "Xadrez.h"

int main()
{
    system("cls");

    /* Cria jogo */
    Jogo *jogo = novoJogo("Kasparov x Deep Blue");

    /* Exibe interface e controla entrada dos jogadores */
    display(jogo);

    getch();
    return 0;
}


/*
    0 1 2 3 4 5 6 7
    A B C D E F G H
0 1 t h b k q b h t
1 2 p p p p p p p p
2 3 O O O O O O O O
3 4 O O O O O O O O
4 5 O O O O O O O O
5 6 O O O O O O O O
6 7 P P P P P P P P
7 8 T H B Q K B H T












*/
