#include "Xadrez.h"

/*************************************************************************************************
 * Inicializacao de Variaveis de Dados                                                           *
 *************************************************************************************************/
/* Melhoria futura: carregar situacao inicial de um arquivo de configuracao */
char* nome_pecas[8] = {"Torre da Rainha", "Cavalo da Rainha", "Bispo da Rainha", "Rainha", "Rei",
                       "Bispo do Rei", "Cavalo do Rei", "Torre do Rei"};
char* nome_lado[2] = {"Brancas (minusculas)", "Pretas (maiusculas)"};
char simb_pecas[8] = {'t', 'h', 'b', 'q', 'k', 'b', 'h', 't'};

/*************************************************************************************************
 * Implementacao das Funcoes do Jogo                                                             *
 *************************************************************************************************/

/* Procedimento: display
 * Descricao: monta a tela principal do jogo, apresentando o tabuleiro e as opcoes do jogador.
 *            trata a entrada do jogador.
 * Parametros:
 *    1. Jogo *jogo: referencia ao jogo cuja interface deve ser construida.
 */
void display(Jogo *jogo) {
    int sair = 0;
    while(!sair) {
        system("cls");

        /* Imprime Tabuleiro */
        imprimeTabuleiro(jogo);

        /* Imprime mensagens */
        printf("\n: %s \n\n", jogo->mensagem);

        /* Limpa campo de mensagem */
        strcpy(jogo->mensagem, " - ");

        /* Monta o menu */
        char jogada[6];
        printf("Digite uma jogada (ex. 7e 6e) ou <ENTER> para sair\n");
        printf("%s: ", nome_lado[jogo->turno]);
        gets(jogada);
        //scanf("%s ", jogada);

        if (strlen(jogada) > 0) {
            /* Quebra comando em origem e destino */
            char *from = strtok(jogada, " ");
            char *to   = strtok(NULL, " ");
            if (from != NULL && to != NULL) {
                movePeca(jogo, from, to);
            } else {
                sprintf(jogo->mensagem, "Comando nao reconhecido!");
            }
        } else {
            /* <ENTER> vazio quebra o loop */
            sair = 1;
        }
    }
}

/* Procedimento: novoJogo
 * Descricao: instancia e inicializa um novo jogo, criando as pecas e a situacao inicial do
 *            tabuleiro.
 * Parametros:
 *    1. char titulo[64]: titulo do jogo
 * Retorna: ponteiro para o novo Jogo criado.
 */
Jogo* novoJogo(char titulo[64]) {
    Jogo *jogo = (Jogo*) malloc(sizeof(Jogo));
    strcpy(jogo->titulo, titulo);
    jogo->turno = BRANCA;
    jogo->peca_movida = NULL;
    jogo->to_col = -1;
    jogo->to_lin = -1;
    strcpy(jogo->mensagem, " - ");
    inicializaTabuleiro(jogo);
    return jogo;
}

/* Procedimento: limpaTabuleiro
 * Descricao: inicializa matriz do tabuleiro como vazio.
 * Parametros:
 *    1. (OUT) Peca* tabuleiro[][]: tabuleiro do jogo
 */
void limpaTabuleiro(Peca* tabuleiro[DIM_TABULEIRO][DIM_TABULEIRO]) {

    /* Inicializa tabuleiro vazio */
    int i, j;
    for (i = 0; i < DIM_TABULEIRO; i++) {
        for (j = 0; j < DIM_TABULEIRO; j++) {
           tabuleiro[i][j] = NULL;
        }
    }
}

/* Procedimento: anexaFuncaoMovimento
 * Descricao: associa uma das funcoes que validam movimentos das pecas, de acordo como tipo da peca.
 * Parametros:
 *    1. (OUT) Peca* peca: peca para anexar funcao de validacao de movimento.
 */
void anexaFuncaoMovimento(Peca *peca) {
    switch(tolower(peca->simbolo)) {
    case 't':
        peca->chkMov = checkMovTorre;
        break;
    case 'b':
        peca->chkMov = checkMovBispo;
        break;
    case 'h':
    case 'q':
    case 'k':
        peca->chkMov = checkMovSTUB;
        break;
    case 'p':
        peca->chkMov = checkMovPeao;
        break;
    }
}

/* Procedimento: inicializaTabuleiro
 * Descricao: cria todas as pecas do jogo e as coloca no tabuleiro.
 * Parametros:
 *    1. (OUT) Jogo* jogo: referencia para o jogo em andamento
 */
void inicializaTabuleiro(Jogo *jogo) {
    /* Limpa o tabuleiro antes de posicionar as pecas */
    limpaTabuleiro(jogo->tabuleiro);

    /* Cria peoes brancos e pretos  */
    int i, j;
    int linha, aux_ind, indice;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 8; j++) {
            indice = j + (i * 8);
            strcpy(jogo->pecas[indice].nome, "Peao");
            jogo->pecas[indice].simbolo = ('p' - (32 * i));
            jogo->pecas[indice].lado = i;
            linha = (i * 5) + 1;
            jogo->pecas[indice].linha = linha;
            jogo->pecas[indice].coluna = j;
            anexaFuncaoMovimento(&(jogo->pecas[indice]));
            jogo->tabuleiro[linha][j] = &(jogo->pecas[indice]);
            jogo->pecas[indice].linha = linha;
            jogo->pecas[indice].coluna = j;
            jogo->pecas[indice].jogada = 0;
        }
    }

    /* Cria e posiciona demais pecas */
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 8; j++) {
            aux_ind = (j + (i * 8));
            indice = aux_ind + 16;
            strcpy(jogo->pecas[indice].nome, nome_pecas[j]);
            jogo->pecas[indice].simbolo = (simb_pecas[j] - (32 * i));
            jogo->pecas[indice].lado = i;
            linha = (i * 7);
            jogo->pecas[indice].linha = linha;
            jogo->pecas[indice].coluna = j;
            anexaFuncaoMovimento(&(jogo->pecas[indice]));
            jogo->tabuleiro[linha][j] = &(jogo->pecas[indice]);
            jogo->pecas[indice].linha = linha;
            jogo->pecas[indice].coluna = j;
            jogo->pecas[indice].jogada = 0;
        }
    }
}

/* Procedimento: movePeca
 * Descricao: movimenta uma peca no tabuleiro (ainda não realiza validações).
 *            O movimento é feito com base em duas coordenadas: from e to.
 *            As coordenadas devem ter o formato "<linha><coluna>". Ex. "1d", "6a".
 * Parametros:
 *    1. (OUT) Jogo* jogo: referencia para o jogo em andamento
 *    2. char from[3]: origem do movimento
 *    3. char to[3]: destino do movimento
 */
void movePeca(Jogo *jogo, char from[3], char to[3]) {
    int f_linha, f_coluna, t_linha, t_coluna;
    Peca *t_peca = NULL;

    /* Verifica formato das coordenadas */
    f_linha = from[0] - 49;
    t_linha = to[0] - 49;
    f_coluna = tolower(from[1]) - 97;
    t_coluna = tolower(to[1]) - 97;

    /* Validacoes basicas (independente do tipo da peca) */
    if (((f_linha < 8 && f_linha >= 0) && (t_linha < 8 && t_linha >= 0)) &&
        ((f_coluna < 8 && f_coluna >= 0) && (t_coluna < 8 && t_coluna >= 0))) {

        jogo->peca_movida = jogo->tabuleiro[f_linha][f_coluna];
        jogo->to_lin = t_linha;
        jogo->to_col = t_coluna;
        if (jogo->peca_movida != NULL) {
            /* Verifica se a peca movida pertence ao jogador */
            if (jogo->peca_movida->lado == jogo->turno) {

                t_peca = jogo->tabuleiro[t_linha][t_coluna];
                if ((t_peca != NULL) && (jogo->peca_movida->lado == t_peca->lado)) {
                    /* Nao pode mover uma peca para cima de outra peca da mesma cor */
                    sprintf(jogo->mensagem, "Posicao destino ocupada por peca do jogador!");
                } else {
                    if (jogo->peca_movida->chkMov(jogo)) {
                        if (t_peca != NULL) {
                            /* Peca inimiga roubada */
                            sprintf(jogo->mensagem, "%s rouba %s do adversario.",
                                    jogo->peca_movida->nome, t_peca->nome);
                        }
                        jogo->tabuleiro[f_linha][f_coluna] = NULL;
                        jogo->tabuleiro[t_linha][t_coluna] = jogo->peca_movida;
                        jogo->peca_movida->linha  = t_linha;
                        jogo->peca_movida->coluna = t_coluna;
                        jogo->peca_movida->jogada++;

                        /* Passa a vez para o adversario */
                        jogo->turno = (jogo->turno + 1) % 2;
                    }
                }
            } else {
                sprintf(jogo->mensagem, "Nao mova pecas do adversario!");
            }
        } else {
            sprintf(jogo->mensagem, "Nao ha peca na posicao de origem!");
        }
    } else {
        sprintf(jogo->mensagem, "Formato invalido para coordenadas!");
    }
}

/* Procedimento: imprimeTabuleiro
 * Descricao: imprime situação do tabuleiro, de acordo com o posicionamento das pecas.
 * Parametros:
 *    1. (OUT) Jogo* jogo: referencia para o jogo em andamento
 */
void imprimeTabuleiro(Jogo *jogo) {

    /* Imprime tabuleiro  */
    int i, j;
    char simbolo;

    /* Imprime Titulo */
    printf("\n%s\n", jogo->titulo);

    /* Imprime marcadores de coluna */
    printf("\n\t  |---|---|---|---|---|---|---|---|\n");

    for (i = (DIM_TABULEIRO - 1); i >= 0; i--) {
        printf("\t%d | ", (i + 1));
        for (j = 0; j < DIM_TABULEIRO; j++) {
            /* Formata cada entrada com dois digitos, preenchidos com zeros */
            simbolo = (jogo->tabuleiro[i][j] != NULL)? jogo->tabuleiro[i][j]->simbolo : ' ';
            printf("%c | ", simbolo);
        }
        /* Quebra linha */
        printf("\n\t  |---|---|---|---|---|---|---|---|\n");
    }
    printf(  "\t    A   B   C   D   E   F   G   H  \n");
}

/*************************************************************************************************
 * Implementacao das Funcoes de Validacao de Movimento das Pecas                                 *
 * NOTA: as funcoes abaixo servem para validar o movimento de cada uma das pecas do jogo. Serao  *
 *       referenciadas por ponteiros e, portanto, todas devem ter a mesma assinatura:            *
 *       int(*func_name)(Jogo*)                                                                  *
 *                                                                                               *
 * Operacao: toda funcao recebe como parametro o tabuleiro e as coordenadas iniciais (from) e    *
 *           finais. Deve verificar se o movimento eh valido. Se for valido, retorna 1, senao 0. *
 *************************************************************************************************/

/* Funcao que verifica padrao de movimento especifico de Torres */
int checkPadraoTorre(Jogo *jogo, int deltaLin, int deltaCol) {
    int movimento_valido = 0;
    /* Verifica se houve movimento em apenas 1 direcao */
    if (deltaLin == 0 || deltaCol == 0){
        movimento_valido = 1;
    }
    return movimento_valido;
}

/* Funcao que verifica padrao de movimento especifico de Bispos */
int checkPadraoBispo(Jogo *jogo, int deltaLin, int deltaCol) {
    int movimento_valido = 0;
    /* Verifica se houve movimento proporciona nas duas direcoes */
    if (deltaLin == deltaCol) {
        movimento_valido = 1;
    }
    return movimento_valido;
}

int checkPadraoPeao(Jogo *jogo, int deltaLin, int deltaCol) {
    int movimento_valido = 0;
    Peca *peca = jogo->peca_movida;
    int movDeltaLin = jogo->to_lin - peca->linha;
    int auxDeltaLin = movDeltaLin;
    if (peca->lado == PRETA) {
        auxDeltaLin *= -1;
    }

    int limiteMovLin = 1;

    /* Verifica se eh o primeiro movimento do Peao */
    if (peca->jogada == 0) {
        limiteMovLin = 2;
    }

    if (auxDeltaLin <= limiteMovLin && auxDeltaLin > 0) {
        Peca *destino = jogo->tabuleiro[peca->linha + movDeltaLin][peca->coluna + deltaCol];
        if ((deltaCol > 0 && destino != NULL) || (deltaCol == 0 && destino == NULL)) {
            /* Tomar peca do adversario so eh possivel na diagonal
             * Da mesma forma, movimento na diagonal so eh possivel se for tomar peca do adversario
             */
             movimento_valido = 1;
        }
    }
    return movimento_valido;
}

/* Funcao geral para validacao demovimentos
 * Esta funcao recebe como ultimo parametro um ponteiro para uma funcao que faz a verificacao
 * de movimento especifica de uma peca.
 */
int checkMovGeral(void *aux_jogo, int (*check)(Jogo *, int, int)) {
    Jogo *jogo = (Jogo*) aux_jogo;
    Peca* peca = jogo->peca_movida;
    int f_lin  = peca->linha;
    int f_col  = peca->coluna;
    int t_lin  = jogo->to_lin;
    int t_col  = jogo->to_col;
    int delta_lin    = abs(f_lin - t_lin);
    int delta_col    = abs(f_col - t_col);
    int delta_global = delta_lin + delta_col;

    /* Variavel de retorno: inicializado como "false" */
    int movimento_valido = 0;

    /* Verifica se houve movimento */
    if (delta_global > 0) {
        int mov_barrado = 0;
        /* Verificao especifica da peca */
        if (check(jogo, delta_lin, delta_col)) {
            /*
                Valido, mas deve verificar se ha obstaculo, exceto para o Cavalo, que pode 'pular'
                por sobre as outras pecas.
                A ultima posicao do movimento nao eh testada pois pode haver captura de peca
                inimiga.
            */
            if (tolower(peca->simbolo) != 'h') {
                int sentido_lin  = (f_lin < t_lin)? 1 : (f_lin == t_lin)? 0 : -1;
                int sentido_col  = (f_col < t_col)? 1 : (f_col == t_col)? 0 : -1;
                int i, j;

                j = f_col + sentido_col;
                i = f_lin + sentido_lin;
                while (i != t_lin || j != t_col) {
                    if(jogo->tabuleiro[i][j] != NULL) {
                        mov_barrado = 1;
                        break;
                    }
                    i += sentido_lin;
                    j += sentido_col;
                }

                /* Verifica resultado da varredura do caminho */
                if (mov_barrado == 0) {
                    movimento_valido = 1;
                } else {
                    sprintf(jogo->mensagem, "Movimento bloqueado.");
                }
            }
        } else {
            sprintf(jogo->mensagem, "Movimento invalido.");
        }
    } else {
        sprintf(jogo->mensagem, "A peca nao pode permanecer no mesmo lugar.");
    }

    return movimento_valido;
}

/* Valida movimento das torres */
int checkMovTorre(void *aux_jogo) {
    return checkMovGeral(aux_jogo, checkPadraoTorre);
}

/* Valida movimento dos bispo */
int checkMovBispo(void *aux_jogo) {
    return checkMovGeral(aux_jogo, checkPadraoBispo);
}

/* Valida movimento dos bispo */
int checkMovPeao(void *aux_jogo) {
    return checkMovGeral(aux_jogo, checkPadraoPeao);
}

/* Valida movimento STUB (para testes) */
int checkMovSTUB(void *aux_jogo) {
    return 1;
}
