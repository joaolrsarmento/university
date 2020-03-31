/***********************************/
/* Aluno: JOÃO LUÍS ROCHA SARMENTO */
/* CES-10: Introdução à Computação */
/* Prof. VITOR CURTIS              */
/***********************************/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    FILE *p = fopen("Lab6-1.md", "r");
    int linhas = 1, caracteres = 0, caracteresBrancos = 0, palavras = 0, comecoPalavra = 0;
    char texto[200];
    while (fgets(texto, 200, p) != NULL)
    {
        if(strlen(texto) == 2)
            palavras--;
        caracteres+=strlen(texto);
        for (int i = 0; i < strlen(texto); i++)
        {
            if ((texto[i] != ' ') && (texto[i] != '\n') && (!comecoPalavra))
            {
                comecoPalavra = 1;
            }
            if (((texto[i] == ' ') || (texto[i] == '\n')) && (comecoPalavra))
            {
                comecoPalavra = 0;
                palavras++;
            }
            if (texto[i] == '\n')
            {
                linhas++;
            }
            if (isspace(texto[i]))
            {
                caracteresBrancos++;
            }
        }
    }

    printf("Quantidade de linhas: %d\n"
           "Quantidade de palavras: %d\n"
           "Quantidade de caracteres não whitespace: %d\n",
           linhas, palavras, caracteres - caracteresBrancos);
    return 0;
}