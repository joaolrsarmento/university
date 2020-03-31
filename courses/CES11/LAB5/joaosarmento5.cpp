/* Joao Luis */
/* Turma 3 */
/* CES-11: Algoritmos e Estruturas de Dados */
/* Exercício 5: Livro */

/* Programa compilado com gcc version 8.3.0 (Ubuntu 8.3.0-6ubuntu1~18.04.1) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// struct que representa os nos da arvore que sera criada
struct node
{
    char objeto[21];
    struct node *pai,
        *fesq,
        *idir;
};
//--------------------------------------------------
struct node *Busca(char[], struct node *);
void Inserir(struct node *, char[], char[], char[], FILE *);
void Remover(struct node *, char[], FILE *);
void Transferir(struct node *, char[], char[], char[], FILE *);
void PrintarArvore(struct node *, FILE *);
struct node *InicializarArvore(char[]);
int IndiceHorizontal(struct node *);
void PrintarIndice(struct node *, FILE *);
//--------------------------------------------------
//-------------------------------------------------- FUNCAO MAIN
int main()
{
    FILE *input = fopen("C:\\Lab5\\entrada5.txt", "r");
    FILE *output = fopen("C:\\Lab5\\joaoluis5.txt", "w");
    struct node *raiz = NULL;
    int nListas = 0;
    fprintf(output, "INSTITULO TECNOLÓGICO DE AERONAUTICA\n"
                    "JOAO SARMENTO\n"
                    "TURMA 3\n");
    for (int i = 0; i < 50; i++)
        fprintf(output, "-");
    fprintf(output, "\n");
    char text[71], titulo[10], titulo_objeto[22], posicao[22], objeto[22], segundo_objeto[22], message[22];
    // pega as primeiras linhas
    for (int i = 0; i < 4; i++)
        fgets(text, 70, input);
    // scaneia o arquivo ate encontrar o titulo
    while (fscanf(input, "%s", titulo) && strcmp(titulo, "TITULO"))
    {
        // Checagens de erro
        if (!strcmp(titulo, "LISTA"))
        {
            fprintf(output, "LISTA %d\n\n", ++nListas);
                PrintarArvore(raiz, output);
                for (int i = 0; i < 50; i++)
                    fprintf(output, "-");
                fprintf(output, "\n");
        }
        else if (!strcmp(titulo, "INSERIR"))
        {
            fscanf(input, "%s %s %s", objeto, posicao, segundo_objeto);
            fgetc(input);
            fprintf(output, "ERRO: Nao encontrado %s\n", segundo_objeto);
            for (int i = 0; i < 50; i++)
                fprintf(output, "-");
            fprintf(output, "\n");
        }
        else if (!strcmp(titulo, "REMOVER"))
        {
            fscanf(input, "%s", objeto);
            fgetc(input);
            fprintf(output, "ERRO: Nao encontrado %s\n", objeto);
            for (int i = 0; i < 50; i++)
                fprintf(output, "-");
            fprintf(output, "\n");
        }
        else if (!strcmp(titulo, "TRANSFERIR"))
        {
            fscanf(input, "%s %s %s", objeto, posicao, segundo_objeto);
            fgetc(input);
            fprintf(output, "ERRO: Nao encontrado %s\n", objeto);
            for (int i = 0; i < 50; i++)
                fprintf(output, "-");
            fprintf(output, "\n");
            fprintf(output, "ERRO: Nao encontrado %s\n", segundo_objeto);
            for (int i = 0; i < 50; i++)
                fprintf(output, "-");
            fprintf(output, "\n");
        }
    }
    fscanf(input, " %s", titulo_objeto);
    fgetc(input);
    // inicializa a arvore com o titulo scaneado
    raiz = InicializarArvore(titulo_objeto);
    while (fscanf(input, "%s ", message) && strcmp(message, "FIM"))
    {
        if (!strcmp(message, "LISTA"))
        {
            // checagem de erro
            if (raiz == NULL)
                fprintf(output, "ERRO: Arvore vazia\n");
            else
            {
                fprintf(output, "LISTA %d\n\n", ++nListas);
                PrintarArvore(raiz, output);
                for (int i = 0; i < 50; i++)
                    fprintf(output, "-");
                fprintf(output, "\n");
            }
        }
        else if (!strcmp(message, "INSERIR"))
        {
            // insere um novo item na arvore
            fscanf(input, "%s %s %s", objeto, posicao, segundo_objeto);
            fgetc(input);
            Inserir(raiz, objeto, posicao, segundo_objeto, output);
        }
        else if (!strcmp(message, "REMOVER"))
        {
            // remove um item da lista
            fscanf(input, "%s", objeto);
            fgetc(input);
            struct node *aux_node = Busca(objeto, raiz);
            if (aux_node != NULL)
            {
                // faz o irmao esquerdo (se existir) do cara que vai ser removido ter como irmao direito o irmao direito do cara que vai ser removido
                if (aux_node != aux_node->pai->fesq)
                {
                    struct node *sec_aux_node = aux_node->pai->fesq;
                    while (sec_aux_node->idir != aux_node)
                        sec_aux_node = sec_aux_node->idir;
                    sec_aux_node->idir = sec_aux_node->idir->idir;
                }
                else
                { // caso o irmao esquerdo nao exista, o filho esquerdo do pai do cara que sera removido deve ser o irmao direito do mesmo cara
                    aux_node->pai->fesq = aux_node->idir;
                }
                // desliga o item da arvore
                aux_node->idir = NULL;
            }
            // remove o item
            Remover(aux_node, objeto, output);
        }
        else if (!strcmp(message, "TRANSFERIR"))
        {
            // transfere o item
            fscanf(input, "%s %s %s", objeto, posicao, segundo_objeto);
            fgetc(input);
            Transferir(raiz, objeto, posicao, segundo_objeto, output);
        }
        else if (!strcmp(message, "TITULO"))
        {
            // cria um novo titulo para a arvore
            // scaneia o titulo
            fscanf(input, "%s", titulo_objeto);
            fgetc(input);
            // inicializa uma nova raiz com o novo titulo
            struct node *nova_raiz = InicializarArvore(titulo_objeto);
            // faz a antiga raiz ser filha da nova raiz
            nova_raiz->fesq = raiz;
            raiz->pai = nova_raiz;
            // a raiz agora aponta para a nova raiz
            raiz = nova_raiz;
        }
    }
    // limpa memoria final
    Remover(raiz, raiz->objeto, output);
    fclose(input);
    fclose(output);
    return 0;
}
//--------------------------------------------------

//--------------------------------------------------
//    INICIALIZARARVORE
// Funcao que inicializa uma arvore,
// com o titulo solicitado, retornando um ponteiro para a raiz dessa arvore criada
//--------------------------------------------------

struct node *InicializarArvore(char titulo_objeto[])
{
    struct node *raiz = (struct node *)malloc(sizeof(struct node));
    strcpy(raiz->objeto, titulo_objeto);
    raiz->fesq = NULL;
    raiz->idir = NULL;
    raiz->pai = NULL;
    return raiz;
}

//--------------------------------------------------

//--------------------------------------------------
//    BUSCA
// Funcao que busca um no numa arvore,
// retornando um ponteiro para esse no, caso esteja na arvore.
// E um ponteiro para NULL caso nao esteja.
//--------------------------------------------------

struct node *Busca(char objeto[], struct node *node)
{
    struct node *p, *resposta;
    // checa se a raiz da arvore passada ja nao eh o elemento a ser buscada, ou se a raiz nao eh nula
    if (node == NULL || !strcmp(objeto, node->objeto))
        return node;
    else
    {
        // busca recursivamente o no
        resposta = NULL;
        p = node->fesq;
        while (p != NULL && resposta == NULL)
        {
            // checa-se todos os filhos da arvore
            resposta = Busca(objeto, p);
            p = p->idir;
            // faz a busca em largura (p->idir)
        }
        // retorna o ponteiro para o no encontrado
        // caso nao esteja na arvore, resposta sera NULL
        return resposta;
    }
}

//--------------------------------------------------

//--------------------------------------------------
//    INSERIR
// Funcao que insere um novo item numa arvore em uma posicao dada.
// Para isso, caso a posicao desejada seja sub, faz-se o filho esquerdo do segundo objeto ser o novo item,
// depois, faz-se o irmao direito do novo item ser o irmao direito do antigo filho esquerdo do segundo objeto (caso exista).
// Caso a posicao desejada seja seguinte_a, cria-se um no com as informacoes desejada,
// faz ele ter o mesmo pai do segundo objeto,
// faz ele ter como irmao direito o irmao direito do segundo objeto,
// faz o irmao direito do segundo objeto ser o novo item
//--------------------------------------------------

void Inserir(struct node *raiz, char objeto[], char posicao[], char segundo_objeto[], FILE *output)
{
    struct node *aux_node = Busca(segundo_objeto, raiz);
    // checagem de erro
    if (aux_node == NULL)
    {
        fprintf(output, "ERRO: nao encontrado item %s\n", segundo_objeto);
        for (int i = 0; i < 50; i++)
            fprintf(output, "-");
        fprintf(output, "\n");
        return;
    }
    struct node *sec_aux_node;
    if (!strcmp(posicao, "SUB"))
    {
        // checa-se primeiro se nao existe filho esquerdo
        if (aux_node->fesq == NULL)
        {
            // cria-se o novo no com as informacoes e hierarquia desejada
            aux_node->fesq = (struct node *)malloc(sizeof(struct node));
            aux_node->fesq->fesq = NULL;
            aux_node->fesq->idir = NULL;
            strcpy(aux_node->fesq->objeto, objeto);
            aux_node->fesq->pai = aux_node;
        }
        else
        {
            // Caso ja exista algum filho esquerdo do segundo objeto,
            sec_aux_node = (struct node *)malloc(sizeof(struct node)); // cria-se um novo no com as informacoes desejadas,
            strcpy(sec_aux_node->objeto, objeto);
            sec_aux_node->idir = aux_node->fesq; // faz o irmao direito do novo item no apontar para o filho esquerdo do segundo objeto,
            sec_aux_node->pai = aux_node;        // faz o pai do novo item ser o segundo objeto,
            sec_aux_node->fesq = NULL;
            aux_node->fesq = sec_aux_node; // faz o filho esquerdo do segundo objeto ser o novo item
        }
    }
    else if (!strcmp(posicao, "SEGUINTE_A"))
    {
        // checagem de erro, evita que o novo item seja colocado seguinte a raiz (nao configura arvore)
        if (aux_node == raiz)
        {
            fprintf(output, "ERRO: Nao eh possivel adicionar %s %s %s\n", objeto, posicao, segundo_objeto);
            return;
        }
        sec_aux_node = (struct node *)malloc(sizeof(struct node)); // cria-se novo no com as informacoes desejadas
        sec_aux_node->pai = aux_node->pai;                         // faz o novo no ter mesmo pai do segundo objeto
        sec_aux_node->fesq = NULL;
        sec_aux_node->idir = aux_node->idir; // faz o novo no ter como irmao direito o irmao direito do segundo objeto
        strcpy(sec_aux_node->objeto, objeto);
        aux_node->idir = sec_aux_node; // faz o irmao direito do segundo objeto ser o novo no
    }
}
//--------------------------------------------------

//--------------------------------------------------
//    REMOVER
// Funcao que remove um dado item.
// Para isso, utiliza-se de recursividade.
// Primeiro, busca o no a ser removido.
// Depois, checa se existe filhos dele a serem removidos.
// Depois, checa se existe irmao direito dele a ser removido.
// Por fim, tira ele da arvore e libera a memoria.
//--------------------------------------------------

void Remover(struct node *raiz, char objeto[], FILE *output)
{
    // Note que, nesse algoritmo, optou-se por ligar os nos proximos ao no retirado na propria funcao main, como indicado por comentarios nas linhas 76 - 86
    struct node *aux_node = Busca(objeto, raiz);
    // checagem de erro
    if (aux_node == NULL)
    {
        fprintf(output, "ERRO: nao encontrado item %s\n", objeto);
        for (int i = 0; i < 50; i++)
            fprintf(output, "-");
        fprintf(output, "\n");
        return;
    }
    // checa se tem filho esquerdo a ser liberado, e, se tiver, libera-os recursivamente
    if (aux_node->fesq != NULL)
    {
        Remover(raiz, aux_node->fesq->objeto, output);
        aux_node->fesq = NULL;
    }
    // checa s e tem irmao direto a ser liberado, e, se tiver, libera-os recursivamente
    if (aux_node->idir != NULL)
    {
        Remover(raiz, aux_node->idir->objeto, output);
        aux_node->idir = NULL;
    }
    // retira o no da arvore
    aux_node->pai = NULL;
    // libera a memoria
    free(aux_node);
}
//--------------------------------------------------

//--------------------------------------------------
//    TRANSFERIR
// Funcao que transfere um no da arvore para uma outra posicao dada da arvore.
// No caso da posicao sub a outro no, executa-se o seguinte algoritmo:
// faz o irmao direito do cara a ser transferido ser o filho esquerdo do nó que receberá,
// faz o pai do cara a ser transferido ser o nó que receberá,
// faz o filho esquerdo do cara que receberá ser o cara transferido.
// Ja no caso da posicao seguinte_a outro nó, executa-se o seguinte algoritmo:
// faz o irmao direito do cara a ser transferido ser o irmao direito do cara que receberá,
// faz o pai do cara a ser transferido ser o pai do cara que receberá,
// faz o irmao direito do cara que receberá ser o cara transferido
//--------------------------------------------------

void Transferir(struct node *raiz, char objeto[], char posicao[], char segundo_objeto[], FILE *output)
{
    struct node *aux_node = Busca(objeto, raiz);
    struct node *sec_aux_node = Busca(segundo_objeto, raiz);
    // checagem de erro
    if(sec_aux_node == raiz && !strcmp(posicao, "SEGUINTE_A")){
        fprintf(output, "ERRO: Nao eh possivel transferir %s %s raiz(%s)\n", objeto, posicao, segundo_objeto);
        for (int i = 0; i < 50; i++)
                fprintf(output, "-");
            fprintf(output, "\n");
        return;
    }
    if (aux_node == NULL || sec_aux_node == NULL)
    {
        if (aux_node == NULL)
        {
            fprintf(output, "ERRO: nao encontrado item %s\n", objeto);
            for (int i = 0; i < 50; i++)
                fprintf(output, "-");
            fprintf(output, "\n");
        }
        // checagem de erro
        if (sec_aux_node == NULL)
        {
            fprintf(output, "ERRO: nao encontrado item %s\n", segundo_objeto);
            for (int i = 0; i < 50; i++)
                fprintf(output, "-");
            fprintf(output, "\n");
        }
        return;
    }
    // third_aux_node apontará para o irmao esquerdo do cara(caso exista) que sera transferido.
    struct node *third_aux_node;
    // checa se aux_node nao eh a raiz (checagem de erro)
    if (aux_node->pai == NULL)
    {
        fprintf(output, "ERRO: Nao eh possivel transferir a raiz(%s) %s %s\n", objeto, posicao, segundo_objeto);
        return;
    }
    // checa se aux_node eh filho unico, caso seja, basta fazer o filho esquerdo do pai de aux_node ser NULL
    if (aux_node == aux_node->pai->fesq)
    {
        aux_node->pai->fesq = NULL;
    }
    // caso aux_node nao seja filho unico, third_aux_node apontará para seu irmao esquerdo
    else
    {
        third_aux_node = aux_node->pai->fesq;
        while (third_aux_node != NULL && third_aux_node->idir != aux_node)
        {
            third_aux_node = third_aux_node->idir;
        }
        // faz-se o irmao esquerdo de aux_node ter como irmao direito o irmao direito de aux_node
        third_aux_node->idir = third_aux_node->idir->idir;
    }
    if (!strcmp(posicao, "SUB"))
    {
        // Caso a posicao desejada seja sub
        aux_node->idir = sec_aux_node->fesq; // faz-se o irmao direito de aux_node apontar para o filho esquerdo de sec_aux_node
        aux_node->pai = sec_aux_node;        // faz aux_node ser filho de sec_aux_node
        sec_aux_node->fesq = aux_node;       // faz sec_aux_node ser pai de aux_node
    }
    else if (!strcmp(posicao, "SEGUINTE_A"))
    {
        // Caso a posicao desejada seja seguinte_a
        aux_node->idir = sec_aux_node->idir; // faz o irmao direito de aux_node ser o irmao direito de sec_aux_node
        aux_node->pai = sec_aux_node->pai;   // faz o pai de aux_node ser o pai de sec_aux_node
        sec_aux_node->idir = aux_node;       // faz o irmao direito de sec_aux_node ser o aux_node
    }
}
//--------------------------------------------------

//--------------------------------------------------
//    PRINTARARVORE
// Funcao que printa a arvore de forma indentada
//--------------------------------------------------

void PrintarArvore(struct node *raiz, FILE *output)
{
    // checagem de erro
    if (raiz == NULL)
    {
        return;
    }
    // printa os indices da raiz recursivamente
    PrintarIndice(raiz, output);
    // faz a indentação
    fprintf(output, "      %s\n", raiz->objeto);
    // printa os filhos da raiz
    PrintarArvore(raiz->fesq, output);
    // printa os irmao da raiz
    PrintarArvore(raiz->idir, output);
}
//--------------------------------------------------

//--------------------------------------------------
//    INDICEHORIZONTAL
// Funcao que calcula o indice horizontal de um dado no
//--------------------------------------------------

int IndiceHorizontal(struct node *node)
{
    if (node->pai == NULL)
    {
        if (node == NULL)
            return 0;
        else
            return 1;
    }
    if (node == NULL)
        return 0;
    int comprimento = 0;
    struct node *aux_node = node->pai->fesq;
    while (aux_node != node && aux_node != NULL)
    {
        aux_node = aux_node->idir;
        comprimento++;
    }
    return comprimento;
}
//--------------------------------------------------

//--------------------------------------------------
//    PRINTARINDICE
// Funcao que printa os indices de um dado no
//--------------------------------------------------
void PrintarIndice(struct node *raiz, FILE *output)
{
    // checagem de erro
    if (raiz->pai == NULL)
        return;
    // printa os indices do pai, primeiramente
    PrintarIndice(raiz->pai, output);
    fprintf(output, "%d.", IndiceHorizontal(raiz) + 1);
}
//--------------------------------------------------