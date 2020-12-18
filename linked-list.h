/*
 *  =========
 *  UNLICENSE
 *  =========
 *
 *  This is free and unencumbered software released into the public domain.
 *
 *  Anyone is free to copy, modify, publish, use, compile, sell, or
 *  distribute this software, either in source code form or as a compiled
 *  binary, for any purpose, commercial or non-commercial, and by any
 *  means.
 *
 *  In jurisdictions that recognize copyright laws, the author or authors
 *  of this software dedicate any and all copyright interest in the
 *  software to the public domain. We make this dedication for the benefit
 *  of the public at large and to the detriment of our heirs and
 *  successors. We intend this dedication to be an overt act of
 *  relinquishment in perpetuity of all present and future rights to this
 *  software under copyright law.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 *
 *  For more information, please refer to <http://unlicense.org/>
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct Node {
  void *data;
  struct Node *next;
} Node;

typedef struct LList {
  Node *head;
  Node *tail;
  size_t element_size;
} LList;

LList *llist_new(size_t element_size);
Node *node_new(void *data, size_t data_size, Node *next);

void llist_push_back(LList *list, void *val);
void llist_push_front(LList *list, void *val);

void llist_pop_back(LList *list);
void llist_pop_front(LList *list);

Node *llist_tail(LList *list);
#define llist_get_head(list) (list->head)

// TODO:
//   void llist_insert(LList *list, void *val, size_t index);
//   void llist_remove(LList *list, size_t index);

size_t llist_size(LList *list);
void llist_free(LList *list);

#ifdef LINKED_LIST_IMPLEMENTATION

LList *llist_new(size_t element_size)
{
  LList *list = (LList *)malloc(sizeof(LList));
  list->head = NULL;
  list->element_size = element_size;
  return list;
}

Node *node_new(void *data, size_t data_size, Node *next)
{
  Node *node = (Node *)malloc(sizeof(Node));

  node->data = malloc(data_size);
  node->next = next;

  memcpy(node->data, data, data_size);

  return node;
}

void llist_push_back(LList *list, void *val)
{
  if (list->head == NULL) {
    list->head = node_new(val, list->element_size, NULL);
  } else {
    llist_tail(list)->next = node_new(val, list->element_size, NULL);
  }
}

void llist_push_front(LList *list, void *val)
{
  list->head = node_new(val, list->element_size, list->head);
}

void llist_pop_back(LList *list) 
{
  Node *tail = llist_tail(list);
  if (list->head == tail) {
    llist_pop_front(list);
  } else {
    Node *tmp = list->head;

    while (tmp->next != llist_tail(list)) {
      tmp = tmp->next;
    }

    free(tmp->next->data);
    free(tmp->next);

    tmp->next = NULL;
  }
}


void llist_pop_front(LList *list)
{
  Node *next = list->head->next;

  free(list->head->data);
  free(list->head);

  list->head = next;
}


size_t llist_size(LList *list)
{
  if (list->head == NULL) {
    return 0;
  } else {
    size_t i = 1;
    Node *tmp = list->head;

    while (tmp->next != NULL) {
      i++;
      tmp = tmp->next;
    }

    return i;
  }
}

Node *llist_tail(LList *list)
{
  Node *tmp = list->head;

  while (tmp->next != NULL) {
    tmp = tmp->next;
  }

  return tmp;
}

void llist_free(LList *list)
{
  Node *tmp = list->head;
  Node *next;

  while (tmp != NULL) {
    next = tmp->next;
    free(tmp->data);
    free(tmp);
    tmp = next;
  }
}

#endif // LINKED_LIST_IMPLEMENTATION

#endif // LINKED_LIST_H

