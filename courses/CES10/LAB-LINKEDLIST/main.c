#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define NDEBUG

#include "list.h"

// read values into the list from stdin
void inputVector(struct list *list) {
  long int index, value;

  while (scanf(" %ld,%ld", &index, &value)==2)
    append(list, (size_t)index, value);
}


long sum(long a, long b) {
  return a + b;
}

int main() {
  struct list *l1 = new_list();
  struct list *l2 = new_list();

  // Testes para garantir que seu código está correto
  assert(l1 != NULL); assert(l2 != NULL);
  assert(l1 != l2);
  assert(l1->head == NULL); assert(l2->head == NULL);
  assert(l1->tail == NULL); assert(l2->tail == NULL);
  assert(l1->size == 0); assert(l2->size == 0);

  // read values from stdin
  inputVector(l1);
  inputVector(l2);

  // 1 - teste seu código antes de prosseguir
  // A impressão das listas devem estar corretas
  /*printf("Lista 1:\n");
  print_list(l1);
  printf("\nLista 2:\n");
  print_list(l2);
  printf("\n");*/

  // 2 - faça outros testes que achar conveniente

  // perform over the key elements
  struct list* res = elementwise_op(sum, l1->head, l2->head);

  delete_list(l1);
  delete_list(l2);

  print_list(res);

  delete_list(res);
  return 0;
}