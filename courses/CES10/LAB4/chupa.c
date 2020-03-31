#include <stdio.h>

min

for(int i = 0; i < numerodecand; i++){
    if(numerovotos[i] == min && !cand[i].eliminado)
        cand[i].eliminado = true;
}

for(int i = 0; i < numerodelinhas; i++){
    for(int j = 0; j < numerocandidatos; j++){
        if(!cand[votos[i][j]-1].eliminado){
            cand[votos[i][j]-1].numerovotos++;
            break;
        }
    }
}