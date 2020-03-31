#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INFINITO 999999

struct Candidates{
    char name[81];
    bool eliminated;
    int nVotes;
    };

bool checkTie(int nCandidates, struct Candidates *Candidate); /// check if there's a tie
int getMinimum(int nCandidates, struct Candidates *Candidate); /// return the indice of the least voted candidate
int getWinner(int nCandidates, int nBallots, struct Candidates *Candidate); /// check if there's a winner
void eliminating(int nCandidates, int min, int nBallots, int **votes, struct Candidates *Candidate); /// eliminate the least voted candidates and count the votes again
void printingTie(int nCandidates, struct Candidates *Candidate); /// print the name of the tied candidates

int main(){
    int nCases, nCandidates, nBallots, i, j, winner;
    scanf("%d", &nCases);
    getchar();
    while(nCases--){
        struct Candidates *Candidate;
        int **votes = NULL;
        scanf("%d ", &nCandidates);
        Candidate = (struct Candidates *) malloc(nCandidates*sizeof(struct Candidates));
        for(i = 0; i < nCandidates; i++){
            fgets(Candidate[i].name, 81, stdin);
            Candidate[i].eliminated = false;
            Candidate[i].nVotes = 0;
        }
        for(i = 0; i < 1001; i++){
            votes = (int **) realloc(votes,(i+1)*sizeof(int *));
            votes[i] = (int *) malloc(nCandidates*sizeof(int));
            for(j = 0; j < nCandidates; j++){
                if(scanf("%d", &votes[i][j]) == EOF){
                    free(votes[i]);
                    nBallots = i;
                    i = 1001;
                    break;
                }
            }
            if(i != 1001)
                Candidate[votes[i][0]-1].nVotes++;
        }
        winner = -1;
        while(winner == -1){
            bool tie = checkTie(nCandidates, Candidate);
            int min = getMinimum(nCandidates, Candidate);
            if(tie == true){
                printingTie(nCandidates, Candidate);
                break;
            }
            else{
                eliminating(nCandidates, min, nBallots, votes, Candidate);
                winner = getWinner(nCandidates, nBallots, Candidate);
            }
        }
        if(winner != -1){
            printf("%s", Candidate[winner].name);
        }
        free(Candidate);
        for(i = 0; i < nBallots; i++)
            free(votes[i]);
        free(votes);
    }
    return 0;
}

int getWinner(int nCandidates, int nBallots, struct Candidates *Candidate){
    int i;
    for(i = 0; i < nCandidates; i++){
        if(!Candidate[i].eliminated && Candidate[i].nVotes > nBallots/2){
            return i;
        }
    }
    return -1;
}

int getMinimum(int nCandidates, struct Candidates *Candidate){
    int i, min = INFINITO;
    int indiceMin = -1;
    for(i = 0; i < nCandidates; i++){
        if(!Candidate[i].eliminated && min > Candidate[i].nVotes){
            min = Candidate[i].nVotes;
            indiceMin = i;
        }
    }
    return indiceMin;
}

bool checkTie(int nCandidates, struct Candidates *Candidate){
    int auxiliar, i;
    for(i = 0; i < nCandidates; i++){
        if(!Candidate[i].eliminated){
            auxiliar = i;
            break;
        }
    }
    for(i = auxiliar; i < nCandidates; i++){
        if(!Candidate[i].eliminated && Candidate[i].nVotes != Candidate[auxiliar].nVotes)
            return false;
    }
    return true;
}

void eliminating(int nCandidates, int min, int nBallots, int **votes, struct Candidates *Candidate){
    int i, j;
    for(i = 0; i < nCandidates; i++){
        if(Candidate[min].nVotes == Candidate[i].nVotes){
            Candidate[i].eliminated = true;
        }
    }
    for(i = 0; i < nCandidates; i++){
        Candidate[i].nVotes = 0;
    }
    for(i = 0; i < nBallots; i++){
        for(j = 0; j < nCandidates; j++){
            if(!Candidate[votes[i][j]-1].eliminated){
                Candidate[votes[i][j]-1].nVotes++;
                break;
            }
        }
    }
}

void printingTie(int nCandidates, struct Candidates *Candidate){
    int i;
    for(i = 0; i < nCandidates; i++){
        if(!Candidate[i].eliminated) 
            printf("%s", Candidate[i].name);
    }
}









