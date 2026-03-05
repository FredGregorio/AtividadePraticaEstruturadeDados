#include <stdio.h>
#include "types.h"
#include "StackCards.h"
#include "Player.h"
#include "Actions.h"

// jogador compra carta
void buyCard(Player* player, Stack* deck) {
    if (!isEmptyStack(deck)) {
        Card newCard = pop(deck);
        addCardToPlayer(player, newCard);
        printf("Você comprou: [%c%c]\n", newCard.value, newCard.suit);
    } else {
        printf("Baralho vazio!\n");
    }
}

//jogar descarta carta
void discardCard(Player* player, int cardIndex, Stack* discardPile) {
    if (player->hand.size > 0) {
        Card discarded = removeCardFromPlayer(player, cardIndex - 1);
        push(discardPile, discarded);
        printf("Descartou: [%c%c]\n", discarded.value, discarded.suit);
    } else {
        printf("Você não tem cartas!\n");
    }
}

//verifica se a jogada é valida
int isValidPlay(Card topDiscard, Card playedCard) {
    return (topDiscard.suit == playedCard.suit) || 
           (topDiscard.value == playedCard.value);
}

//Actions.c
