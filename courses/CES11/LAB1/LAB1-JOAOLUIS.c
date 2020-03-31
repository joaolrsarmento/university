#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//-------------------------------------------DECLARACAO DA STRUCT NODE---------------------------------------------------

struct node
{
    char city[31];
    int flight;
    bool urgency;
    struct node *next;
};

//----------------------------------------------------------------------------------------------------------------------

//-------------------------------------------FUNCAO QUE CRIA NODES------------------------------------------------------

struct node *create_node(char city[], int flight, struct node *next)
{
    struct node *aux = (struct node *)malloc(sizeof(struct node));
    if (aux != NULL)
    {
        strcpy(aux->city, city);
        aux->flight = flight;
        aux->urgency = false;
        aux->next = next;
    }
    return aux;
}

//---------------------------------------------------------------------------------------------------------------------

//-------------------------------------------FUNCAO QUE COPIA DADOS DE UM NODE PARA OUTRO------------------------------

void swap(struct node *firstNode, struct node *secondNode)
{
    char aux_string[31];
    strcpy(aux_string, firstNode->city);
    strcpy(firstNode->city, secondNode->city);
    strcpy(secondNode->city, aux_string);
    firstNode->flight ^= secondNode->flight;
    secondNode->flight ^= firstNode->flight;
    firstNode->flight ^= secondNode->flight;
}

//-------------------------------------------------------------------------------------------------------------------

int main()
{
    FILE *input = fopen("C:\\Lab1\\entrada1.txt", "r");
    FILE *output = fopen("C:\\Lab1\\joaoluis1.txt", "w");
    char row[70], message[70];
    for (int i = 0; i < 7; i++)
        fgets(row, 70, input);      // PEGA AS PRIMEIRAS LINHAS DA ENTRADA
    fscanf(input, "%s", message);   // SCANEIA A PRIMEIRA MENSAGEM
    if (!strcmp(message, "INICIO")) // TESTA SE A MENSAGEM EH O INICIO
    {
        fgets(row, 70, input); // PULA A LINHA DO INICIO
        fprintf(output, "INSTITUTO TECNOLOGICO DE AERONAUTICA\n"
                        "CES11\n"
                        "HELLO WORLD\n"
                        "=========================================\n"
                        "FLIGHT  FROM\n\n");
        char city[70];
        int flight;
        struct node *first = NULL; // PONTEIRO QUE VAI APONTAR PARA O PRIMEIRO DA LISTA
        struct node *last = NULL;  // PONTEIRO QUE VAI APONTAR PARA O ÚLTIMO DA LISTA
        while (fscanf(input, "%s", message) && strcmp(message, "FIM"))
        {
            fscanf(input, "%04d %[^\n]", &flight, city);
            if (!strcmp(message, "pede_pouso")) // CRIA NOVO NODE NO FIM DA LISTA
            {
                if (first == NULL)
                {
                    first = create_node(city, flight, NULL);
                    last = first;
                }
                else
                {
                    last->next = create_node(city, flight, NULL);
                    last = last->next;
                }
            }
            else if (!strcmp(message, "pista_liberada"))
            {
                if (first == NULL) // TESTA SE TEM ALGUEM DISPONIVEL PARA POUSAR
                    fprintf(output, "0000\tNenhum aviao pousando\n");
                else
                {
                    fprintf(output, "%04d\t%-30s\n", first->flight, first->city); // PRINTA NO ARQUIVO O PRIMEIRO DA LISTA
                    struct node *auxiliar_node = first->next;
                    free(first); // LIBERA MEMÓRIA
                    first = auxiliar_node;
                }
            }
            else if (!strcmp(message, "URGENCIA"))
            {
                struct node *auxiliar_node = first;
                while (auxiliar_node->flight != flight)
                    auxiliar_node = auxiliar_node->next; // FAZ AUXILIAR_NODE APONTAR PARA O AVIAO QUE LANCOU O CHAMADO DE URGENCIA
                struct node *second_auxiliar_node = first;
                while(second_auxiliar_node->urgency) second_auxiliar_node = second_auxiliar_node->next; // FAZ SECOND APONTAR PARA O PRIMEIRO AVIAO NAO URGENTE
                second_auxiliar_node->urgency = true; // MARCA COMO URGENTE
                while (second_auxiliar_node->flight != auxiliar_node->flight) 
                {
                    /*
                        AQUI EFETUA-SE TROCAS ATE SE ATINGIR A ORDEM DESEJADA, POR EXEMPLO: SE TIVERMOS A SEGUINTE ORDEM "A B C D E F",
                        EM QUE 'B' EH O PRIMEIRO AVIAO NAO URGENTE (SECOND_AUXILIAR_NODE) E 'E' EH O AVIAO QUE FOI MARCADO COMO URGENTE
                        (AUXILIAR_NODE):
                        1º VEZ NO WHILE: "A E C D B F"
                        2º VEZ NO WHILE: "A E B D C F"
                        3º VEZ NO WHILE: "A E B C D F"
                        QUE EH A ORDEM DESEJADA
                    */
                    swap(second_auxiliar_node, auxiliar_node);
                    second_auxiliar_node = second_auxiliar_node->next;
                }
            }
        }
        fprintf(output, "\nSituacao da fila\n\n");
        if (first == NULL)
            fprintf(output, "Nenhum aviao na espera\n");
        else
        {
            while (first != NULL)
            {
                fprintf(output, "%04d\t%s\n", first->flight, first->city);
                first = first->next;
            }
        }
    }
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------------