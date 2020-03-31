#include <stdio.h>

int main(){
    int n = 1;
    char temp[1];
    while(1){
        scanf("%d", &n);
        char temp = '\n';
        int count = 0;
        while(temp == '\n'){
            temp = getchar();
            count++;
        }
    }
    return 0;
}