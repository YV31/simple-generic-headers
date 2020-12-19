#define STACK_IMPLEMENTATION
#include "stack.h"

#include <stdio.h>

int main()
{
  int val = 200;
  int top;
  Stack *stack = stack_new(sizeof(int), 2); // Create a new stack

  printf("| stack->data %p | stack->sp %p | stack->max_size %zd | stack->element_size %zd |\n", 
         stack->data, stack->sp, stack->max_size, stack->element_size);

  stack_push(stack, &val);      // Push value on the stack
  stack_push(stack, &val);

  top = *(int *)stack_top(stack); // Get top stack value
  stack_grow(stack, 1);           // Grow stack in <i> elements
  stack_pop(stack);               // Pop the stack

  printf("| stack->data %p | stack->sp %p | stack->max_size %zd | stack->element_size %zd |\n", 
         stack->data, stack->sp, stack->max_size, stack->element_size);

  stack_free(stack);            // Free stack memory

  printf("%d\n", top);
  return 0;
}
