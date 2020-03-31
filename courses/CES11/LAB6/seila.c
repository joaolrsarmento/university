#include <stdio.h>
#include <stdlib.h>

int main(){
    fila f;
    inicializar(&f);
    int n = 0, nprox = 1;
    int nivel = 0;
    noh *aux, *sec_aux;
    inserirnafila(&f, raiz);
    while(f.ini != NULL){
        aux = (f.ini)->noh;
        remove(&f);
        sec_aux = aux->fesq;
        while(sec_aux != NULL){
            inserirnafila(&f, sec_aux);
            n++;
            sec_aux = sec_aux->idir;
        }
        nprox--;
        if(!nprox){
            printf("nivel %d: %d nós", nivel++, n);
            nprox = n;
            n = 0;
        }
    }
    return 0;
}