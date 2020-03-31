#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int k=0;
int vet[7];

struct noh
{
    char nome[22];
    struct noh *pai;
    struct noh *irmaodir;
    struct noh *filhoesq;
};

typedef struct noh noh;

struct noh *Busca(char objeto[22], noh *x)
{
    noh *p, *resposta;
    if (!strcmp(objeto, x->nome))
        return x;
    else
    {
        resposta = NULL;
        p = x->filhoesq;
        while (p != NULL && resposta == NULL)
        {
            resposta = Busca(objeto, p);
            p = p->irmaodir;
        }
        return resposta;
    }
}


void Remover(noh *x)
{
    if(x->filhoesq!=NULL)
    {
        Remover(x->filhoesq);
    }
    if(x->irmaodir!=NULL)
    {
        Remover(x->irmaodir);
    }
    free(x);
}


void Inserir(char nome1[22], char nome2[22], char comando[22], noh *raiz, FILE* saida)
{
    noh *p, *q;
    q= (noh *)malloc(sizeof(noh));
    q->irmaodir=NULL;
    q->filhoesq=NULL;
    strcpy(q->nome, nome1);
    if (strcmp(comando, "SUB") == 0)
    {
        p = Busca(nome2, raiz);
        if(p==NULL)
        {
            fprintf(saida, "ERRO: nao encontrado item %s\n", nome2);
            fprintf(saida, "--------------------------------------------------\n");
            return;
        }
        q->pai=p;
        q->irmaodir=p->filhoesq;
        p->filhoesq=q;

    }
    else if(strcmp(comando, "SEGUINTE_A") == 0)
    {
        p = Busca(nome2, raiz);
        if(p==NULL)
        {
            printf("ERRO: nao encontrado item %s\n", nome2);
            return;
        }
        q->irmaodir=p->irmaodir;
        p->irmaodir=q;
        q->pai=p->pai;
    }
}


void PreOrdem(noh *x, FILE *saida)
{
    int contador=1;
    if(x==NULL)
    return;
    while( x!=NULL)
    {
        if(k==0)
            k++;
        else{
            vet[k]=contador;
            k++;
            for(int i=1; i<k; i++)
                fprintf(saida, "%d.", vet[i]);
        }
        fprintf(saida,"       %s\n", x->nome);
        PreOrdem(x->filhoesq,saida);
        x=x->irmaodir;
        k--;
        contador++;
    }
}

void Transferir(char nome1[22], char nome2[22], char comando[22], noh *raiz, FILE* saida)
{
    noh *b,*a,*c;
    b=Busca(nome1,raiz);
    if(b==NULL)
        {
            fprintf(saida, "ERRO: nao encontrado item %s", nome1);
            fprintf(saida, "--------------------------------------------------");
            return;
        }
    a=b;
    c=a;
    b=b->pai;
    b=b->filhoesq;
    if(b!=a){
        while(strcmp(b->irmaodir->nome,nome1)!=0)
        {
            b=b->irmaodir;
        }
            b->irmaodir=b->irmaodir->irmaodir;
    }
    else
    {
        a->pai->filhoesq=a->irmaodir;
    }
    noh *p, *q;
    p=a;
    q=Busca(nome2, raiz);
    if(q==NULL)
        {
            fprintf(saida, "ERRO: nao encontrado item %s\n", nome2);
            fprintf(saida, "--------------------------------------------------\n");
            return;
        }
    if(strcmp(comando,"SUB")==0)
    {
        p->irmaodir = q->filhoesq;
        p->pai = q;
        q->filhoesq = p;
    }
    else
    {
        q->irmaodir=p->irmaodir;
        p->irmaodir=q;
        q->pai=p->pai;
    }
}

int main()
{

    FILE *entrada = fopen("entrada5.txt", "r");
    FILE *saida = fopen("Lucas5.txt", "w");

    //Pulo as linhas para que começe a ler a partir de onde o programa começa
    char c;
    char comando1[22], comando2[22];
    int contador = 0;
    int n, listas;
    listas=1;
    char nome1[22], nome2[22];
    noh *raiz;
    raiz = (noh *)malloc(sizeof(noh));
    raiz->pai = NULL;
    raiz->filhoesq=NULL;
    raiz->irmaodir=NULL;

    

    //-------------------------------------------------------
    //    Pulando as linhas inutilizadas e salvando o MAX
    //-------------------------------------------------------

    while (contador <= 3 && (c = fgetc(entrada)) != EOF)
    {
        if (c == '\n')
        {
            contador++;
        }
    }
    contador=0;

    fscanf(entrada, "%s ",comando1);
    while(strcmp(comando1, "TITULO")!=0){
    fscanf(entrada, "%s ",nome1);
    strcpy(raiz->nome, nome1);
    }
    

    //-------------------------------------------------------
    //    INICIALIZANDO A LISTA
    //-------------------------------------------------------

    fprintf(saida, "JoseLloyds Bank\nBla BLa\nSoftware\n");
    fprintf(saida, "--------------------------------------------------\n");

    //-------------------------------------------------------
    //  LENDO OS COMANDOS ATÉ O FIM E EXECUÇÃO DO SOFTWARE
    //-------------------------------------------------------

    while (strcmp(comando1, "FIM") != 0)
    {
        fscanf(entrada, "%s ", comando1);
        printf("%s", comando1);
        if(strcmp(comando1,"TITULO")==0 ||strcmp(comando1,"REMOVER")==0 )
        {
        fscanf(entrada, "%s ", nome1);
        }
        else if(strcmp(comando1,"LISTA")==0)
        {
        }
        else{
        fscanf(entrada, "%s ", nome1);
        fscanf(entrada, "%s ", comando2);
        fscanf(entrada, "%s ", nome2);
        printf("%s %s %s %s\n", comando1, nome1, comando2, nome2);
        }
        //-------------------------------------------------------
        //    INSERIR
        //-------------------------------------------------------
        if (strcmp(comando1, "INSERIR") == 0)
        {
            Inserir(nome1,nome2,comando2,raiz,saida);
        }

        //-------------------------------------------------------
        //    REMOVER
        //-------------------------------------------------------

        else if (strcmp(comando1, "REMOVER") == 0)
        {
            noh *p,*q;
            p=Busca(nome1,raiz);
             if(p==NULL)
        {
            fprintf(saida, "ERRO: nao encontrado item %s\n", nome1);
            fprintf(saida, "--------------------------------------------------\n");
        }
        else{
            q=p;
            p=p->pai;
            p=p->filhoesq;
            while(strcmp(p->irmaodir->nome,nome1)!=0)
            {
                p=p->irmaodir;
            }
            p->irmaodir=p->irmaodir->irmaodir;
            q->irmaodir=NULL;
            q->pai==NULL;
            Remover(q);
        }
        }

        //-------------------------------------------------------
        //    TRANSFERIR
        //-------------------------------------------------------

        else if (strcmp(comando1, "TRANSFERIR") == 0)
        {


            Transferir(nome1,nome2,comando2,raiz,saida);
        }

        //-------------------------------------------------------
        //    TITULO
        //-------------------------------------------------------

        else if (strcmp(comando1, "TITULO") == 0)
        {
            noh *nova_raiz;
            nova_raiz=(noh *)malloc(sizeof(noh));
            nova_raiz->filhoesq==NULL;
            nova_raiz->irmaodir==NULL;
            strcpy(nova_raiz->nome, nome1);
            nova_raiz->filhoesq=raiz;
            raiz=nova_raiz;
        }

        //-------------------------------------------------------
        //    LISTA
        //-------------------------------------------------------

        else if (strcmp(comando1, "LISTA") == 0)
        {
            fprintf(saida, "LISTA %d\n\n", listas);
            listas++;
            PreOrdem(raiz, saida);
            fprintf(saida, "--------------------------------------------------\n");
        }
    }
    
    fclose(entrada);
    fclose(saida);

}