/* Joao Luis */
/* Turma 3 */
/* CES-11: Algoritmos e Estruturas de Dados */
/* Exercício 2: Produto Matrizes */

/* Programa compilado com gcc version 8.3.0 (Ubuntu 8.3.0-6ubuntu1~18.04.1) */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int Best_Path[20][20]; // Matriz para armazenamento da melhor ordem de multiplicacao
int Count_Recursive_Calls = 0; // Contagem de chamadas recursivas

/*------------------
--------------Funcao Minimum_Multi que retorna o numero minimo de multiplicoes escalares para dados inicio (prev) e fim (next)
------Para isso, a funcao chama recursivamente cada possivel particao no intervalo [prev,next)
------Alem disso, armazena na matriz global a melhor particao 
------------------*/

int Minimum_Multi(int *Matrix[2], int nMatrix, int prev, int next){
    Count_Recursive_Calls++;
    if(prev == next) 
        return 0;
    int auxiliar = INT_MAX; // Inicializa a variavel como o maior inteiro possivel
    for (int i = prev; i < next; i++){
        int previous_aux = Minimum_Multi(Matrix, nMatrix, prev, i) + Minimum_Multi(Matrix, nMatrix, i + 1, next) + Matrix[0][prev] * Matrix[1][i] * Matrix[1][next];
        if (auxiliar > previous_aux){
            auxiliar = previous_aux; // Guarda o minimo atual
            Best_Path[prev][next] = i; // Armazena a melhor particao
        }
    }
    return auxiliar;
}

/*----------------------------------------------------------------------------------------------------------*/

/*------------------
--------------Funcao que printa a melhor ordem de multiplicacao das matrizes
------Para isso, chama recursivamente a funcao duas vezes, representando a particao
------------------*/

void printBest_Path(int prev, int next, FILE *output){
    if (next == prev)
        return;
    if (next == prev + 1){
        fprintf(output, "%5d x %2d\n", prev + 1, next + 1);
        return;
    }
    printBest_Path(prev, Best_Path[prev][next], output);
    printBest_Path(Best_Path[prev][next] + 1, next, output);
    if(next == Best_Path[prev][next] + 1){
        fprintf(output,"%2d-%2d x %2d\n", prev + 1,Best_Path[prev][next] + 1, next + 1);
        return;
    }
    if(prev == Best_Path[prev][next]){
        fprintf(output, "%5d x %2d-%2d\n", prev + 1,Best_Path[prev][next] + 2, next + 1);
        return;
    }
    fprintf(output, "%2d-%2d x %2d-%2d\n", prev + 1, Best_Path[prev][next] + 1, Best_Path[prev][next] + 2, next + 1);
}

/*----------------------------------------------------------------------------------------------------------*/

int main()
{
    FILE *input = fopen("C:\\Lab2\\entrada2.txt", "r");
    FILE *output = fopen("C:\\Lab2\\seunome2.txt", "w");
    char row[71];
    for (int i = 0; i < 5; i++)
        fgets(row, 70, input); // Pula as primeiras linhas
    int nMatrix;
    fscanf(input, "%d", &nMatrix);
    for (int i = 0; i < 3; i++)
        fgets(row, 70, input);
    int *Matrix[2]; // Armazena as dimensoes das matrizes
    Matrix[0] = (int *)malloc(nMatrix * sizeof(int));
    Matrix[1] = (int *)malloc(nMatrix * sizeof(int));
    for (int i = 0; i < nMatrix; i++){
        fscanf(input, "%d %d", &Matrix[0][i], &Matrix[1][i]);
        fgets(row, 70, input);
    }
    int answer = Minimum_Multi(Matrix, nMatrix, 0, nMatrix - 1);
    fprintf(output, "INSTITUTO TECNOLOGICO DE AERONAUTICA\n"
                    "ALUNO: JOAO LUIS\n"
                    "PROFESSOR: ARMANDO\n"
                    "\nTotal de multiplicacoes escalares = %d\n\n"
                    "Chamadas aa funcao: %d\n\n"
                    "Melhor ordem para realizar o produto:\n",
            answer, Count_Recursive_Calls);
    printBest_Path(0, nMatrix - 1, output);
    free(Matrix[0]);
    free(Matrix[1]);
    fclose(input);
    fclose(output);
    return 0;
}