#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv){
    FILE *entrada1 = fopen(argv[1], "r");
    FILE *entrada2 = fopen(argv[2], "r");
    char text1[200];
    char text2[200];
    while((entrada1 != NULL || entrada2 != NULL) || !strcmp(text1, "FIM") || !strcmp(text2, "FIM")){
        if(fgets(text1, 200, entrada1) == NULL ||
        fgets(text2, 200, entrada2) == NULL) break;
        // printf("estou em tex1: %s", text1);
        // system("pause");
        getchar();
        if(strcmp(text1, text2)) printf("%s------diferente de-------\n%s", text1, text2);
        else printf("---strings iguais---\n");
    }
    return 0;
}
