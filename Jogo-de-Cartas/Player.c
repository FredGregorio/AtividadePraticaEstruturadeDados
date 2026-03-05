#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "StackCards.h"
#include "QueueActions.h" 
#include "Player.h"

void initPlayer(Player* player, const char* name) {
    strncpy(player->name, name, sizeof(player->name) - 1);
    initStack(&player->hand);
    player->points = 0;
}

void addCardToPlayer(Player* player, Card card) {
    push(&player->hand, card);
}

Card removeCardFromPlayer(Player* player, int cardIndex) {
    Stack temp;
    initStack(&temp);
    Card selected;
    
    // Transferir cartas até o índice desejado
    for (int i = 0; i < cardIndex; i++) {
        Card c = pop(&player->hand);  
        push(&temp, c);               
    }
    
    //remover carta selecionada
    selected = pop(&player->hand);
    
    //devolver cartas restantes
    while (!isEmptyStack(&temp)) {
        Card c = pop(&temp);         
        push(&player->hand, c);       
    }
    
    return selected;
}

void displayPlayerHand(Player* player) {
    printf("\nCartas de %s:\n", player->name);
    if (player->hand.size == 0) {
        printf("  Nenhuma carta na mão\n");
        return;
    }
    
    //criar uma pilha temporária para preservar a ordem
    Stack tempStack;
    initStack(&tempStack);
    int count = player->hand.size;
    
    //transferir cartas para a pilha temporária (invertendo a ordem)
    while (!isEmptyStack(&player->hand)) {
        Card c = pop(&player->hand);
        push(&tempStack, c);
    }
    
    //mostrar cartas
    for (int i = 0; i < count; i++) {
        Card c = pop(&tempStack);
        printf("  %d: [%c-%c]\n", count - i, c.value, c.suit);
        push(&player->hand, c);
    }
}

//Player.c