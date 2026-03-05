#ifndef TYPES_H
#define TYPES_H

typedef struct Card{
    char suit;
    char value;
} Card;

typedef struct CardNode{
    Card card;
    struct CardNode* next;
} CardNode;

typedef struct Stack{
    CardNode * top;
    int size;
    
} Stack;





typedef struct {
    char name[50];
    Stack hand;   //cartas na mão do jogador 
    int points;
} Player;

typedef struct PlayerNode{
    Player player;
    struct PlayerNode* next;
} PlayerNode;

typedef struct Queue{
    PlayerNode * front; //inicio da fila
    PlayerNode * rear; //fim da fila
    int size;
    
} Queue;




#endif