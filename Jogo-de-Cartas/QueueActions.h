#ifndef QUEUE_ACTIONS_H
#define QUEUE_ACTIONS_H

#include "types.h"

void initQueue(Queue *queue);
int isEmptyQueue(Queue *queue);
void enqueue(Queue *queue, Player player);
Player dequeue(Queue *queue);
Player front(Queue *queue);
void displayQueue(Queue *queue);
void rotateQueue(Queue *queue);

#endif