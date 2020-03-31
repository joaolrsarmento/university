#ifndef LIST_H // avoid to redeclare the functions
#define LIST_H

struct node
{
  size_t key;
  long int value;
  struct node *next;
};

struct list
{
  struct node *head;
  struct node *tail;
  size_t size;
};

// Declare o tipo 'el_wise_op_t' como um function pointer.
//
// A função recebe dois long int (correspondem aos value's dos nodes) e
// retorna um long int (corresponde ao resultado de alguma operação elementwise)
typedef long int (*el_wise_op_t)(long int, long int);

/************* FUNCTION DECLARATIONS *****************/

struct list *new_list();

void delete_list(struct list *lista);

struct node *append(struct list *, size_t key, int long value);

void print_list(struct list *list);

struct list *elementwise_op(el_wise_op_t op, struct node *n1, struct node *n2);

#endif // LIST_H