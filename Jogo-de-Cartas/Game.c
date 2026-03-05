#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "StackCards.h"
#include "QueueActions.h"
#include "Deck.h"
#include "Player.h"
#include "Actions.h"
#include "Game.h"

void startGame(int numPlayers) {
    //inicializar estruturas
    Stack deck, discardPile;
    Queue turnQueue;
    
    initStack(&deck);
    initStack(&discardPile);
    initQueue(&turnQueue);
    
    //criar e embaralhar baralho
    createDeck(&deck);
    shuffleDeck(&deck);
    
    //criar jogadores
    for (int i = 0; i < numPlayers; i++) {
        Player p;
        char name[50];
        sprintf(name, "Jogador %d", i + 1);
        initPlayer(&p, name);
        enqueue(&turnQueue, p);
    }
    
    //distribuir 5 cartas para cada jogador
    PlayerNode* current = turnQueue.front;
    for (int i = 0; i < 5; i++) {
        while (current) {
            if (!isEmptyStack(&deck)) {
                addCardToPlayer(&current->player, pop(&deck));
            }
            current = current->next;
        }
        current = turnQueue.front;
    }
    
    //iniciar primeira carta no descarte
    if (!isEmptyStack(&deck)) {
        push(&discardPile, pop(&deck));
    }
    
    //loop principal do jogo
    int gameOver = 0;
    while (!gameOver && !isEmptyQueue(&turnQueue)) {
        Player* currentPlayer = &turnQueue.front->player;
        printf("\n--- VEZ DE %s ---\n", currentPlayer->name);
        
       

        int action;
        do {
             //mostrar estado do jogo
            printf("Topo do descarte: [%c-%c]\n", peek(&discardPile).value, peek(&discardPile).suit);
            displayPlayerHand(currentPlayer);
            printf("\nEscolha uma ação:\n");
            printf("1. Comprar carta\n");
            printf("2. Descartar carta\n");
            printf("Escolha: ");
            scanf("%d", &action);

            if (action == 1) {
                buyCard(currentPlayer, &deck);
            } else if (action == 2) {
                if (currentPlayer->hand.size == 0) {
                    printf("Você não tem cartas para descartar!\n");
                } else {
                    
                    printf("Escolha o número da carta para descartar: ");
                    int idx;
                    scanf("%d", &idx);

                    Card top = peek(&discardPile);
                    Stack temp = currentPlayer->hand;

                    CardNode* node = temp.top;
                    int count = 1;
                    while (node && count < idx) {
                        node = node->next;
                        count++;
                    }

                    if (idx < 1 || idx > currentPlayer->hand.size) {
                        printf("Índice inválido!\n");
                        action = 0;
                    } else if (node && isValidPlay(top, node->card)) {
                        discardCard(currentPlayer, idx, &discardPile);
                    } else {
                        printf("Jogada inválida! Carta não combina com o topo do descarte.\n");
                        action = 0;
                    }
                }
            }
        } while (action != 1 && action != 2);
        
        //verificar se o jogador venceu
        if (currentPlayer->hand.size == 0) {
            printf("\nPARABÉNS! %s VENCEU O JOGO!\n", currentPlayer->name);
            gameOver = 1;
        }

        //rotacionar jogador 
        Player updatedPlayer = *currentPlayer;
        dequeue(&turnQueue);
        enqueue(&turnQueue, updatedPlayer);

        //reutilizar descarte se baralho acabar
        if (isEmptyStack(&deck) && !isEmptyStack(&discardPile)) {
            Card top = pop(&discardPile);
            while (!isEmptyStack(&discardPile)) {
                push(&deck, pop(&discardPile));
            }
            push(&discardPile, top);
            shuffleDeck(&deck);
            printf("\nBaralho reciclado!\n");
        }
    }
}