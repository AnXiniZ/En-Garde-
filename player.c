#include <stdio.h>
#include <string.h>

#include "main.h"

int initActionArrays(char* actionArray);
int initActionUsed(char* actionsNext);
void printActionArrays(char* actionArray);

void playerTurn(char* playerActionsPrev, char* playerActionsCurr, char* playerActionsNext, int player) {
    int i;
    char* actionsPrev = playerActionsPrev;
    char* actionsCurr = playerActionsCurr;
    char* actionsNext = playerActionsNext;
    printf("Moves:\n");
    for (i = 1; i <= NUM_OF_MOVES; i++) {
        if (i != NUM_OF_MOVES) printf("[%d] %s, ", i, moveNames[i-1]);
        else printf("[%d] %s\n\n", i, moveNames[i-1]);
    }
    int actionsUsed = initActionUsed(actionsNext);
    memcpy(actionsPrev, actionsCurr, sizeof(actionsCurr));
    memcpy(actionsCurr, actionsNext, sizeof(actionsNext));
    initActionArrays(actionsNext);
    printf("  Actions last turn  |   Actions this turn  |  Actions next turn:\n");
    printActionArrays(actionsPrev);
    printf(" | ");
    printActionArrays(actionsCurr);
    printf(" | ");
    printActionArrays(actionsNext);
    printf("\n\n");
    while (actionsUsed < 6) {
        if (player == 1) printf("Player 1, please enter your move:\n");
        else if (player == 2) printf("Player 2, please enter your move:\n");
        else printf("Please enter your move:\n");
        int move;
        scanf("%d", &move);
        move = move - 1;
        if (move < NUM_OF_MOVES) {
            for (i = 0; i < moveCosts[move]; i++) {
                if (actionsUsed < 6) actionsCurr[actionsUsed] = moveIcons[move][i];
                else actionsNext[actionsUsed - 6] = moveIcons[move][i];
                actionsUsed++;
            }
            printf("Your chosen move: %s\n\n", moveNames[move]);
            printf("  Actions last turn  |   Actions this turn  |  Actions next turn:\n");
            printActionArrays(actionsPrev);
            printf(" | ");
            printActionArrays(actionsCurr);
            printf(" | ");
            printActionArrays(actionsNext);
            printf("\n\n");
        }
    }
}