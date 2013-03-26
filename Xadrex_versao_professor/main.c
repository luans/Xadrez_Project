#include "Xadrez.h"

int main()
{
    Peca pecas[32];
    Peca* tabuleiro[DIM_TABULEIRO][DIM_TABULEIRO];
    inicializaTabuleiro(tabuleiro);

    /* Cria pecas */
    criaPecas(pecas, tabuleiro);

    /* Imprime Tabuleiro */
    imprimeTabuleiro("TABULEIRO:", tabuleiro);

    getch();

    system("cls");

    /* Move uma peca */
    movePeca(tabuleiro, "6a", "4a");


    getch();
    return 0;
}

/* Procedimento: display
 * Descricao: monta a tela principal do jogo, apresentando o tabuleiro e as opcoes do jogador.
 *            trata a entrada do jogador.
 */
void display() {
    while(1) {
        system("cls");

        /* Imprime Tabuleiro */
        imprimeTabuleiro("TABULEIRO:", tabuleiro);

        printf("");

    }
}


/* Procedimento: movePeca
 * Descricao: movimenta uma peca no tabuleiro (ainda não realiza validações).
 *            O movimento é feito com base em duas coordenadas: from e to.
 *            As coordenadas devem ter o formato "<linha><coluna>". Ex. "1d", "6a".
 * Parametros:
 *    1. (OUT) Peca* tabuleiro[][]: tabuleiro do jogo
 *    2. char from[3]: origem do movimento
 *    3. char to[3]: destino do movimento
 */
void movePeca(Peca* tabuleiro[DIM_TABULEIRO][DIM_TABULEIRO], char from[3], char to[3]) {
    int f_linha, f_coluna, t_linha, t_coluna;
    Peca *f_peca, *t_peca;

    /* Verifica formato das coordenadas */
    f_linha = from[0] - 48;
    t_linha = to[0] - 48;
    f_coluna = tolower(from[1]) - 97;
    t_coluna = tolower(to[1]) - 97;

    if (((f_linha < 8 && f_linha >= 0) && (t_linha < 8 && t_linha >= 0)) &&
        ((f_coluna < 8 && f_coluna >= 0) && (t_coluna < 8 && t_coluna >= 0))) {

        f_peca = tabuleiro[f_linha][f_coluna];
        if (f_peca != NULL) {

            t_peca = tabuleiro[t_linha][t_coluna];
            if ((t_peca != NULL) && (f_peca->lado == t_peca->lado)) {
                /* Nao pode mover uma peca para cima de outra peca da mesma cor */
                printf("Posicao destino ocupada por peca do jogador!");
            } else {
                if (t_peca != NULL) {
                    /* Peca inimiga roubada */
                    printf("%s rouba %s do adversario.", f_peca->nome, t_peca->nome);
                }
                tabuleiro[f_linha][f_coluna] = NULL;
                tabuleiro[t_linha][t_coluna] = f_peca;
            }
        } else {
            printf("Nao ha peca na posicao de origem!");
        }
    } else {
        printf("Formato invalido para coordenadas!");
    }
}

/* Procedimento: inicializaTabuleiro
 * Descricao: inicializa matriz do tabuleiro como vazio.
 * Parametros:
 *    1. (OUT) Peca* tabuleiro[][]: tabuleiro do jogo
 */
void inicializaTabuleiro(Peca* tabuleiro[DIM_TABULEIRO][DIM_TABULEIRO]) {

    /* Inicializa tabuleiro vazio */
    int i, j;
    for (i = 0; i < DIM_TABULEIRO; i++) {
        for (j = 0; j < DIM_TABULEIRO; j++) {
           tabuleiro[i][j] = NULL;
        }
    }

}

/* Procedimento: criaPecas
 * Descricao: cria todas as pecas do jogo e as coloca no tabuleiro.
 * Parametros:
 *    1. (OUT) Peca pecas[32]: vetor de pecas do jogo
 *    2. (OUT) Peca* tabuleiro[][]: tabuleiro do jogo
 */
void criaPecas(Peca pecas[32], Peca* tabuleiro[DIM_TABULEIRO][DIM_TABULEIRO]) {

    /* Melhoria futura: carregar situacao inicial de um arquivo de configuracao */
    char* nomes[8] = {"Torre da Rainha", "Cavalo da Rainha", "Bispo da Rainha", "Rainha", "Rei", "Bispo do Rei", "Cavalo do Rei", "Torre do Rei"};
    char simbolos[8] = {'t', 'h', 'b', 'q', 'k', 'b', 'h', 't'};

    /* Cria peoes brancos e pretos  */
    int i, j;
    int linha, aux_ind, indice;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 8; j++) {
            indice = j + (i * 8);
            strcpy(pecas[indice].nome, "Peao");
            pecas[indice].simbolo = ('p' - (32 * i));
            pecas[indice].lado = i + 1;
            linha = (i * 5) + 1;
            pecas[indice].linha = linha;
            pecas[indice].coluna = j;

            tabuleiro[linha][j] = &pecas[indice];
        }
    }

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 8; j++) {
            aux_ind = (j + (i * 8));
            indice = aux_ind + 16;
            strcpy(pecas[indice].nome, nomes[j]);
            pecas[indice].simbolo = (simbolos[j] - (32 * i));
            pecas[indice].lado = i + 1;
            linha = (i * 7);
            pecas[indice].linha = linha;
            pecas[indice].coluna = j;

            tabuleiro[linha][j] = &pecas[indice];
        }
    }
}

/* Procedimento: imprimeTabuleiro
 * Descricao: imprime situação do tabuleiro, de acordo com o posicionamento das pecas.
 * Parametros:
 *    1. char tit[32]: titulo impresso acima do tabuleiro. Tamanho maximo = 31 caracteres + '\0'
 *    2. Peca* tabuleiro[][]: matriz que deve ser impressa
 */
void imprimeTabuleiro(char tit[32], Peca* tabuleiro[DIM_TABULEIRO][DIM_TABULEIRO]) {

    /* Imprime tabuleiro  */
    int i, j;
    char simbolo;

    /* Imprime Titulo */
    printf("\n%s\n", tit);

    /* Imprime marcadores de coluna */
    printf("\n\t  |---|---|---|---|---|---|---|---|\n");

    for (i = (DIM_TABULEIRO - 1); i >= 0; i--) {
        printf("\t%d | ", (i + 1));
        for (j = 0; j < DIM_TABULEIRO; j++) {
            /* Formata cada entrada com dois digitos, preenchidos com zeros */
            simbolo = (tabuleiro[i][j] != NULL)? tabuleiro[i][j]->simbolo : ' ';
            printf("%c | ", simbolo);
        }
        /* Quebra linha */
        printf("\n\t  |---|---|---|---|---|---|---|---|\n");
    }
    printf(  "\t    A   B   C   D   E   F   G   H  \n");
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
