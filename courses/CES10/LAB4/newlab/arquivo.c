/***********************************/
/* Aluno: JOÃO LUÍS ROCHA SARMENTO */
/* CES-10: Introdução à Computação */
/* Prof. VITOR CURTIS              */
/***********************************/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(){
    FILE *p = fopen("Lab6-1.md", "r");
    char c;
    while((c = fgetc(p)) != EOF){
        printf("%c", c);
    }
    return 0;
}