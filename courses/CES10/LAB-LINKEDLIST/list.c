#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#define NDEBUG

#include "list.h"

/************** STATIC FUNCTIONS ************************/
// functions not visible outside this file

// Create a new node
//
// Return:
// - NULL on failure

static struct node *create_node(size_t key, long int value, struct node *next)
{
  struct node *n = (struct node *)malloc(sizeof(struct node));

  if (n != NULL)
  {
    n->key = key;
    n->value = value;
    n->next = next;
  }

  return n;
}

// Print a node as '[key]=value'
static void print_node(struct node *n)
{
  printf("[%zu]=%ld", n->key, n->value);
}

/******************* NON STATIC FUNCTIONS *****************/
// functions visible outside this file

// Print the list values using the function print_node
void print_list(struct list *list)
{
  struct node *n = (list == NULL) ? NULL : list->head; // if list == NULL, list->head does not work

  while (n != NULL)
  {
    print_node(n);
    printf("\n");
    n = n->next;
  }
}

// Create a new empty list in heap
//
// Return:
// - NULL on failure
struct list *new_list()
{
  struct list *p = (struct list *)malloc(sizeof(struct list));

  if (p != NULL)
  {
    // Initialization (or calloc)
    p->head = p->tail = NULL;
    p->size = 0;
  }

  return p;
}

// Delete all the node's and list structures
void delete_list(struct list *lista)
{
  if (lista == NULL)
    return;

  struct node *n = lista->head;

  while (n != NULL)
  {
    lista->head = n->next;
    free(n);
    n = lista->head;
  }

  free(lista);
}

// Add a new (key,value) in the end of the list
//
// Return:
// - NULL on failure
// - pointer to (key,value) node on success
struct node *append(struct list *list, size_t key, int long value)
{
  struct node *new_node = create_node(key, value, NULL);

  assert(new_node != NULL);
  assert(new_node->key == key);
  assert(new_node->value == value);
  assert(new_node->next == NULL);

  // update the list structure
  if (list->head == NULL){
    list->head = new_node;
    list->tail = list->head;
  }

  if (list->tail != NULL)
  {
    list->tail->next = new_node;
    list->tail = list->tail->next;
  }
  list->size++;
  return new_node;
}

// Compute an elementwise operation (op) over nodes
//
// Return:
// - NULL on failure
// - list with the result
struct list *elementwise_op(el_wise_op_t op, struct node *n1, struct node *n2)
{

  struct list *res_list = new_list();
  while (n1 != NULL || n2 != NULL)
  {
    if(n1 != NULL) {
      append(res_list, n1->key, n1->value);
      n1 = n1->next;
      }
    if(n2 != NULL){
      append(res_list, n2->key, n2->value);
      n2 = n2->next;
    }
  }
  struct node *first_iterator = res_list->head, *second_iterator, *third_iterator;
  int how_many_eliminated = 0;
  while(first_iterator->next != NULL){
    second_iterator = first_iterator->next;
    while(second_iterator != NULL){
      if(second_iterator->key < first_iterator->key){
        first_iterator->key ^= second_iterator->key; first_iterator->value ^= second_iterator->value;
        second_iterator->key ^= first_iterator->key; second_iterator->value ^= first_iterator->value;
        first_iterator->key ^= second_iterator->key; first_iterator->value ^= second_iterator->value;
      }
      second_iterator = second_iterator->next;
    }
    first_iterator = first_iterator->next;
  }
  first_iterator = res_list->head;
  while(first_iterator->next != NULL){
    second_iterator = first_iterator->next;
    while(second_iterator != NULL){
      if(second_iterator->key == first_iterator->key && second_iterator->value != 0 && first_iterator->value != 0){
        how_many_eliminated++;
        first_iterator->value = op(first_iterator->value,second_iterator->value);
        third_iterator = second_iterator;
        while(third_iterator->next != NULL){
          third_iterator->key = third_iterator->next->key;
          third_iterator->value = third_iterator->next->value;
          third_iterator = third_iterator->next;
        }
        third_iterator->value = 0;
        third_iterator->key = 0;
      }
      second_iterator = second_iterator->next;
    }
    first_iterator = first_iterator->next;
  }
  first_iterator = res_list->head;
  while(first_iterator != NULL){
    if(first_iterator->value == 0 && first_iterator->key != 0){
        how_many_eliminated++;
        third_iterator = first_iterator;
        while(third_iterator->next != NULL){
          third_iterator->key = third_iterator->next->key;
          third_iterator->value = third_iterator->next->value;
          third_iterator = third_iterator->next;
        }
      }
      else first_iterator = first_iterator->next;
  }
  first_iterator = res_list->head;
  for(int i = 0; i < (int)res_list->size - how_many_eliminated-1; i++){
    first_iterator = first_iterator->next;
  }
  first_iterator->next = NULL;
  if(res_list->head->value == 0) res_list->head = NULL;
  /* for(int i = 0; i < how_many_eliminated; i++){
    struct node *auxiliar = first_iterator->next;
    free(first_iterator);
    first_iterator = auxiliar;
  }*/
  res_list->size -= how_many_eliminated;
  
  return res_list;
}
      


