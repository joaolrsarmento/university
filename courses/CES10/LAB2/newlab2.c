#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **createType(int s);

int main(){
    char *number = (char *)malloc(9 * sizeof(char));
    int s, typeIterator;
    int formatNumbers[10][5] = {  // contains every number's types
        {1, 4, 0, 4, 1}, // number 0
        {0, 2, 0, 2, 0}, // number 1
        {1, 2, 1, 3, 1}, // number 2
        {1, 2, 1, 2, 1}, // number 3
        {0, 4, 1, 2, 0}, // number 4
        {1, 3, 1, 2, 1}, // number 5
        {1, 3, 1, 4, 1}, // number 6
        {1, 2, 0, 2, 0}, // number 7
        {1, 4, 1, 4, 1}, // number 8
        {1, 4, 1, 2, 1}  // number 9
    };
    while (scanf("%d %s", &s, number) && s){
        char **type = createType(s);
        for (int i = 0; i < 2 * s + 3; i++){
            if (i == 0) typeIterator = 0;
            else if (i > 0 && i < s + 1) typeIterator = 1;
            else if (i == s + 1) typeIterator = 2; 
            else if (i > s + 1 && i < 2 * s + 2) typeIterator = 3;
            else typeIterator = 4;
            for (int j = 0; j < (int)strlen(number); j++){
                printf("%s%c", type[formatNumbers[(int)number[j] - '0'][typeIterator]], (j == (int)strlen(number) - 1 ? '\n' : ' '));
            }
        }
        for (int i = 0; i < 5; i++) free(type[i]);
        free(type);
    }
    free(number);
    return 0;
}

char **createType(int s){ /// creates five types of possible rows
    char **type = (char **)malloc(5 * sizeof(char *));
    for (int i = 0; i < 5; i++){
        type[i] = (char *)malloc((s + 3) * sizeof(char));
        type[i][s + 2] = '\0';
    }
    for (int i = 0; i < s + 2; i++){ // something like "     "
        type[0][i] = ' ';           
    }
    for (int i = 0; i < s + 2; i++){ // something like " --- "
        if (i == 0 || i == s + 1) type[1][i] = ' ';   
        else type[1][i] = '-';
    }
    for (int i = 0; i < s + 2; i++){ // something like "    |"
        if (i == s + 1) type[2][i] = '|';
        else type[2][i] = ' ';
    }
    for (int i = 0; i < s + 2; i++){ // something like "|    "
        if (i == 0) type[3][i] = '|';
        else type[3][i] = ' ';
    }
    for (int i = 0; i < s + 2; i++){ // something like "|   |"
        if (i == 0 || i == s + 1) type[4][i] = '|';
        else type[4][i] = ' ';
    }
    return type;
}