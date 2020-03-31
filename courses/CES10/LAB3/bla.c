#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *p = fopen("Lab6-1.md", "r");
    fclose(p);
    return 0;
}
