/* Joao Luis */
/* Turma 3 */
/* CES-11: Algoritmos e Estruturas de Dados */
/* Exercício 6: Agenda */

/* Programa compilado com gcc version 8.3.0 (Ubuntu 8.3.0-6ubuntu1~18.04.1) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Macros que calculam filho esquerdo, filho direito e pai de um dado indice
#define fesq(i) (2 * i + 1)
#define fdir(i) (2 * i + 2)
#define pai(i) ((i - 1) / 2)

// Nó que representa cada tarefa
struct node
{
    char tarefa[71];
    int prioridade;
};

// Heap que representa a agenda
struct Heap
{
    struct node *v;
    int nElementos;
    int MAX;
};

// Prototipação das funcoes
void Insert(FILE *, struct Heap *, int, char[]);
void RemoveMax(FILE *, struct Heap *);
void Inicializar(FILE *, struct Heap *, int);
void Finalizar(FILE *, struct Heap *);
void SubirNaHeap(FILE *, struct Heap *, int);
void DescerNaHeap(FILE *, struct Heap *, int);
int Maximum(FILE *, struct Heap *);
bool HeapVazio(FILE *, struct Heap *);
bool HeapCheio(FILE *, struct Heap *);

//------------------------------------------------------------FUNCAO MAIN
int main()
{
    FILE *input = fopen("C:\\Lab6\\entrada6.txt", "r");
    FILE *output = fopen("C:\\Lab6\\joaosarmento6.txt", "w");
    char texto[71];
    int MAX;
    // Le as primeiras linhas e o numero maximo de elementos
    for (int i = 0; i < 5; i++)
        fgets(texto, 71, input);
    fscanf(input, "%d", &MAX);
    fgetc(input);
    for (int i = 0; i < 3; i++)
        fgets(texto, 71, input);
    // Cria a heap e inicializa
    struct Heap heap;
    Inicializar(output, &heap, MAX);
    char message[71];
    // Escreve cabeçalho
    fprintf(output, "INSTITUTO TECNOLOGICO DE AERONAUTICA\n"
                    "JOAO SARMENTO - T3\n"
                    "ARMANDO GOUVEIA\n"
                    "VEM FERIAS\n\n");
    for (int i = 0; i < 50; i++)
        fprintf(output, "-");
    fprintf(output, "\n");
    fprintf(output, "RESPOSTAS DAS CONSULTAS\n");
    for (int i = 0; i < 50; i++)
        fprintf(output, "-");
    fprintf(output, "\n");
    while (fscanf(input, "%s ", message) && strcmp(message, "FIM"))
    {
        if (!strcmp(message, "NOVA"))
        {
            int prioridade;
            char tarefa[71];
            fscanf(input, "%d ", &prioridade);
            fgets(tarefa, 71, input);
            // insere novo item na agenda
            Insert(output, &heap, prioridade, tarefa);
        }
        else if (!strcmp(message, "PROXIMA"))
        {
            // remove item de maxima prioridade da agenda e printa-o no output
            RemoveMax(output, &heap);
        }
    }
    fprintf(output, "\n");
    for (int i = 0; i < 50; i++)
        fprintf(output, "-");
    fprintf(output, "\n");
    // printa o que restou da agenda e libera todos
    fprintf(output, "FICA PARA O DIA SEGUINTE\n");
    for (int i = 0; i < 50; i++)
        fprintf(output, "-");
    fprintf(output, "\n");
    if (HeapVazio(output, &heap))
    {
        fprintf(output, "Agenda vazia! Nao restam tarefas para o dia seguinte.\n");
    }
    else
    {
        while (!HeapVazio(output, &heap))
        {
            RemoveMax(output, &heap);
        }
    }
    // libera a memoria alocada
    Finalizar(output, &heap);
    // libera os arquivos
    fclose(output);
    fclose(input);
    return 0;
}
//------------------------------------------------------------

//------------------------------------------------------------FUNCAO INSERT
// funcao checa, primeiro se tem espaço livre na agenda
// se tiver espaço, insere o novo item no final da heap
// sobe o elemento ate a posicao correta
//------------------------------------------------------------
void Insert(FILE *output, struct Heap *heap, int prioridade, char tarefa[])
{
    // checagem de erro
    if (HeapCheio(output, heap))
    {
        fprintf(output, "ERRO     Agenda cheia. Impossivel inserir.\n");
        return;
    }
    // coloca novo item no final da heap
    heap->v[heap->nElementos].prioridade = prioridade;
    strcpy(heap->v[heap->nElementos].tarefa, tarefa);
    heap->nElementos++;
    // sobe o novo item
    SubirNaHeap(output, heap, heap->nElementos - 1);
}
//------------------------------------------------------------

//------------------------------------------------------------FUNCAO REMOVEMAX
// Checa se a heap nao esta vazia
// coloca o ultimo elemento como raiz
// desce o ultimo elemento ate a posicao certa
// tira o elemento que era raiz primeiramente, e printa-o
//------------------------------------------------------------
void RemoveMax(FILE *output, struct Heap *heap)
{
    // checagem de erro
    if (HeapVazio(output, heap))
    {
        fprintf(output, "AVISO    Nao ha tarefas na agenda  :-)\n");
        return;
    }
    // pega a raiz
    int max = Maximum(output, heap);
    struct node aux_node = heap->v[max];
    // troca a raiz pelo ultimo
    heap->v[max] = heap->v[heap->nElementos - 1];
    heap->v[heap->nElementos - 1] = aux_node;
    heap->nElementos--;
    // printa o elemento de maxima prioridade
    fprintf(output, "%2d       %s", heap->v[heap->nElementos].prioridade, heap->v[heap->nElementos].tarefa);
    // desce a nova raiz ate a posicao correta
    DescerNaHeap(output, heap, max);
}
//------------------------------------------------------------

//------------------------------------------------------------FUNCAO INICIALIZAR
// funcao que inicializa a heap, alocando dinamicamente o vetor e colocando os valores iniciais
//------------------------------------------------------------
void Inicializar(FILE *output, struct Heap *heap, int MAX)
{
    heap->v = (struct node *)malloc(MAX * sizeof(struct node));
    heap->nElementos = 0;
    heap->MAX = MAX;
}
//------------------------------------------------------------

//------------------------------------------------------------FUNCAO FINALIZAR
// funcao que libera memoria alocada
//------------------------------------------------------------
void Finalizar(FILE *output, struct Heap *heap)
{
    free(heap->v);
}
//------------------------------------------------------------

//------------------------------------------------------------FUNCAO SUBIRNAHEAP
// funcao que coloca o elemento na posicao correta, seguindo o algoritmo:
// checa se o indice analisado ja nao eh a raiz
// compara o elemento com o pai
// se a prioridade do elemento for maior que a do pai, trocam-se o pai pelo filho e
// chama a funcao novamente para o novo pai
//------------------------------------------------------------
void SubirNaHeap(FILE *output, struct Heap *heap, int ind)
{
    // checagem de erro e condicao correta de troca
    if (ind > 0 && heap->v[pai(ind)].prioridade < heap->v[ind].prioridade)
    {
        // efetua a troca
        struct node aux_node = heap->v[pai(ind)];
        heap->v[pai(ind)] = heap->v[ind];
        heap->v[ind] = aux_node;
        // chama a funcao para o pai
        SubirNaHeap(output, heap, pai(ind));
    }
}
//------------------------------------------------------------

//------------------------------------------------------------FUNCAO DESCERNAHEAP
// funcao que desce um elemento de um dado indice para a posicao correta
// checa-se primeiramente se ele já nao eh o ultimo elemento
// compara o elemento com os dois filhos, escolhe-se o maior deles
// compara o maior deles com o elemento, se o pai for menor, trocam-se os elementos e
// chama a funcao novamente para a escolha feita
//------------------------------------------------------------
void DescerNaHeap(FILE *output, struct Heap *heap, int ind)
{
    int escolha;
    // checagem de erro
    if (fesq(ind) < heap->nElementos)
    {
        // escolha primeiramente o filho esquerdo
        escolha = fesq(ind);
        // se o direito existir e sua prioridade for maior que a do esquerdo, a nova escolha eh o direito
        if (fdir(ind) < heap->nElementos && heap->v[fesq(ind)].prioridade < heap->v[fdir(ind)].prioridade)
            escolha = fdir(ind);
        // se o pai tiver menor prioridade que filho de maior prioridade, faz-se a troca
        if (heap->v[ind].prioridade < heap->v[escolha].prioridade)
        {
            struct node aux_node = heap->v[escolha];
            heap->v[escolha] = heap->v[ind];
            heap->v[ind] = aux_node;
            // chama-se a funcao para a escolha feita, caso a troca tenha sido efetuada
            DescerNaHeap(output, heap, escolha);
        }
    }
}
//------------------------------------------------------------

//------------------------------------------------------------FUNCAO MAXIMUM
// retorna o indice da raiz (sempre 0)
//------------------------------------------------------------
int Maximum(FILE *output, struct Heap *heap)
{
    return 0;
}
//------------------------------------------------------------

//------------------------------------------------------------FUNCAO HEAPVAZIO
// checa se o numero de elementos da agenda eh 0, ou seja, agenda vazia
//------------------------------------------------------------
bool HeapVazio(FILE *output, struct Heap *heap)
{
    return (heap->nElementos == 0);
}
//------------------------------------------------------------

//------------------------------------------------------------FUNCAO HEAPCHEIO
// checa se o numero de elementos eh igual ao numero maximo permitido
//------------------------------------------------------------
bool HeapCheio(FILE *output, struct Heap *heap)
{
    return (heap->MAX == heap->nElementos);
}
//------------------------------------------------------------