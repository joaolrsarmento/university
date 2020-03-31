/* Joao Luis */
/* Turma 3 */
/* CES-11: Algoritmos e Estruturas de Dados */
/* Exercício 4: Banco */

/* Programa compilado com gcc version 8.3.0 (Ubuntu 8.3.0-6ubuntu1~18.04.1) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//struct de cada cliente
struct correntistas
{
    char nome[21];
    float saldo;
};
//lista circular que contém os dados dos clientes
struct lista
{
    struct correntistas *correntista;
    int inicio, fim;
    int MAX;
};

struct lista Inicializar(int, FILE *);
void Finalizar(struct lista *);
void Inserir(struct lista *, char *, FILE *);
void AtualizarSaldo(struct lista *, float, char *, FILE *);
void ConsultarSaldo(struct lista *, char *, FILE *);
void Remover(struct lista *, char *, FILE *);
int BuscarPosicao(struct lista *, char *, FILE *);
bool ListaVazia(struct lista *);
int resto(int, int);
void RelatorioFinal(struct lista *, FILE *);

int main()
{
    FILE *input = fopen("entrada4.txt", "r");
    FILE *output = fopen("joaoluis4.txt", "w");
    char text[52];
    int MAX;
    //Pega as primeiras linhas
    for (int i = 0; i < 6; i++)
    {
        fgets(text, 52, input);
    }
    fscanf(input, "%d", &MAX);
    for (int i = 0; i < 2; i++)
        fgets(text, 51, input);
    fprintf(output, "INSTITUTO TECNOLOGICO DE AERONAUTICA\n"
                    "JOAO LUIS ROCHA SARMENTO\n"
                    "T3 - ARMANDO GOUVEIA\n\n"
                    "RESULTADOS DAS CONSULTAS\n\n");
    //Inicializa a lista
    struct lista lista_correntistas = Inicializar(MAX, output);
    while (strcmp(text, "FIM"))
    {
        fscanf(input, "%s ", text);
        if (!strcmp(text, "ABRE_CONTA"))
        {
            char nome[21];
            fgets(nome, 21, input);
            Inserir(&lista_correntistas, nome, output);
        }
        else if (!strcmp(text, "DEPOSITO"))
        {
            float valor;
            char nome[21];
            fscanf(input, "%f ", &valor);
            fgets(nome, 21, input);
            AtualizarSaldo(&lista_correntistas, valor, nome, output);
        }
        else if (!strcmp(text, "SAQUE"))
        {
            float valor;
            char nome[21];
            fscanf(input, "%f ", &valor);
            fgets(nome, 21, input);
            AtualizarSaldo(&lista_correntistas, -valor, nome, output);
        }
        else if (!strcmp(text, "EXTRATO"))
        {
            char nome[21];
            fgets(nome, 21, input);
            ConsultarSaldo(&lista_correntistas, nome, output);
        }
        else if (!strcmp(text, "FECHA_CONTA"))
        {
            char nome[21];
            fgets(nome, 21, input);
            Remover(&lista_correntistas, nome, output);
        }
    }
    fprintf(output, "\nRELATORIO FINAL\n\n"
                    "Tamanho maximo da lista:  %4d\n"
                    "Total de correntistas:    %4d\n"
                    "Posicoes ocupadas: inicio:%4d\n"
                    "                      fim:%4d\n\n"
                    "CORRENTISTAS ATUAIS\n\n",
            lista_correntistas.MAX, lista_correntistas.fim - lista_correntistas.inicio + 1, resto(lista_correntistas.inicio, lista_correntistas.MAX), resto(lista_correntistas.fim, lista_correntistas.MAX));
    //Da o relatorio final
    RelatorioFinal(&lista_correntistas, output);
    //Finaliza a lista (dá free)
    Finalizar(&lista_correntistas);
    return 0;
}

//--------------------------------------------------
//    INICIALIZAR
// Funcao que inicializa uma lista circular,
// com o numero maximo de pessoas
//--------------------------------------------------

struct lista Inicializar(int MAX, FILE *output)
{
    struct lista lista_correntista;
    //aloca-se os correntistas com tamanho maximi possivel
    lista_correntista.correntista = (struct correntistas *)malloc(MAX * sizeof(struct correntistas));
    // utiliza-se a convencao inicio 0 e fim MAX para identificar uma lista vazia
    lista_correntista.inicio = 0;
    lista_correntista.fim = MAX;
    lista_correntista.MAX = MAX;
    return lista_correntista;
}

//--------------------------------------------------
//    INSERIR
// Funcao que insere um elemento novo na lista circular
// Para isso, analisa-se primeiro a ordem do elemento a ser
// inserido com o meio da lista, para executar o shift para
// o lado mais curto
//--------------------------------------------------

void Inserir(struct lista *lista_correntistas, char *nome, FILE *output)
{
    int MAX = lista_correntistas->MAX;
    //Checa-se se a lista ta vazia
    if (ListaVazia(lista_correntistas))
    {
        //Se estiver vazia, inicializa o primeiro elemento da lista
        lista_correntistas->correntista[0].saldo = 0;
        strcpy(lista_correntistas->correntista[0].nome, nome);
        lista_correntistas->inicio = 0;
        lista_correntistas->fim = 0;
        return;
    }
    //encontra-se o tamanho da lista, para evitar estouro de memória ou acesso inválido
    int tamanho = lista_correntistas->fim - lista_correntistas->inicio + 1;
    if (tamanho == MAX)
    {
        fprintf(output, "ERRO: Lista lotada. Impossível abrir conta\n");
        return;
    }
    //Para evitar problemas com a metade, utiliza-se esse caso separado
    //em que o tamanho eh 1.
    if (tamanho == 1)
    {
        //checa-se onde o elemento novo vai se posicionar
        if (strcmp(nome, lista_correntistas->correntista[resto(lista_correntistas->inicio, MAX)].nome) >= 0)
        {
            if (!strcmp(nome, lista_correntistas->correntista[resto(lista_correntistas->inicio, MAX)].nome))
            {
                fprintf(output, "ERRO: Já existe um cliente com nome %s", nome);
                return;
            }
            strcpy(lista_correntistas->correntista[resto(lista_correntistas->fim + 1, MAX)].nome, nome);
            lista_correntistas->correntista[resto(lista_correntistas->fim + 1, MAX)].saldo = 0;
            // shift para direita
            lista_correntistas->fim++;
            return;
        }
        strcpy(lista_correntistas->correntista[resto(lista_correntistas->inicio - 1, MAX)].nome, nome);
        lista_correntistas->correntista[resto(lista_correntistas->inicio - 1, MAX)].saldo = 0;
        // shift para esquerda
        lista_correntistas->inicio--;
        return;
    }
    int i;
    // encontra-se a metade da lista circular
    int metade = (lista_correntistas->inicio + lista_correntistas->fim) / 2;
    // compara, primeiramente, o elemento a ser inserido com a metade da lista
    // com o intuito de shiftar pro lado mais curto
    if (strcmp(nome, lista_correntistas->correntista[resto(metade, MAX)].nome) >= 0)
    {
        // checa-se primeiro se nao existe o cliente com o nome
        if (!strcmp(nome, lista_correntistas->correntista[resto(metade, MAX)].nome))
        {
            fprintf(output, "ERRO: Já existe um cliente com nome %s", nome);
            return;
        }
        // shift para direita
        for (int i = lista_correntistas->fim + 1; i > metade; i--)
        {
            strcpy(lista_correntistas->correntista[resto(i, MAX)].nome, lista_correntistas->correntista[resto(i - 1, MAX)].nome);
            lista_correntistas->correntista[resto(i, MAX)].saldo = lista_correntistas->correntista[resto(i - 1, MAX)].saldo;
        }
        strcpy(lista_correntistas->correntista[resto(metade, MAX)].nome, nome);
        lista_correntistas->correntista[resto(metade, MAX)].saldo = 0;
        // shift para direita
        lista_correntistas->fim++;
        i = metade;
        while (i + 1<=lista_correntistas->fim && strcmp(lista_correntistas->correntista[resto(i, MAX)].nome, lista_correntistas->correntista[resto(i + 1, MAX)].nome) >= 0)
        {
            // checa-se se tem um cliente com esse nome
            if (!strcmp(lista_correntistas->correntista[resto(i, MAX)].nome, lista_correntistas->correntista[resto(i + 1, MAX)].nome))
            {
                fprintf(output, "ERRO: Já existe um cliente com nome %s", nome);
                return;
            }
            //troca os elementos com o da direita
            char aux_string[21];
            strcpy(aux_string, lista_correntistas->correntista[resto(i, MAX)].nome);
            strcpy(lista_correntistas->correntista[resto(i, MAX)].nome, lista_correntistas->correntista[resto(i + 1, MAX)].nome);
            strcpy(lista_correntistas->correntista[resto(i + 1, MAX)].nome, aux_string);
            lista_correntistas->correntista[resto(i, MAX)].saldo = lista_correntistas->correntista[resto(i + 1, MAX)].saldo;
            lista_correntistas->correntista[resto(i + 1, MAX)].saldo = 0;
            i++;
        }
        // a variavel i representa a posicao desejada
    }
    else
    {
        // novamente testa-se se existe elemento com esse nome
        if (!strcmp(nome, lista_correntistas->correntista[resto(metade, MAX)].nome))
        {
            fprintf(output, "ERRO: Já existe um cliente com nome %s", nome);
            return;
        }
        // copia os elementos para esquerda
        for (int i = lista_correntistas->inicio - 1; i < metade; i++)
        {
            strcpy(lista_correntistas->correntista[resto(i, MAX)].nome, lista_correntistas->correntista[resto(i + 1, MAX)].nome);
            lista_correntistas->correntista[resto(i, MAX)].saldo = lista_correntistas->correntista[resto(i + 1, MAX)].saldo;
        }
        strcpy(lista_correntistas->correntista[resto(metade, MAX)].nome, nome);
        lista_correntistas->correntista[resto(metade, MAX)].saldo = 0;
        lista_correntistas->inicio--;
        i = metade;
        while (i - 1 >= lista_correntistas->inicio && strcmp(lista_correntistas->correntista[resto(i, MAX)].nome, lista_correntistas->correntista[resto(i - 1, MAX)].nome) <= 0)
        {
            // checa se existe elemento com esse nome
            if (!strcmp(lista_correntistas->correntista[resto(i, MAX)].nome, lista_correntistas->correntista[resto(i - 1, MAX)].nome))
            {
                fprintf(output, "ERRO: Já existe um cliente com nome %s", nome);
                return;
            }
            // troca os elementos ate encontrar a posicao correta
            char aux_string[21];
            strcpy(aux_string, lista_correntistas->correntista[resto(i, MAX)].nome);
            strcpy(lista_correntistas->correntista[resto(i, MAX)].nome, lista_correntistas->correntista[resto(i - 1, MAX)].nome);
            strcpy(lista_correntistas->correntista[resto(i - 1, MAX)].nome, aux_string);
            lista_correntistas->correntista[resto(i, MAX)].saldo = lista_correntistas->correntista[resto(i - 1, MAX)].saldo;
            lista_correntistas->correntista[resto(i - 1, MAX)].saldo = 0;
            i--;
        }
        // esse if serve para garantir que o shift nao foi feito para o local errado,
        // o que poderia acontecer pois no meu algoritmo pode-se ter alguns problemas caso
        // a variavel i seja exatamente a metade
        // assim, testa-se se o shift foi feito para o lado esquerdo quando deveria ser pro lado direito,
        // caso tenha sido feito erroneamente, faz-se 2 shifts para direita, afim de se ajustar
        if (resto(i - lista_correntistas->inicio, lista_correntistas->MAX) == resto(lista_correntistas->fim - i, lista_correntistas->MAX))
        {
            for (int j = lista_correntistas->fim + 1; j > lista_correntistas->inicio; j--)
            {
                char aux_string[21];
                strcpy(aux_string, lista_correntistas->correntista[resto(j, MAX)].nome);
                strcpy(lista_correntistas->correntista[resto(j, MAX)].nome, lista_correntistas->correntista[resto(j - 1, MAX)].nome);
                strcpy(lista_correntistas->correntista[resto(j - 1, MAX)].nome, aux_string);
                lista_correntistas->correntista[resto(j, MAX)].saldo = lista_correntistas->correntista[resto(j - 1, MAX)].saldo;
                lista_correntistas->correntista[resto(j - 1, MAX)].saldo = 0;
            }
            lista_correntistas->inicio++;
            lista_correntistas->fim++;
        }
    }
}

//--------------------------------------------------
//    ATUALIZARSALDO
// Funcao que atualiza o saldo de um cliente, usando
// a funcao buscarposicao. Aqui vai ser usado para o saque
// e para o deposito
//--------------------------------------------------

void AtualizarSaldo(struct lista *lista_correntistas, float valor, char *nome, FILE *output)
{
    if (!ListaVazia(lista_correntistas))
    {
        int MAX = lista_correntistas->MAX;
        int posicao = BuscarPosicao(lista_correntistas, nome, output);
        if (posicao != -1)
        {
            // atualiza o saldo do cliente
            lista_correntistas->correntista[resto(posicao, MAX)].saldo += valor;
            return;
        }
        fprintf(output, "ERRO: Nao encontrado cliente com nome %s", nome);
        return;
    }
    fprintf(output, "ERRO: Lista vazia\n");
}

//--------------------------------------------------
//    CONSULTARSALDO
// Funcao que busca o saldo de um elemento da lista,
// utilizando a funcao buscarposicao
//--------------------------------------------------

void ConsultarSaldo(struct lista *lista_correntistas, char *nome, FILE *output)
{
    if (!ListaVazia(lista_correntistas))
    {
        int MAX = lista_correntistas->MAX;
        int posicao = BuscarPosicao(lista_correntistas, nome, output);
        if (posicao != -1)
        {
            // imprime o saldo do cliente
            fprintf(output, "Saldo %8.2f  %s", lista_correntistas->correntista[resto(posicao, MAX)].saldo, nome);
            return;
        }
        fprintf(output, "ERRO: Nao encontrado cliente com nome %s", nome);
        return;
    }
    fprintf(output, "ERRO: Lista vazia\n");
}

//--------------------------------------------------
//    REMOVER
// Funcao que remove um dado elemento da lista circular,
// Para isso, tenta-se buscar o elemento, e, a partir dai,
// executa-se o shift para o lado mais curto
//--------------------------------------------------

void Remover(struct lista *lista_correntistas, char *nome, FILE *output)
{
    if (!ListaVazia(lista_correntistas))
    {
        int MAX = lista_correntistas->MAX;
        int posicao = BuscarPosicao(lista_correntistas, nome, output);
        if (posicao != -1)
        {
            // encontra-se o lado mais curto para executar o shift
            if (resto(posicao - resto(lista_correntistas->inicio, MAX), MAX) >= resto(resto(lista_correntistas->fim, MAX) - posicao, MAX))
            {
                for (int i = posicao; i < resto(lista_correntistas->fim, MAX); i++)
                {
                    strcpy(lista_correntistas->correntista[resto(i, MAX)].nome, lista_correntistas->correntista[resto(i + 1, MAX)].nome);
                    lista_correntistas->correntista[resto(i, MAX)].saldo = lista_correntistas->correntista[resto(i + 1, MAX)].saldo;
                }
                if (lista_correntistas->fim == lista_correntistas->inicio)
                {
                    lista_correntistas->fim = MAX;
                    lista_correntistas->inicio = 0;
                    return;
                }
                lista_correntistas->fim--;
                return;
            }
            else
            {
                for (int i = posicao; i > resto(lista_correntistas->inicio, MAX); i--)
                {
                    strcpy(lista_correntistas->correntista[resto(i, MAX)].nome, lista_correntistas->correntista[resto(i - 1, MAX)].nome);
                    lista_correntistas->correntista[resto(i, MAX)].saldo = lista_correntistas->correntista[resto(i - 1, MAX)].saldo;
                }
                lista_correntistas->inicio++;
                return;
            }
        }
        fprintf(output, "ERRO: Nao encontrado cliente com nome %s", nome);
    }
}

//--------------------------------------------------
//    FINALIZAR
// Funcao que da free nos elementos alocados dinamicamente
// ao inicializar a lista circular, para isso, basta
// executar o free no ponteiro correntista
//--------------------------------------------------

void Finalizar(struct lista *lista_correntistas)
{
    // libera memoria
    free(lista_correntistas->correntista);
}

//--------------------------------------------------
//    BUSCARPOSICAO
// Funcao que retorna a posicao de um cliente, ou -1
// caso o cliente nao pertença a fila. Para isso, checa-se
// inicialmente o meio da fila, pra poder shiftar para
// o lado mais curto, visando economizar tempo
//--------------------------------------------------

int BuscarPosicao(struct lista *lista_correntistas, char *nome, FILE *output)
{
    int MAX = lista_correntistas->MAX;
    if (ListaVazia(lista_correntistas))
        return -1;
    if (lista_correntistas->inicio == lista_correntistas->fim)
    {
        if (!strcmp(nome, lista_correntistas->correntista[resto(lista_correntistas->inicio, MAX)].nome))
            return resto(lista_correntistas->inicio, MAX);
        else
            return -1;
    }
    int metade = (lista_correntistas->inicio + lista_correntistas->fim) / 2;
    if (!strcmp(nome, lista_correntistas->correntista[resto(metade, MAX)].nome))
        return resto(metade, MAX);
    bool depois_da_metade = false;
    // checa se o elemento a ser buscado esta depois da metade
    if (strcmp(nome, lista_correntistas->correntista[resto(metade, MAX)].nome) > 0)
        depois_da_metade = true;
    if (depois_da_metade)
    {
        // se ele estiver depois da metade, basta comparar da mesma para o final
        for (int i = metade; i <= lista_correntistas->fim; i++)
            if (!strcmp(lista_correntistas->correntista[resto(i, MAX)].nome, nome))
            {
                return resto(i, MAX);
            }
    }
    else
    {
        // se estiver antes da metade, basta comparar da mesma para o inicio
        for (int i = lista_correntistas->inicio; i <= metade; i++)
            if (!strcmp(lista_correntistas->correntista[resto(i, MAX)].nome, nome))
            {
                return resto(i, MAX);
            }
    }
    return -1;
}

//--------------------------------------------------
//    LISTAVAZIA
// Funcao que checa se a lista ta vazia, analisando
// os valores dos indices iniciais e finais da lista
//--------------------------------------------------

bool ListaVazia(struct lista *lista_correntistas)
{
    // checa se a lista ta vazia
    if (lista_correntistas->inicio == 0 && lista_correntistas->fim == lista_correntistas->MAX)
        return true;
    return false;
}

//--------------------------------------------------
//    RESTO
// Funcao que fornece o resto da divisao de a por b,
// desconsiderando-se valores negativos
//--------------------------------------------------

int resto(int a, int b)
{
    int restoObtido = a % b;
    // checa se o resto obtido é menor que 0, a fim de evitar problemas de acesso de memoria
    if (restoObtido < 0)
        return restoObtido + b;
    return restoObtido;
}

//--------------------------------------------------
//    RELATORIOFINAL
// Funcao que fornece a situacao final da fila
//--------------------------------------------------

void RelatorioFinal(struct lista *lista_correntistas, FILE *output)
{
    // lista_correntistas->correntista[resto(lista_correntistas->fim, lista_correntistas->MAX)].nome[strlen(lista_correntistas->correntista[resto(lista_correntistas->fim, lista_correntistas->MAX)].nome) - 2] = '\0';
    for (int i = lista_correntistas->inicio; i <= lista_correntistas->fim; i++)
        fprintf(output, "%8.2f %d %s", lista_correntistas->correntista[resto(i, lista_correntistas->MAX)].saldo, resto(i,lista_correntistas->MAX), lista_correntistas->correntista[resto(i, lista_correntistas->MAX)].nome);
}

//--------------------------------------------------
