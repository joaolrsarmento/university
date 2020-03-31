#include <stdio.h>

int main(){
    int num1, num2, i, cycleLength, max_cycleLength;
    while(scanf("%d %d", &num1, &num2) == 2){
        max_cycleLength = 0;
        for(i = num1; i <= num2; i++){
            cycleLength = 1;
            int aux = i;
            while(aux != 1){
                cycleLength++;  //increments one everytime it tries other number
                if(aux%2 == 0)
                    aux /= 2;
                else
                    aux = 3*aux + 1;
            }
            if(max_cycleLength < cycleLength)
                max_cycleLength = cycleLength;  // compare the size of the cycle, getting the maximum
        }  
        printf("%d %d %d\n", num1, num2, max_cycleLength);
    }
}