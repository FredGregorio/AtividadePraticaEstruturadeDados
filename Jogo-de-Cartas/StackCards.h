#ifndef STACK_CARDS_H
#define STACK_CARDS_H

#include "types.h"

void initStack(Stack *stack);
int isEmptyStack(Stack *stack);
void push(Stack *stack, Card card);
Card pop(Stack *stack);
Card peek(Stack* stack);
void displayStack(Stack *stack);

#endif