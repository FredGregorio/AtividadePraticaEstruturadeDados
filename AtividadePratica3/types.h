#ifndef TYPES_H
#define TYPES_H

typedef struct Card{
    char suit;
    char value;
} Card;

typedef struct Node{
    Card card;
    struct Node* next;
} Node;

typedef struct Stack{
    Node * top;
    int size;
    
} Stack;

typedef struct Queue{
    Node * front; //inicio da fila
    Node * rear; //fim da fila
    int size;
    
} Queue;

typedef struct {
    char name[50];
    Stack hand;   //cartas na mão do jogador (pode ser uma pilha ou lista)
    int points;
} Player;


#endif