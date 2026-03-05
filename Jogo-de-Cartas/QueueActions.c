#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "QueueActions.h"
#include "StackCards.h"

void initQueue (Queue * queue){
    queue->front = queue->rear = NULL;
    queue->size = 0;
}

int isEmptyQueue(Queue * queue){
    return queue->front == NULL;
}

void enqueue(Queue * queue, Player player){
    PlayerNode * newNode = (PlayerNode*)malloc(sizeof(PlayerNode));
    if (!newNode) {
        printf("Erro de alocação de memória\n");
        exit(EXIT_FAILURE);
    }

    newNode->player = player;
    newNode->next = NULL;

    if(queue->rear == NULL){
        queue->front = queue->rear = newNode;
    }
    else{
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
}

Player dequeue(Queue* queue){
    if (isEmptyQueue(queue)){
        printf("Erro: Fila Vazia\n");
        Player invalid;
        strcpy(invalid.name, "INVALID");
        invalid.points = -1;
        initStack(&invalid.hand);
        return invalid;
    }

    PlayerNode * temp = queue-> front;
    Player dequeuedPlayer = temp->player;
    queue->front = temp->next;
    if(queue->front == NULL){
        queue->rear = NULL;
    }
    free(temp);
    queue->size--;
    return dequeuedPlayer;
}

Player front(Queue * queue){
    if (isEmptyQueue(queue)){
        printf("Erro: Fila Vazia\n");
        Player invalid;
        strcpy(invalid.name, "INVALID");
        invalid.points = -1;
        initStack(&invalid.hand);
        return invalid;
    }
    return queue->front->player;
}

void displayQueue(Queue * queue){
    if (isEmptyQueue(queue)){
        printf("Fila Vazia.\n");
        return;
    }
    PlayerNode * temp = queue->front;
    printf("Fila de Jogadores (%d): \n", queue->size);

    while(temp){
        printf("- %s (Pontos: %d, Cartas: %d)\n", temp->player.name, temp->player.points, temp->player.hand.size);
        temp = temp->next;
    }
    printf("\n");
}

void rotateQueue(Queue* queue){
    if (isEmptyQueue(queue) || queue->front == queue->rear) {
        return;
    }
    PlayerNode* temp = queue->front;
    queue->front = (PlayerNode*)temp->next;
    queue->rear->next = (struct PlayerNode*)temp;
    queue->rear = temp;
    temp->next = NULL;
}

//QueueActions.c