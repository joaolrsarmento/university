#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(){
    char string[51];
    int n;
    FILE *output = fopen("entrada3.txt", "w");
    scanf("%d", &n);
    fprintf(output, "%d\n", n);
    time_t t;
    srand((unsigned) time(&t));
    while(n--){
        int tam = 8 + rand() % 41;
        string[0] = 'A' + rand() % 26;
        for(int i = 1; i < tam - 1; i++){
            int whichLetter = rand() % 27;
            if(string[i-1] != ' ' && whichLetter == 26) string[i] = ' ';
            else if(whichLetter != 26){
                if(string[i-1] == ' '){
                    string[i] = 'A' + whichLetter;
                }
                else string[i] = 'a' + whichLetter;
            }
            else string[i] = 'a' + rand() % 26;
        }
        if(n != 0) string[tam-1] = '\n';
        string[tam] = '\0';
        fprintf(output, "%s", string);
    }
    fclose(output);
    return 0;
}
