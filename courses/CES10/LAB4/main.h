struct Candidates{
    char name[81];
    int eliminated;
    int nVotes;
} *Candidate;

int checkTie(int nCandidates);
int getMinimum(int nCandidates);
int checkWinner(int nCandidates, int nBallots);
void eliminating(int nCandidates, int min, int nBallots, int **votes);
void printingTie(int nCandidates);
