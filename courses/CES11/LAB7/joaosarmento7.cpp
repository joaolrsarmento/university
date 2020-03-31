/* Joao Luis */
/* Turma 3 */
/* CES-11: Algoritmos e Estruturas de Dados */
/* Exercício 7: Fibra Ótica  */

/* Programa compilado com gcc version 8.3.0 (Ubuntu 8.3.0-6ubuntu1~18.04.1) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <values.h>

// inteiro representando o máximo valor inteiro
const int INF = MAXINT/2;

// número máximo de vertices
#define MAX 150

// struct que define as informação que cada vertice armazena
typedef struct vert{
    char nome[20];
    int adj[MAX]; // representa as relações do vertice com os outros (matriz de adjacência)
} Vert;

// struct que representa o grafo
typedef struct graph{
    Vert vert[MAX];
    int nVert;
} Graph;

// definicao de vertice
typedef int vertex;

// vetores globais para o algoritmo de prim
int visited[MAX];
int cost[MAX];

//--------------------------------------------------
//    Funcao InitGraph
// Funcao que inicializa uma grafo, 
// atribuindo o numero de vertices a 0
//--------------------------------------------------

void InitGraph(Graph *graph){
    graph->nVert = 0;
}

//--------------------------------------------------

//--------------------------------------------------
//    Funcao swap
// Funcao que recebe dois ponteiros para inteiros e troca seus valores
//--------------------------------------------------

void swap(int *x, int *y){ 
   int temp;
   temp=*x;
   *x=*y;
   *y=temp;
}

//--------------------------------------------------

//--------------------------------------------------
//    Funcao newEdge
// Funcao que recebe duas strings e um custo e
// cria uma aresta entre eles com o custo desejado
//--------------------------------------------------

void newEdge(FILE *output, Graph *graph, char b1[], char b2[], int cost){
    if(graph->nVert == MAX){
        fprintf(output, "ERRO: Numero maximo de predios\n");
        return;
    }
    // booleanas que armazenam se as strings b1 e b2 ja estao no grafo
    bool foundB1 = false;
    bool foundB2 = false;
    // indice da string b1 e da string b2 no grafo
    vertex B1 = -1;
    vertex B2 = -1;

    for(vertex w = 0; w < graph->nVert; w++){
        if(!strcmp(graph->vert[w].nome, b1) || !strcmp(graph->vert[w].nome, b2)){
            // se b1 ja estiver no grafo
            if(!strcmp(graph->vert[w].nome, b1)){
                foundB1 = true;
                B1 = w;
            }
            // se b2 ja estiver no grafo
            else{
                foundB2 = true;
                B2 = w;
            }
        }
    }
    // se nao tiver encontrado b1, adiciona ele ao grafo
    if(!foundB1){
        B1 = graph->nVert;
        strcpy(graph->vert[B1].nome, b1);
        graph->nVert++;
        // marca as relações de b1 com os outros como "sem relação", ou seja, -1
        for(vertex w = 0; w < graph->nVert; w++){
            graph->vert[w].adj[B1] = -1;
            graph->vert[B1].adj[w] = -1;
        }
    }
    // Mesma coisa do b1
    if(!foundB2){
        B2 = graph->nVert;
        strcpy(graph->vert[B2].nome, b2);
        graph->nVert++;
        for(vertex w = 0; w < graph->nVert; w++){
            graph->vert[w].adj[B2] = -1;
            graph->vert[B2].adj[w] = -1;
        }
    }
    // cria a relação, sem ser direcionada, entre b1 e b2
    graph->vert[B1].adj[B2] = cost;
    graph->vert[B2].adj[B1] = cost;
}

//--------------------------------------------------

//--------------------------------------------------
//    Funcao Prim
// Funcao que acha uma MST e printa seu custo maximo,
// alem das arestas utilizadas para isso.
// Basicamente, selecionaremos um vertice x que ainda nao esta na nuvem
// e um vertice y que esta na nuvem. Assim, dentre todos esses vertices,
// escolheremos o que tem menor custo x -> y. Se tiver vários com o mesmo custo,
// escolhe-se alfabeticamente. Por fim, o primeiro cara a ser colocado na nuvem é
// escolhido alfabeticamente também.
//--------------------------------------------------

void Prim(Graph *graph, FILE *output){
    // armazena o custo da MST formada
    int res = 0;
    // armazena os indices das arestas utilizadas e os custos da aresta
    int ans[graph->nVert-1][3];
    for(int i = 0; i < graph->nVert; i++){
        // marca todos como nao visitados
        visited[i] = 0;
        // marca todos com custo infinito
        cost[i] = INF;
    }
    // string criada para comparar alfabeticamente os vertices que ainda nao estao na nuvem
    char compare[20] = "";
    int ind = 0;
    // ciclo que escolherá o primeiro cara a entrar na nuvem (alfabeticamente)
    for(int i = 0; i < graph->nVert; i++){
        if(!strcmp(compare, "") || strcmp(compare, graph->vert[i].nome) > 0){
            ind = i;
            strcpy(compare, graph->vert[i].nome);
        }
    }

    // variavel inteira que armazenará a quantidade de vertices na nuvem
    int many = 0;
    // primeiro cara a entrar na nuvem é assumido custo 0
    cost[ind] = 0;
    // salva o ultimo no escolhido no algoritmo para printar 
    int save;
    // ciclo do algoritmo, que colocará todos os vertices na nuvem
    for(int f = graph->nVert; f > 0; f--){
        // guarda o vertice escolhido no algoritmo, isto é, o vertice y fora da nuvem, que nao foi visitado.
        int node = -1;
        strcpy(compare, "");
        // procura, dentre os que nao estao na nuvem, o vertice y que recebe uma aresta da nuvem de menor custo,
        // se tiver varios com menor custo, escolhe-se alfabeticamente
        for(int i = 0; i < graph->nVert; i++){
            if(!visited[i] && (node == -1 || cost[i] < cost[node]) && (strcmp(compare, "") || strcmp(compare, graph->vert[i].nome)) > 0){
                node = i;
                strcpy(compare, graph->vert[i].nome);
            }
        }
        // coloca o vertice escolhido na nuvem
        visited[node] = 1;
        // se nao existe MST (grafo nao conexo, o custo desejado é infinito e sai-se do ciclo).
        if(cost[node] == INF){
            res = INF;
            fprintf(output, "ERRO: O grafo não é conexo, não é possivel encontrar a MST\n");
            return;
        }
        // soma o custo da aresta selecionada ao resultado desejado
        res += cost[node];
        // se o vertice nao for o primeiro a entrar na nuvem, salva-se o indices das arestas selecionadas
        // e o custo dela
        if(cost[node]){
            ans[many][0] = save;
            ans[many][1] = node;
            ans[many][2] = cost[node];
            many++;
            // printa-se a aresta escolhida e o custo dela
            fprintf(output, "%-10s %-10s %3d\n", graph->vert[save].nome, graph->vert[node].nome, cost[node]);
        }
        // atualiza os custos das arestas que saem da nuvem
        for(int i = 0; i < graph->nVert; i++){
            if(graph->vert[node].adj[i] != -1 && cost[i] > graph->vert[node].adj[i]){
                cost[i] = graph->vert[node].adj[i];
            }
        }
        // salva o ultimo vertice escolhido
        save = node;
    }
    // printa custo total encontrado
    fprintf(output, "\nCusto total: %d\n\n", res);
    for(int i = 0; i < 39; i++) fprintf(output, "-");
    fprintf(output, "\n");
    fprintf(output, "Ordem crescente de custos\n");
    for(int i = 0; i < 39; i++) fprintf(output, "-");
    fprintf(output, "\n");
    // ordena as arestas em ordem crescente de custos por BubbleSort
    for(int i = 0; i < graph->nVert - 1; i++){
        for(int j = 0; j < graph->nVert - 2; j++){
            if(ans[j][2] > ans[j+1][2]){
                swap(&ans[j][0], &ans[j+1][0]);
                swap(&ans[j][1], &ans[j+1][1]);
                swap(&ans[j][2], &ans[j+1][2]);
            }
        }
    }
    // printa as arestas em ordem crescente de custos
    for(int i = 0; i < graph->nVert - 1; i++){
        fprintf(output, "%-10s %-10s %3d\n", graph->vert[ans[i][0]].nome, graph->vert[ans[i][1]].nome, ans[i][2]);
    }
}

//--------------------------------------------------

//--------------------------------------------------
//    Funcao main
//--------------------------------------------------

int main()
{
    FILE *input = fopen("C:\\Lab7\\entrada7.txt", "r");
    FILE *output = fopen("C:\\Lab7\\joaosarmento7.txt", "w");
    char building1[11], building2[11], message[70];
    for(int i = 0; i < 6; i++) fgets(message, 70, input);
    int cost;
    Graph graph; // cria o grafo e inicializa
    InitGraph(&graph);
    fprintf(output, "JOAO SARMENTO\n"
                    "T23-3\n"
                    "AS FERIAS CHEGARAM\n\n");
    for(int i = 0; i < 39; i++) fprintf(output, "-");
    fprintf(output, "\nOrdem de selecao pelo algoritmo\n");
    for(int i = 0; i < 39; i++) fprintf(output, "-");
    fprintf(output, "\n");
    while(!feof(input)){
        // le o input
        fscanf(input, "%s %s %d ", building1, building2, &cost);
        // cria nova aresta
        newEdge(output, &graph, building1, building2, cost);
    }
    // encontra e printa a MST
    Prim(&graph, output);
    fclose(input);
    fclose(output);
    return 0;
}

//--------------------------------------------------