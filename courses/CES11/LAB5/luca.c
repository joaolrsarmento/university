/* Luca de Souza Pires                      */
/* Turma 3                                  */
/*                                          */
/* Exercicio 5: Livro                       */

/* Programa compilado com gcc version 7.4.0 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*---------------------------------------------------*/
//Contador e vetor utilizados na funcao para printar
//a LISTA com os indices
/*---------------------------------------------------*/

int k = 0;
int vet[7];

/*---------------------------------------------------*/
//Struct para armazenar o noh da arvore
/*---------------------------------------------------*/
typedef struct noh noh;

struct noh
{
    char secoes[22];
    noh *pai;
    noh *fesq;
    noh *idir;
};
noh *raiz;

/*---------------------------------------------------*/
//                      BUSCA
/*---------------------------------------------------*/
/*
Funcao que percorre a arvore e retorna o noh no qual
esta armazenado o nome buscado.
*/

noh *Busca(char nome_buscado[22], noh *x)
{
    noh *p;
    noh *resposta;
    if (strcmp(x->secoes, nome_buscado) == 0)
        return x;
    else
    {
        resposta = NULL;
        p = x->fesq;
        while (p != NULL && resposta == NULL)
        {
            resposta = Busca(nome_buscado, p);
            p = p->idir;
        }
        return resposta;
    }
}

/*---------------------------------------------------*/
//                    PreOrdem
/*---------------------------------------------------*/
/*
Funcao que percorre a arvore em Pre Ordem e printa a
informacao de cada noh com os respectivos indices
*/
void PreOrdem(noh *x, FILE *saida)
{
    int cont = 1;
    if (x == NULL)
        return;
    while (x != NULL)
    {
        if (k == 0)
            k++;
        else
        {
            vet[k] = cont;
            k++;
            for (int i = 1; i < k; i++)
                fprintf(saida, "%d.", vet[i]);
        }
        fprintf(saida, "      %s\n", x->secoes);
        PreOrdem(x->fesq, saida);
        x = x->idir;
        k--;
        cont++;
    }
}

/*---------------------------------------------------*/
//                     REMOVER
/*---------------------------------------------------*/
/*
Funcao que remove determinado noh e sua sub-arvore
correspondente
*/
void Remover(noh *x)
{
    noh *p;
    p = x->fesq;
    while (p != NULL)
    {
        Remover(p);
        p = p->idir;
    }
    free(x);
    return;
}

/*---------------------------------------------------*/
//                       MAIN
/*---------------------------------------------------*/

int main(void)
{
    /*---------------------------------------------------*/
    /*Abertura dos arquivos*/
    /*---------------------------------------------------*/
\
    FILE *entrada = fopen("entrada5.txt", "r");
    FILE *saida = fopen("luca5.txt", "w");

    /*---------------------------------------------------*/
    /*Escrita das linhas iniciais da saida*/
    /*---------------------------------------------------*/

    fprintf(saida, "Livro do Luca\n");
    fprintf(saida, "O melhor livro de todos\n");
    fprintf(saida, "Relatorio\n");
    fprintf(saida, "---------------------------------------------------\n");

    /*---------------------------------------------------*/
    /*Pular linhas iniciais da entrada*/
    /*---------------------------------------------------*/

    char linhas_inutilizadas[72];
    for (int i = 0; i < 4; i++)
        fgets(linhas_inutilizadas, 52, entrada);

    /*---------------------------------------------------*/
    /*Ler o comando*/
    /*---------------------------------------------------*/
    char comando[22];
    char nome_secao[22];
    char nome_secao_aux[22];

    int cont = 0;

    while (strcmp(comando, "FIM") != 0)
    {
        fscanf(entrada, "%s ", comando);
        /*Declaracao do novo noh*/
        noh *novo_noh = (noh *)malloc(sizeof(noh));
        novo_noh->fesq = NULL;
        novo_noh->idir = NULL;
        novo_noh->pai = NULL;

        /*---------------------------------------------------*/
        //                     TITULO
        /*---------------------------------------------------*/
        /*
        Adiciona o titulo como raiz da arvore. Caso ja haja
        algum titulo, esse se torna parte da sub-arvore com
        o novo titulo como raiz
        */
        if (strcmp(comando, "TITULO") == 0)
        {
            fscanf(entrada, "%s ", nome_secao);
            strcpy(novo_noh->secoes, nome_secao);

            //Caso em que nao foi adicionado titulo ainda
            if (raiz == NULL)
                raiz = novo_noh;

            //Caso em que ja existe titulo
            else
            {
                noh *p = raiz;
                raiz = novo_noh;
                novo_noh->fesq = p;
                p->pai = raiz;
            }
        }

        /*---------------------------------------------------*/
        //                    INSERIR
        /*---------------------------------------------------*/
        /*
        Insere determinado noh na arvore. Pode ser inserido
        como irmao direito de algum noh ou como filho esquerdo
        */
        if (strcmp(comando, "INSERIR") == 0)
        {
            fscanf(entrada, "%s ", nome_secao);
            strcpy(novo_noh->secoes, nome_secao);

            char posicao[22];
            fscanf(entrada, "%s ", posicao);
            fscanf(entrada, "%s ", nome_secao_aux);

            //Comando antes de inserir o titulo
            if (raiz == NULL)
            {
                fprintf(saida, "ERRO: Titulo nao encontrado\n");
                fprintf(saida, "--------------------------------------------------\n");
            }

            else
            {
                noh *noh_aux = Busca(nome_secao_aux, raiz);

                //Inserir com item de referencia que nao esta na arvore
                if (noh_aux == NULL)
                {
                    fprintf(saida, "ERRO: nao encontrado item %s\n", nome_secao_aux);
                    fprintf(saida, "--------------------------------------------------\n");
                }

                //Caso SUB
                else if (strcmp(posicao, "SUB") == 0)
                {
                    //Nao ha filhos
                    if (noh_aux->fesq == NULL)
                    {
                        noh_aux->fesq = novo_noh;
                        novo_noh->pai = noh_aux;
                    }

                    //Ja existem filhos
                    else
                    {
                        noh *p = noh_aux->fesq;
                        novo_noh->pai = noh_aux;
                        novo_noh->idir = p;
                        noh_aux->fesq = novo_noh;
                    }
                }

                else if (strcmp(posicao, "SEGUINTE_A") == 0)
                {
                    //Inserir seguinte_a titulo (erro)
                    if (noh_aux == raiz)
                    {
                        fprintf(saida, "ERRO: Operação inválida\n");
                        fprintf(saida, "--------------------------------------------------\n");
                    }
                    //Inserir normalmente
                    else
                    {
                        novo_noh->idir = noh_aux->idir;
                        novo_noh->pai = noh_aux->pai;
                        noh_aux->idir = novo_noh;
                    }
                }
            }
        }

        /*---------------------------------------------------*/
        //                    REMOVER
        /*---------------------------------------------------*/
        /*
        Remove algum noh da arvore e realoca os demais
        */
        if (strcmp(comando, "REMOVER") == 0)
        {
            //Comando antes de inserir titulo
            if (raiz == NULL)
            {
                fprintf(saida, "ERRO: Titulo nao encontrado\n");
                fprintf(saida, "--------------------------------------------------\n");
            }

            else
            {

                fscanf(entrada, "%s ", nome_secao);
                noh *p = Busca(nome_secao, raiz);

                //Remover item que nao existe na arvore
                if (p == NULL)
                {
                    fprintf(saida, "ERRO: nao encontrado item %s\n", nome_secao);
                    fprintf(saida, "--------------------------------------------------\n");
                }

                else
                {
                    //Caso em que o titulo eh removido
                    if (p == raiz)
                    {
                        Remover(p);
                        raiz = NULL;
                    }

                    else
                    {
                        noh *q = p->pai->fesq;

                        //So tem um filho
                        if (q == p)
                        {
                            p->pai->fesq = p->idir;
                            Remover(p);
                        }

                        //Tem mais de um filho
                        else
                        {
                            while (q->idir != p)
                                q = q->idir;
                            q->idir = p->idir;
                            Remover(p);
                        }
                    }
                }
            }
        }

        /*---------------------------------------------------*/
        //                    TRANSFERIR
        /*---------------------------------------------------*/
        /*
        Transfere determinado noh para outra posicao. Pode ser
        para irmao direito ou filho esquerdo de outro noh
        */
        if (strcmp(comando, "TRANSFERIR") == 0)
        {
            fscanf(entrada, "%s ", nome_secao);
            char posicao[22];
            fscanf(entrada, "%s ", posicao);
            fscanf(entrada, "%s ", nome_secao_aux);

            //Comando antes de inserir titulo
            if (raiz == NULL)
            {
                fprintf(saida, "ERRO: Titulo nao encontrado\n");
                fprintf(saida, "--------------------------------------------------\n");
            }

            else
            {
                noh *noh_transferido = Busca(nome_secao, raiz);
                noh *noh_aux = Busca(nome_secao_aux, raiz);

                //Nao existe item a ser transferido (erro)
                if (noh_transferido == NULL)
                {
                    fprintf(saida, "ERRO: nao encontrado item %s\n", nome_secao);
                    fprintf(saida, "--------------------------------------------------\n");
                }

                //Nao existe item de referencia (erro)
                if (noh_aux == NULL)
                {
                    fprintf(saida, "ERRO: nao encontrado item %s\n", nome_secao_aux);
                    fprintf(saida, "--------------------------------------------------\n");
                }

                if (strcmp(posicao, "SUB") == 0 && noh_aux != NULL && noh_transferido != NULL)
                {
                    if (noh_aux != NULL && noh_transferido != NULL)
                    {
                        noh *pai = noh_transferido->pai;
                        if (noh_transferido == pai->fesq)
                            pai->fesq = noh_transferido->idir;
                        else
                        {
                            noh *p = noh_transferido->pai->fesq;
                            while (p->idir != noh_transferido)
                                p = p->idir;
                            p->idir = noh_transferido->idir;
                        }
                    }
                    noh_transferido->idir = noh_aux->fesq;
                    noh_aux->fesq = noh_transferido;
                    noh_transferido->pai = noh_aux;
                }

                if (strcmp(posicao, "SEGUINTE_A") == 0 && noh_aux != NULL && noh_transferido != NULL)
                {
                    if (noh_aux != NULL && noh_transferido != NULL && noh_aux != raiz)
                    {
                        noh *pai = noh_transferido->pai;
                        if (noh_transferido == pai->fesq)
                            pai->fesq = noh_transferido->idir;
                        else
                        {
                            noh *p = noh_transferido->pai->fesq;
                            while (p->idir != noh_transferido)
                                p = p->idir;
                            p->idir = noh_transferido->idir;
                        }
                    }
                    if (noh_aux == raiz)
                    {
                        fprintf(saida, "ERRO: Operacao invalida\n");
                        fprintf(saida, "--------------------------------------------------\n");
                    }
                    else
                    {
                        noh_transferido->idir = noh_aux->idir;
                        noh_aux->idir = noh_transferido;
                        noh_transferido->pai = noh_aux->pai;
                    }
                }
            }
        }

        /*---------------------------------------------------*/
        //                    LISTA
        /*---------------------------------------------------*/
        /*
        Printa a arvore em Pre Ordem com os determinados indices
        */
        if (strcmp(comando, "LISTA") == 0)
        {
            cont++;
            fprintf(saida, "LISTA %d\n", cont);
            fprintf(saida, "\n");
            PreOrdem(raiz, saida);
            fprintf(saida, "--------------------------------------------------\n");
        }
    }

    fclose(entrada);
    fclose(saida);
    return 0;
}