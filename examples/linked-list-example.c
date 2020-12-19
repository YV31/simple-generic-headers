#include <stdio.h>

#define  LINKED_LIST_IMPLEMENTATION
#include "linked-list.h"

#define GET_VOID(PTR, TYPE) ( *(TYPE *) (PTR) )

#define llist_print_all(list, type)               \
  do {                                            \
    Node *tmp = list->head;                       \
    while(tmp != NULL) {                          \
      printf("%d\n", GET_VOID(tmp->data, type));  \
      tmp = tmp->next;                            \
    }                                             \
  } while (0)

int main()
{
  int val = 10;

  LList *list = llist_new(sizeof(int));
  
  llist_push_back(list, &val);
  val = 30;
  llist_insert(list, &val, 0);
  val = 10;
  llist_push_back(list, &val);

  printf("Size: %zd\n", llist_size(list));
  printf("Head: %d\n", GET_VOID(list->head->data, int));
  printf("Tail: %d\n", GET_VOID(llist_tail(list)->data, int));

  llist_print_all(list, int);
  llist_free(list);
}
