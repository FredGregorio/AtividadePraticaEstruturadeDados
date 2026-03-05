#ifndef ACTIONS_H
#define ACTIONS_H

#include "types.h"
#include "Player.h"
#include "StackCards.h"

void buyCard(Player* player, Stack* deck);
void discardCard(Player* player, int cardIndex, Stack* discardPile);
int isValidPlay(Card topDiscard, Card playedCard);

#endif