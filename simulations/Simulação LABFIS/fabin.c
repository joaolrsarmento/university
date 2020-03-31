#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

#define NUMBER 1
#define OPU 2
#define OPAR 3
#define CPAR 4
#define INVAL 5
#define OPB 6

// PARENTETICA.H
typedef union
{
    double value;
    char op, carac;
} atribatom ;

typedef struct atom
{
    int tipo;
    atribatom atrib;
} atom;

typedef char expression[100];
atom parenthetical[100];
expression expr;
int natoms = 0, i;
char c;

void make_atoms (void);

void print_atoms (atom[],int );

char get_non_blank (void);

char get_next (void);

void init_expr (void);

// POLONESA.H
typedef struct node
{
    atom* element;
    struct node* prox;
} node_t;

typedef node_t *stack_t;

void adt_initStack (stack_t *);

void adt_pushStack (stack_t *, atom *);

void adt_popStack (stack_t *);

atom* adt_topStack (stack_t);

bool adt_isEmptyStack (stack_t);

void adt_emptyStack (stack_t *);

// ARVORE.H
typedef struct cell
{
    atom *elem;
    struct cell *lchild, *rchild;
} cell_t;

typedef cell_t *bintree_node;

typedef cell_t *bintree_t;

bintree_t criaArvore(stack_t*);

void ordem_central(bintree_t);

double evaluate(bintree_t);

// MAIN
int main ()
{
    char resp_user;
    int aux_2 = 0;
    do
    {
        printf("Expression:  ");
        fflush(stdin);
        setbuf(stdin,NULL);
        fgets(expr,100,stdin);
        make_atoms( );
        atom* operador = 0;
        int d, k = 0;
        stack_t P;
        stack_t OP;
        adt_initStack(&P);
        adt_initStack(&OP);
        while (k<natoms)
        {
            d = parenthetical[k].tipo;
            if(d == 1)// COLOCA NUMERO NA POLONESA
            {
                adt_pushStack(&P, &parenthetical[k]);
            }
            else if(d == 2)// COLOCA OPERADOR NA PILHA OP
            {
                adt_pushStack(&OP, &parenthetical[k]);
            }
            else if(d == 6)
            {
                adt_pushStack(&OP, &parenthetical[k]);
            }
            else if(d == 4) // DESEMPILHA O OPERADOR E COLOCA NA POLONESA
            {
                operador = adt_topStack(OP);
                adt_popStack(&OP);
                adt_pushStack(&P, operador);
            }
            k++;
        }
        // ARVORE
        bintree_t A;
        A = criaArvore(&P);
        double resultado = evaluate(A);
        printf("O resultado e: %lf\n",resultado);
        printf("Deseja continuar?(s/n) \n");
        scanf("%c", &resp_user);
        if( resp_user == 'n')
        {
            aux_2 = 1;
        }
    }
    while(aux_2 == 0);

    return 0;
}
// PARENTETICA.C

char get_non_blank()
{
    while (isspace(expr[i]) || (iscntrl (expr[i]) && expr[i] != '\0'))
        i++;
    return expr [i];
}
char get_next()
{
    i++;
    return expr[i];
}
void init_expr()
{
    i = 0;
}

void make_atoms()
{
    double num = 0;
    init_expr();
    c = get_non_blank();
    while ( c != '\0')
    {
        if(isdigit(c))
        {
            int aux = 1;
            num = c - '0';
            c = get_next();
            while(isdigit(c))
            {
                num = 10*num + c - '0';
                c = get_next();
            }
            if(c == '.')
            {
                c = get_next();
                while(isdigit(c))
                {
                    num = 10*num + c - '0';
                    c = get_next();
                    aux = aux*10;
                }
            }
            num = num/aux;
            parenthetical[natoms].tipo = 1;
            parenthetical[natoms].atrib.value = num;
            natoms++;
        }
        if(c == '*' || c == '+' || c == '-' || c == '/' || c == '@' || c == 'L')
        {
            parenthetical[natoms].tipo = 2;
            parenthetical[natoms].atrib.op = c;
            natoms++;

        }
        if( c == 'R' || c == 'S' || c == 'C' || c == '~')
        {
            parenthetical[natoms].tipo = 6;
            parenthetical[natoms].atrib.op = c;
            natoms++;
        }
        if(c == '(')
        {
            parenthetical[natoms].tipo = 3;
            parenthetical[natoms].atrib.carac = ' ';
            natoms++;
        }
        if(c == ')')
        {
            parenthetical[natoms].tipo = 4;
            parenthetical[natoms].atrib.carac = ' ';
            natoms++;
        }
        if(c == ' ')
        {

        }
        else if (c != ' ' && c != ')' && c != '(' && c != '*' && c != '+' && c != '-' && c != '/' && c != '@' && c != 'R' && c != 'L' && c != 'S' && c != 'C' && c != '~' )
        {
            parenthetical[natoms].tipo = 5;
            parenthetical[natoms].atrib.carac = c;
            natoms++;
        }
        c = get_next();
    }
    natoms--;
}
void print_atoms(atom parenthetical[ ], int natoms)
{
    printf("Type   |   Attribute   \n");
    for(int k = 0; k<natoms; k++)
    {
        if(parenthetical[k].tipo == 1)
        {
            printf("%d      |   %lf          \n", parenthetical[k].tipo, parenthetical[k].atrib.value);
        }
        else if( parenthetical[k].tipo == 3 || parenthetical[k].tipo == 4 || parenthetical[k].tipo == 5)
        {
            printf("%d      |   %c           \n", parenthetical[k].tipo, parenthetical[k].atrib.carac);
        }
        else if( parenthetical[k].tipo == 2 || parenthetical[k].tipo == 6 )
        {
            printf("%d      |   %c           \n", parenthetical[k].tipo, parenthetical[k].atrib.op);
        }
    }

}
// POLONESA.C

void adt_initStack (stack_t * P)
{
    *P = NULL;
}

void adt_pushStack (stack_t * p, atom * atoms)
{
    stack_t temp;
    temp = *p;
    *p = (stack_t)malloc(sizeof(node_t));
    (*p)->element = atoms;
    (*p)->prox = temp;
}

void adt_popStack (stack_t * p)
{
    stack_t temp;
    if (*p != NULL)
    {
        temp = *p;
        *p = (*p)->prox;
        free(temp);
    }
}

atom* adt_topStack (stack_t p)
{
    if(p!=NULL)
    {
        return p->element;
    }
    else
    {
        return 0;
    }
}

bool adt_isEmptyStack ( stack_t p )
{
    if( p == NULL )
        return true;
    else
        return false;
}

void adt_emptyStack ( stack_t * p)
{
    stack_t temp;
    temp = *p;
    while (temp != NULL)
    {
        (temp) = (temp)->prox;
        free(temp);
    }
    *p = NULL;
}

// ARVORE.C

bintree_t criaArvore(stack_t* p)
{
    bintree_node T;
    T = (bintree_node) malloc(sizeof(cell_t));
    T->elem = (atom*) malloc(sizeof(atom));
    atom* q = adt_topStack(*p);
    T->elem->tipo = q->tipo;
    switch(T->elem->tipo)
    {
    case 1:
        T->elem->atrib.value = adt_topStack(*p)->atrib.value;
        break;
    case 2:
        T->elem->atrib.op = adt_topStack(*p)->atrib.op;
        break;
    case 6:
        T->elem->atrib.op = adt_topStack(*p)->atrib.op;
        break;
    default:
        break;
    }
    if(p != NULL)
        adt_popStack(p);
    if(T->elem->tipo == 1)
    {
        T->rchild = NULL;
        T->lchild = NULL;
    }
    if(T->elem->tipo == 2)
    {
        T->rchild = criaArvore(p);
        T->lchild = criaArvore(p);
    }

    if(T->elem->tipo == 6)
    {
        T->rchild = criaArvore(p);
        T->lchild = NULL;
    }

    return T;
}

void ordem_central(bintree_t T)
{
    if(T->lchild == NULL && T->rchild == NULL)
        printf("%f ", T->elem->atrib.value);
    else
    {
        ordem_central(T->lchild);
        printf("%c ", T->elem->atrib.op);
        ordem_central(T->rchild);
    }
}

double evaluate(bintree_t T)
{
    if(T->elem->tipo == 1)
    {
        return T->elem->atrib.value;
    }
    else if(T->elem->tipo == 2)
    {
        switch(T->elem->atrib.op)
        {
        case '+':
            return evaluate(T->lchild) + evaluate(T->rchild);
            break;
        case '*':
            return evaluate(T->lchild) * evaluate(T->rchild);
            break;
        case '-':
            return evaluate(T->lchild) - evaluate(T->rchild);
            break;
        case '/':
            return evaluate(T->lchild) / evaluate(T->rchild);
            break;
        case '@':
            return pow(evaluate(T->lchild),evaluate(T->rchild));
            break;
        case 'L':
            return log(evaluate(T->lchild))/log(evaluate(T->rchild));
        default:
            break;
        }
    }
    else if (T->elem->tipo == 6)
    {
        switch(T->elem->atrib.op)
        {
        case 'R':
            return sqrt(evaluate(T->rchild));
            break;
        case 'S':
            return sin(evaluate(T->rchild));
            break;
        case 'C':
            return cos(evaluate(T->rchild));
            break;
        case '~':
            return 0 - evaluate(T->rchild);
            break;
        default:
            break;
        }
    }
    return 0;
}