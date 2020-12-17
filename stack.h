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

/*
 *  =====================
 *  Generic Stack Library
 *  =====================
 *
 *  Usage:
 *    Define STACK_IMPLEMENTATION in only one file.
 *
 *      #define STACK_IMPLEMENTATION
 *      #include "stack.h"
 *
 *      <type> val = <value>;
 *      <type> top;
 *      Stack *stack = stack_new(sizeof(<type>), <size>); // Create a new stack
 *      stack_push(stack, &val);      // Push value on the stack
 *      top = *(<type> *)stack_top(); // Get top stack value
 *      stack_grow(stack, <i>);       // Grow stack in <i> elements
 *      stack_pop(stack);             // Pop the stack
 *      stack_free(stack);            // Free stack memory
 */

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
  void *data;          // Points to the actual data
  void *sp;            // Points to the next top element on stack
  size_t element_size; // Element size in bytes
  size_t max_size;     // Max size in bytes
} Stack;

/*
 *  Returns a pointer to a new stack.
 *  Takes the size of the type that will be stored in the stack
 *  and the maximum number of elements of the stack.
 */
Stack *stack_new(size_t element_size, size_t size);

/*  
 *  Push value to the stack.
 *  Return 0 if the stack isn't full and push a element to the stack.
 *  Return 1 if the stack is full.
 *  Takes a address to an stack and the address to an value to be pushed.
 */
int stack_push(Stack *stack, void *val);

/*  
 *  Pop the stack.
 *  Returns 0 if the stack_size is biger than 0 and pop a element out of the
 *  stack. Returns 1 if the stack_size is 0.
 *  Takes a address to an stack.
 */
int stack_pop(Stack *stack);

/*
 *  Grow the stack max_size.
 *  Takes a address to an stack and the amount in elements to increase it.
 */
void stack_grow(Stack *stack, size_t size);

/*
 *  Free stack memory.
 *  Takes a address to an stack.
 */
void stack_free(Stack *stack);

// Returns an void pointer to the top of the stack.
#define stack_top(stack) \
  ( (void *)((uint8_t *)(stack)->sp - ((stack)->element_size)) )

// Returns the size of the stack in elements.
#define stack_size(stack) \
  ( ((uint8_t *)(stack)->sp - (uint8_t *)(stack)->data) / (stack)->element_size )

// Checks is the stack is empty.
#define stack_empty(stack)  ( stack_size(stack) == 0 ? 1 : 0 )

// Returns a void pointer to the given index.
#define stack_get(stack, i) \
  ( (void *)((uint8_t *)(stack)->data + ((i) * (stack)->element_size)) )

#ifdef STACK_IMPLEMENTATION

Stack *stack_new(size_t element_size, size_t size)
{
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->element_size = element_size;
  stack->max_size = element_size * size;
  stack->data = malloc(stack->max_size);
  stack->sp = stack->data;
  return stack;
}

int stack_push(Stack *stack, void *val)
{
  if (stack_size(stack) < stack->max_size / stack->element_size) {
    memcpy(stack->sp, val, stack->element_size);
    stack->sp = (uint8_t *)((uint8_t *)stack->sp + stack->element_size);
    return 0;
  } else {
    return 1;
  }
}

int stack_pop(Stack *stack)
{
  if (stack_size(stack) > 0) {
    stack->sp = (uint8_t *)((uint8_t *)stack->sp - stack->element_size);
    return 0;
  } else {
    return 1;
  }
}

void stack_grow(Stack *stack, size_t size)
{
  stack->max_size += stack->element_size * size;
  stack->data = realloc(stack->data, stack->max_size);
}

void stack_free(Stack *stack)
{
  free(stack->data);
  free(stack);
}

#endif // STACK_IMPLEMENTATION

#endif // STACK_H

/*
 *  ================
 *  REVISION HISTORY
 *  ================
 *
 *  1.0 - Initial release.              [12/12/20]
 *  1.1 - Fix void pointer arithmetics. [17/12/20]
 */

