/* Joao Luis */
/* Turma 3 */
/* CES-11: Algoritmos e Estruturas de Dados */
/* Exercício 8: PERT */

/* Programa compilado com gcc version 8.3.0 (Ubuntu 8.3.0-6ubuntu1~18.04.1) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// numero maximo de vertices
#define MAX 50

// na dfs, temos os 3 estados: nao visitado, sendo visitado e já visitado:
// representados pelos defines a seguir
#define N_VISITADO 0
#define VISITANDO 1
#define VISITADO 2

// inteiro que armazenará o estado de um vértice
int estado[MAX];

// struct que representa uma lista de vetor simples
typedef struct Lista
{
    int ind[MAX];
    int tamanho;
} lista;

// struct que representa cada vertice
struct Tarefa
{
    char rotulo;
    char descricao[35];
    int duracao;
};

// struct que representa o grafo implementado com matriz de adjacência
typedef struct Grafo
{
    int v; //numero de vertices do grafo
    struct Tarefa no[MAX];
    int matriz[MAX][MAX];
} Grafo;

//*************************************** FUNCAO INITGRAFO
// Funcao que iniciliza o grafo, com tamanho 0 e todos os elementos da matriz 0 (sem aresta)
// se grafo->matriz[i][j] = 1, existe uma aresta i->j
// se for igual a 0, nao existe.
//***************************************

void InitGrafo(Grafo *grafo)
{
    grafo->v = 0;
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            grafo->matriz[i][j] = 0;
}

//***************************************

//*************************************** FUNCAO INDICE
// Funcao que retorna o indice de um vertice do grafo, a partir de seu rotulo.
// caso o rotulo nao tenha sido implementado ainda, a funcao retorna -1
//***************************************

int Indice(Grafo *grafo, char rotulo)
{
    for (int i = 0; i < grafo->v; i++)
    {
        if (grafo->no[i].rotulo == rotulo)
            return i;
    }
    return -1;
}

//***************************************

//*************************************** FUNCAO NOVONOH
// Funcao que cria um novo vertice no grafo, com rotulo, descricao e duracao.
// Nessa funcao, nao se considera ainda os precedentes, a fim de evitar casos em que
// o precedente utilizado so seja criado depois no input
// assim, primeiro criaremos todos os vertices, depois atribuiremos as arestas
//***************************************

void NovoNoh(FILE *output, Grafo *grafo, char rotulo, char descricao[], int duracao)
{
    struct Tarefa novaTarefa;
    novaTarefa.rotulo = rotulo;
    strcpy(novaTarefa.descricao, descricao);
    novaTarefa.descricao[34] = '\0';
    novaTarefa.duracao = duracao;
    grafo->no[grafo->v] = novaTarefa;
    grafo->v++;
}

//***************************************

//*************************************** FUNCAO PRINTARORDENACAO
// Funcao que printa a ordenação topologica, recebendo a lista
//***************************************

void PrintarOrdenacao(FILE *output, Grafo *grafo, lista *L)
{
    fprintf(output, "UMA ORDENACAO TOPOLOGICA:\n\n");
    for (int i = 0; i < L->tamanho; i++)
    {
        fprintf(output, "%c%c", grafo->no[L->ind[i]].rotulo, (i == L->tamanho - 1 ? '\n' : ' '));
    }
}

//***************************************

//*************************************** FUNCAO PRINTARCICLO
// Funcao que printa o ciclo, recebendo a lista que o armazenou
//***************************************

void PrintarCiclo(FILE *output, Grafo *grafo, lista *ciclo)
{
    fprintf(output, "UM CICLO: \n\n");
    for (int i = 0; i < ciclo->tamanho; i++)
    {
        fprintf(output, "%c%c", grafo->no[ciclo->ind[i]].rotulo, (i == ciclo->tamanho - 1 ? '\n' : ' '));
    }
}
//***************************************

//*************************************** FUNCAO PRECEDENCIA
// Funcao que estabelece as arestas.
// Ela recebe o grafo, e a matriz de precedencias, isto é, uma matriz de caracteres do tipo:
// [.]
// [A,B,C]
// [B,H]
// [E,I]
//***************************************

void Precedencia(FILE *output, Grafo *grafo, char prec[MAX][110])
{
    for (int i = 0; i < grafo->v; i++)
    {
        // testa se existe algum precedente
        if (prec[i][0] != '.')
        {
            for (int j = 0; j < strlen(prec[i]); j += 2)
            {
                int indice = Indice(grafo, prec[i][j]);
                // teste de erro
                if (indice != -1)
                    grafo->matriz[indice][i] = 1;
                else
                    fprintf(output, "ERRO: Nao encontrada tarefa de rotulo %c\n", prec[i][j]);
            }
        }
    }
}

//***************************************

//*************************************** FUNCAO INSERIRPRIMEIRO
// Funcao que recebe uma lista de inteiros e um elemento,
// e insere-o na primeira posição
//***************************************

void InserirPrimeiro(int ind, lista *lista)
{
    for (int i = lista->tamanho; i > 0; i--)
    {
        lista->ind[i] = lista->ind[i - 1];
    }
    lista->ind[0] = ind;
    lista->tamanho++;
}

//***************************************

//*************************************** FUNCAO CHECARLISTA
// Funcao que um elemento e uma lista, retorna
// true se o elemento estiver na lista
// false se o elemento n estiver na lista
//***************************************

bool ChecarLista(int check, lista *lista)
{
    for (int i = 0; i < lista->tamanho; i++)
    {
        if (lista->ind[i] == check)
            return true;
    }
    return false;
}

//***************************************

//*************************************** FUNCAO LISTA
// Funcao inicializa uma lista L com tamanho 0 e retorna L
//***************************************

lista Lista()
{
    lista L;
    L.tamanho = 0;
    return L;
}

//***************************************

//*************************************** FUNCAO DFS
// Funcao que recebe um grafo, uma lista e um indice a ser testado.
// Como o nome indica, é uma busca em profundidade.
// Entretanto, alterou-se um pouco o algoritmo para conseguir a ordenacao topologica.
// Basicamente, chama-se recursivamente todos os adjacentes nao visitados de um vertices
// e, ao final disso, insere o vertice na lista
//***************************************

void dfs(Grafo *grafo, bool visitado[], int indice, lista *L)
{
    visitado[indice] = true;
    for (int i = 0; i < grafo->v; i++)
    {
        if (grafo->matriz[indice][i])
        {
            if (!visitado[i])
            {
                dfs(grafo, visitado, i, L);
            }
        }
    }
    InserirPrimeiro(indice, L);
}

//***************************************

//*************************************** FUNCAO CICLO
// Funcao que recebe um grafo, uma lista e um indice a ser testado.
// Como o nome indica, é um teste de aciclicidade usando uma busca em profundidade.
// Se a funcao retornar true, significa que o grafo é ciclico.
// O teste de ciclo é, se, quando eu partir de um vertice x,
// até eu terminar sua busca, eu nao posso encontrar x novamente.
// Assim, todos os elementos, ao serem chamados pela funcao, marcam o elemento como VISITANDO
// E, ao final do dfs, o elemento é marcado como VISITADO
// Se um adjacente de x tiver marcado como VISITANDO, é um ciclo
// e insere-se todos os elementos na lista ciclo
//***************************************

bool Ciclo(Grafo *grafo, int indice, lista *ciclo)
{
    // Armazena se o ciclo esta completo e pode parar de inserir na lista
    static bool CompletouCiclo = false;
    estado[indice] = VISITANDO;
    for (int i = 0; i < grafo->v; i++)
    {
        if (grafo->matriz[indice][i] != 0)
        {
            printf("Testando: %c %c\n", grafo->no[indice].rotulo, grafo->no[i].rotulo);
            if (estado[i] == N_VISITADO)
            {
                if (Ciclo(grafo, i, ciclo))
                {
                    // encontrou ciclo, insere todos na lista
                    if (ChecarLista(i, ciclo))
                    {
                        // se encontrar um cara que ja ta na lista, para de inserir e insere novamente
                        CompletouCiclo = true;
                        InserirPrimeiro(i, ciclo);
                    }

                    if (!CompletouCiclo) // enquanto nao encontrar o cara q ja ta na lista, insere
                        InserirPrimeiro(i, ciclo);

                    return true;
                }
            }
            else if (estado[i] == VISITANDO)
            {
                // a condicao de ciclo eh um filho estar no estado "visitando"
                if (!CompletouCiclo)
                    InserirPrimeiro(i, ciclo);
                return true;
            }
        }
    }
    estado[indice] = VISITADO;
    return false;
}

//***************************************

//*************************************** FUNCAO TESTACICLO
// Funcao que chama a funcao Ciclo para todo vertice nao visitado
// se tiver ciclo, ele printará
//***************************************

bool TestaCiclo(FILE *output, Grafo *grafo)
{
    // booleana que armazena se tem ciclo ou nao
    bool temCiclo = false;
    // lista que armazena o ciclo
    lista ciclo;
    bool visitado[grafo->v];
    for (int i = 0; i < grafo->v; i++)
        visitado[i] = false;
    for (int i = 0; i < grafo->v && !temCiclo; i++)
        if (!visitado[i])
        {
            // testa se tem ciclo
            ciclo = Lista();
            if (Ciclo(grafo, i, &ciclo))
                temCiclo = true;
        }
    if (temCiclo)
    {
        fprintf(output, "ERRO: O grafo eh ciclico\n");
        PrintarCiclo(output, grafo, &ciclo);
    }
    return temCiclo;
}
//***************************************

//*************************************** FUNCAO ORDENACAOTOPOLOGICA
// cria-se uma booleana para marcar os visitados
// inicializa todos com false
// chama a funcao dfs para todos os nao visitados
// no final, teremos a lista com a ordenacao
// atente-se que nao testa-se o ciclo aqui, mas sim antes de tentar fazer essa ordenacao
// como indicado na main.
//***************************************

void OrdenacaoTopologica(Grafo *grafo, lista *L)
{
    bool visitado[grafo->v];
    for (int i = 0; i < grafo->v; i++)
        visitado[i] = false;
    for (int i = 0; i < grafo->v; i++)
    {
        if (!visitado[i])
            dfs(grafo, visitado, i, L);
    }
}

//***************************************

//*************************************** FUNCAO TMT
// Essa funcao recebe o grafo e a ordenacao topologica.
// A ideia é: para cada vertice x, TMT[x] = custo[x] + max{TMT[y]}, tal que existe
// aresta y->x. Assim, segue a sequencia da esquerda para direita na lista, pois
// sempre que chegarmos num elemento x da ordenação topologica, todos os TMT's dos vertices y tais que
// y->x, já terão sido calculados.
// Alem disso, se salva o maximo escolhido como antecessor do elemento. Assim, torna mais facil
// a busca final para printar os vertices escolhidos.
//***************************************

void TMT(FILE *output, Grafo *grafo, lista *L)
{
    fprintf(output, "\n\nCAMINHO CRITICO:\n\nTAREFA        DESCRICAO           DURACAO\n\n");
    // max armazena o tmt maximo, ou seja, a resposta do problema
    int max = 0;
    // inicializa o vetor tmt e marca todos como 0 no inicio
    int tmt[grafo->v];
    for (int i = 0; i < grafo->v; i++)
        tmt[i] = 0;
    // antecessor marcará todos os antecessores do melhor caminho. Ou seja,
    // antecessor[x] grava o indice do y que levou a x pelo caminho maximo.
    // seq grava o caminho de tras pra frente
    int antecessor[grafo->v], seq[grafo->v + 1];
    // marca o antecessor do primeiro da ordenação como -1 (sem antecessor)
    antecessor[L->ind[0]] = -1;
    // itera-se sobre os elementos da lista
    for (int i = 0; i < L->tamanho; i++)
    {
        // salva o maximo dos adjacentes y tais que y->x
        // para isso, compara todos os vertices y que estão antes de x na ordenação topologica
        int max_adj = 0;
        for (int j = 0; j < i; j++)
        {
            if (grafo->matriz[L->ind[j]][L->ind[i]] && max_adj < tmt[L->ind[j]])
            {
                max_adj = tmt[L->ind[j]];
                // salva o antecessor
                antecessor[L->ind[i]] = L->ind[j];
            }
        }
        // calcula o tmt utilizando o maximo adjacente
        tmt[L->ind[i]] = grafo->no[L->ind[i]].duracao + max_adj;
    }
    // saveId armazena o indice do vertice de maior TMT
    int saveId;
    for (int i = 0; i < L->tamanho; i++)
        if (max < tmt[i])
        {
            max = tmt[i];
            saveId = i;
        }
    // o inteiro quantos armazena quantos vertices sao necessarios para se chegar à saveId
    int quantos = 0;
    while (saveId != -1)
    {
        seq[quantos++] = saveId;
        saveId = antecessor[saveId];
    }
    // printa-se a ordem de tras pra frente
    for (int i = quantos - 1; i >= 0; i--)
    {
        fprintf(output, " %34s%4d\n", grafo->no[seq[i]].descricao, grafo->no[seq[i]].duracao);
    }
    fprintf(output, "                                   ----\n");
    fprintf(output, "TEMPO MINIMO PARA O PROJETO:         %d semanas", max);
}

//***************************************

//*************************************** FUNCAO MAIN
int main()
{
    FILE *input = fopen("C:\\Lab8\\entrada8.txt", "r");
    FILE *output = fopen("C:\\Lab8\\joaosarmento8.txt", "w");
    char texto[71];
    char prec[MAX][110];
    int nVert = 0;
    // Le as primeiras linha
    for (int i = 0; i < 7; i++)
        fgets(texto, 71, input);
    // inicializa o grafo
    Grafo grafo;
    InitGrafo(&grafo);
    // acabou marca se chegou ao fim do input
    bool acabou = false;
    while (!acabou)
    {
        char teste = fgetc(input);
        if (teste == '-')
            acabou = true;
        else
        {
            char rotulo, descricao[35];

            int duracao;
            for (int i = 0; i < 34; i++)
                descricao[i] = fgetc(input);
            descricao[34] = '\0';
            rotulo = descricao[1];
            fscanf(input, "%d", &duracao);
            fscanf(input, "%s", prec[nVert++]);
            teste = fgetc(input);
            // cria o vertices
            NovoNoh(output, &grafo, rotulo, descricao, duracao);
        }
    }
    // cria as arestas
    Precedencia(output, &grafo, prec);
    // printa cabecalho
    fprintf(output, "INSTITUTO TECNOLOGICO DE AERONAUTICA\n"
                    "JOAO SARMENTO - T3\n"
                    "ARMANDO GOUVEIA\n"
                    "VEM FERIAS\n\n");
    for (int i = 0; i < 60; i++)
        fprintf(output, "-");
    fprintf(output, "\n\n");

    for (int i = 0; i < MAX; i++)
        estado[i] = N_VISITADO;
    if (!TestaCiclo(output, &grafo))
    {
        // nao teve ciclo, pode criar a ordenacao topologica
        lista L = Lista();
        OrdenacaoTopologica(&grafo, &L);      // aqui se obtem a lista com a ordenacao topologica
        PrintarOrdenacao(output, &grafo, &L); // aqui se printa a lista
        TMT(output, &grafo, &L);              // aqui encontra-se o TMT do grafo e o CPM
    }
    fclose(input);
    fclose(output);
}

//***************************************
