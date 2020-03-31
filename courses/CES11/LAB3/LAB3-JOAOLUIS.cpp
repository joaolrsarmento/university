/* Joao Luis */
/* Turma 3 */
/* CES-11: Algoritmos e Estruturas de Dados */
/* Exercício 3: Ordenacao */

/* Programa compilado com gcc namesersion 8.3.0 (Ubuntu 8.3.0-6ubuntu1~18.04.1) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int compara(const char *, const char *);
void BubbleSort(char **, int);
void MergeSort(char **, int, int);
void Merge(char **, int, int);
void QuickSort(char **, int, int);
int Partition(char **, int, int);
int contador;

int main()
{
    FILE *input = fopen("C:\\Lab3\\entrada3.txt", "r"); //input
    FILE *output_bubble = fopen("C:\\Lab3\\joaoluis3bubble.txt", "w"); //output do algoritmo BubbleSort
    FILE *output_merge = fopen("C:\\Lab3\\joaoluis3merge.txt", "w"); //output do algoritmo MergeSort
    FILE *output_quick = fopen("C:\\Lab3\\joaoluis3quick.txt", "w"); //output do algoritmo QuickSort
    char **names = NULL; //vetor de strings que vai ser ordenado
    char **recover_names = NULL; //backup das strings lidas
    int nPeople; //numero de strings

    fscanf(input, "%d", &nPeople);
    names = (char **)malloc(nPeople * sizeof(char *));
    recover_names = (char **)malloc(nPeople * sizeof(char *));

    fgetc(input); //pegando \n do arquivo
    for (int i = 0; i < nPeople; i++)
    {
        names[i] = (char *)malloc(51 * sizeof(char));
        recover_names[i] = (char *)malloc(51 * sizeof(char));
        fgets(recover_names[i], 50, input);
    }
    recover_names[nPeople - 1][strlen(recover_names[nPeople - 1])] = '\n';
    for (int i = 0; i < nPeople; i++)
        strcpy(names[i], recover_names[i]); //names recebe recover_names
    contador = 0; //conta o numero de comparacoes
    clock_t start = clock(); //marca clock inicial
    BubbleSort(names, nPeople);
    clock_t end = clock(); //marca clock final
    double time = ((double)(end - start)) / CLOCKS_PER_SEC; //calcula tempo
    // printando no arquivo
    fprintf(output_bubble, "Algoritmo: Bubble-Sort\n\n"
                    "Tamanho da entrada: %d\n"
                    "Comparações feitas: %d\n"
                    "Tempo de execução : %.4lf segundos\n\n"
                    "--------------------------------------------------\n",
            nPeople, contador, time);
    for (int i = 0; i < nPeople; i++)
        fprintf(output_bubble, "%s", names[i]); //printa os nomes ordenados no arquivo
    
    for (int i = 0; i < nPeople; i++)
        strcpy(names[i], recover_names[i]); //names recebe recover_names
    contador = 0;
    start = clock();
    MergeSort(names, 0, nPeople - 1);
    end = clock();
    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    //printando no arquivo
    fprintf(output_merge, "Algoritmo: Merge-Sort\n\n"
                    "Tamanho da entrada: %d\n"
                    "Comparações feitas: %d\n"
                    "Tempo de execução : %.4lf segundos\n\n"
                    "--------------------------------------------------\n",
            nPeople, contador, time);
    for (int i = 0; i < nPeople; i++){
        fprintf(output_merge, "%s", names[i]);
        strcpy(names[i], recover_names[i]); //names recebe recover_names
    }

    contador = 0;
    start = clock();
    QuickSort(names, 0, nPeople - 1);
    end = clock();
    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    //printando no arquivo
    fprintf(output_quick, "Algoritmo: Quick-Sort\n\n"
                    "Tamanho da entrada: %d\n"
                    "Comparações feitas: %d\n"
                    "Tempo de execução : %.4lf segundos\n\n"
                    "--------------------------------------------------\n",
            nPeople, contador, time);
    for (int i = 0; i < nPeople; i++)
        fprintf(output_quick, "%s", names[i]);
    
    //libera memoria usada
    for(int i = 0; i < nPeople; i++){
        free(recover_names[i]);
        free(names[i]);
    }
    free(recover_names);
    free(names);

    fclose(input);
    fclose(output_bubble);
    fclose(output_merge);
    fclose(output_quick);
    return 0;
}

int compara(const char *a, const char *b)
{
    contador++;
    return strcmp(a, b);
}

//--------------------------------------------------
//    BUBBLESORT
//--------------------------------------------------
/*
Dado um vetor de strings e seu tamanho, ordena o vetor alfabeticamente
*/
void BubbleSort(char **names, int nPeople)
{
    for (int i = 0; i < nPeople; i++)
        for (int j = 0; j < nPeople - 1; j++)
        {
            if (compara(names[j], names[j + 1]) > 0)
            {
                //permuta
                char aux_string[51];
                strcpy(aux_string, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], aux_string);
            }
        }
}

//--------------------------------------------------
//    MERGE
//--------------------------------------------------
/*
Dado um vetor V de strings e dadas duas posicoes ini e fim.
A metade da esquerda desse trecho ja� esta� ordenada e
a metade da direita  desse trecho ja� esta� ordenada.
Fazer intercalacao (merge) e obter V ordenado.
*/

void Merge(char **names, int begin, int end)
{
    char **T; // temporario
    T = (char **)malloc((end - begin + 1) * sizeof(char *));
    for (int i = 0; i < end - begin + 1; i++)
        T[i] = (char *)malloc(51 * sizeof(char));
    int med,
         i, // percorre T
         j, // percorre lado esquerdo de names
         k;// percorre lado direito  de names
         
    med = (begin + end) / 2; //mesmo arredondamento feito ao chamar MergeSort
    j = begin;
    k = med + 1;
    i = begin;
    //percorrer selecionando os menores
    while (j <= med && k <= end)
    {
        if (compara(names[j], names[k]) <= 0)
        {
            strcpy(T[i - begin], names[j]);
            j++;
        }
        else
        {
            strcpy(T[i - begin], names[k]);
            k++;
        }
        i++;
    }
    //se sobrou algo `a esquerda, copiar para T
    while (j <= med)
    {
        strcpy(T[i - begin], names[j]);
        i++;
        j++;
    }
    //se sobrou algo `a direita, copiar para T
    while (k <= end)
    {
        strcpy(T[i - begin], names[k]);
        i++;
        k++;
    }
    // names recebe T
    for (i = begin; i <= end; i++)
        strcpy(names[i], T[i - begin]);
    //libera memória utilizada
    for(int i = begin; i <= end; i++)
        free(T[i-begin]);
    free(T);
}

//--------------------------------------------------
//    MERGE SORT
//--------------------------------------------------

void MergeSort(char **names, int begin, int end)
{
    int med;
    if (begin < end)
    {
        med = (begin + end) / 2; // dividir ao meio
        MergeSort(names, begin, med); // ordenar lado esquerdo
        MergeSort(names, med + 1, end); // ordenar lado direito
        Merge(names, begin, end); // mesclar as duas metades
    } 
}

//--------------------------------------------------
//    PARTITION
//--------------------------------------------------
/*
Dado um vetor V de strings com elementos em qualquer ordem,
escolher um elemento para ser pivo^
e ent�o dividir os elementos de V em duas partes:
  `a esquerda: os que vem antes na ordem alfabetica que o pivo
  `a direita:  os que vem depois ou na mesma posicao que o pivo
*/

int Partition(char **names, int begin, int end)
{
    char pivot[51], aux[51];
    int left, right;
    strcpy(pivot, names[begin]); // neste exemplo, o pivo � o primeiro da esquerda
    left = begin + 1;
    right = end;
    do
    {
        // percorrer da esquerda para a direita. encontrar alguem >= pivo
        while (left < end && compara(names[left], pivot) < 0)
            left++;
        // percorrer da direita para a esquerda. encontrar alguem < pivo
        while (begin < right && compara(pivot, names[right]) <= 0)
            right--;
        // se achou um `a esquerda e outro `a direita
        if (left < right)
        {
            // permutar
            strcpy(aux, names[left]);
            strcpy(names[left], names[right]);
            strcpy(names[right], aux);
        }
        // caso contrario, terminara� a repeticao
    } while (left < right);

    // trocar o pivo com o elemento que "divide" os subvetores
    strcpy(names[begin], names[right]);
    strcpy(names[right], pivot);
    // retornar a posi��o da "divisa"
    return right;
}

//--------------------------------------------------
//    QUICK SORT
//--------------------------------------------------

void QuickSort(char **names, int begin, int end)
{
    int p; //posi��o do pivo
    if (begin < end)
    {
        p = Partition(names, begin, end);
        QuickSort(names, begin, p - 1);
        QuickSort(names, p + 1, end);
    }
}