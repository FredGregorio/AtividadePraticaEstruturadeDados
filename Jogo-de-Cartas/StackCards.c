#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "StackCards.h"


void initStack(Stack * stack){
    stack->top = NULL;
    stack->size = 0;
}

int isEmptyStack(Stack * stack){
    return stack->top == NULL;
}

void push(Stack * stack, Card card){
    CardNode * newNode = (CardNode*)malloc(sizeof(CardNode));
    if(!newNode) {
        printf("Erro de alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    newNode->card = card;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

Card pop(Stack * stack) {
    if (isEmptyStack(stack)){
        printf("Erro de fila vazia\n");
        return (Card){'\0', '\0'};
    }

    CardNode * temp = stack->top;
    Card poppedCard = temp->card;
    stack->top =temp->next;
    free(temp);
    stack->size--;
    return poppedCard;

}

Card peek(Stack* stack){
    if (isEmptyStack(stack)){
        printf("Erro de fila vazia\n");
        return (Card){'\0', '\0'};
    }
    return stack->top->card;

}

void displayStack(Stack * stack){
    if (isEmptyStack(stack)){
        printf("Erro de fila vazia\n");
        return;
    }
    CardNode * temp = stack->top;
    printf("Pilha (%d cartas): ", stack->size);
    while(temp){
         printf("[%c%c] ", temp->card.value, temp->card.suit);
        temp = temp->next;
    }
    printf("\n");
}



//StackCards.c