#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"
#include "StackCards.h"
#include "Player.h"
#include "Game.h"
#include "Actions.h"

int main() {
    srand(time(NULL));
    int choice;
    
    do {
        printf("\nJOGO DE CARTAS\n");
        printf("1. Iniciar novo jogo\n");
        printf("2. Regras do jogo\n");
        printf("3. Sair\n");
        printf("Escolha: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                int numPlayers;
                printf("Número de jogadores (2-4): ");
                scanf("%d", &numPlayers);
                
                if (numPlayers >= 2 && numPlayers <= 4) {
                    startGame(numPlayers);
                } else {
                    printf("Número inválido de jogadores!\n");
                }
                break;
            }
            case 2: {
                int subChoice;
                do {
                    printf("\n--- REGRAS DO JOGO ---\n");
                    printf("1. O objetivo é descartar todas as cartas da mão.\n");
                    printf("2. Para descartar uma carta, ela deve ter:\n");
                    printf("   - O mesmo valor (ex.: 'A', '2', 'K') OU\n");
                    printf("   - O mesmo naipe (ex.: 'C' para Copas, 'O' para Ouros).\n");
                    printf("3. Se não puder descartar, compre uma carta do baralho.\n");
                    printf("4. O primeiro jogador a ficar sem cartas vence!\n");
                    printf("\n--- SIGNIFICADO DAS CARTAS ---\n");
                    printf("Valores:\n");
                    printf("   - 'A': Ás\n");
                    printf("   - '2' a '9': Valores numéricos\n");
                    printf("   - 'D': 10\n");
                    printf("   - 'J': Valete\n");
                    printf("   - 'Q': Rainha\n");
                    printf("   - 'K': Rei\n");
                    printf("Naipes:\n");
                    printf("   - 'C': Copas\n");
                    printf("   - 'O': Ouros\n");
                    printf("   - 'P': Paus\n");
                    printf("   - 'E': Espadas\n");
                    printf("\nDigite 0 para voltar ao menu inicial.\n");
                    printf("Escolha: ");
                    scanf("%d", &subChoice);
                } while (subChoice != 0);
                break;
            }
            case 3:
                printf("Fechando programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (choice != 3);
    
    return 0;
}

//Main.c