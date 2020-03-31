/***********************************/
/* Aluno: JOÃO LUÍS ROCHA SARMENTO */
/* CES-10: Introdução à Computação */
/* Prof. VITOR CURTIS              */
/***********************************/

#include <stdio.h>

int fatorial (int n);

int main(){
    int n;
    scanf("%d", &n);
    printf("%d\n", fatorial(n));
    return 0;
}

int fatorial(int n){
    if(n == 1) return 1;
    int previous = fatorial(n-1);
    int ans = 0;
    for(int i = 0; i < n; i++)
        ans += previous;
    return ans;
}