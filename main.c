#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "main.h"

void initAllActionArrays(char* playerActionsPrev, char* playerActionsCurr, char* playerActionsNext, char* botActionsPrev, char* botActionsCurr, char* botActionsNext);
void announceGameState(char* playerActionsPrev, char* playerActionsCurr, char* playerActionsNext, char* botActionsPrev, char* botActionsCurr, char* botActionsNext, int playerPos, int botPos, int playerScore, int botScore, int gamemode);
void playerTurn(char* playerActionsPrev, char* playerActionsCurr, char* playerActionsNext, int player);
void botTurn(char* botActionsPrev, char* botActionsCurr, char* botActionsNext, char* playerActionsPrev, int playerPos, int botPos);
int compareResults(char* playerActionsPrev, char* playerActionsCurr, char* botActionsPrev, char* botActionsCurr, int* playerPos, int* botPos, int* playerScore, int* botScore);

int main(int argc, char* argv) {
    srand(time(NULL));
    char playerActionsPrev[6];
    char playerActionsCurr[6];
    char playerActionsNext[6];
    char player2ActionsPrev[6];
    char player2ActionsCurr[6];
    char player2ActionsNext[6];
    char botActionsPrev[6];
    char botActionsCurr[6];
    char botActionsNext[6];
    int playerPos = 3;
    int player2Pos = 6;
    int botPos = 6;
    int playerScore = 0;
    int player2Score = 0;
    int botScore = 0;
    int maxScore = 5;
    int i;
    int result = 0;
    int round = 1;
    int gamemode = 1;
    printf("Choose gamemode (0 = pve, 1 = pvp): ");
    scanf("%d", gamemode);
    getchar();
    printf("\n");
    if (gamemode == 0) {
        while (playerScore < maxScore && botScore < maxScore) {
            if (result == -1) {
                playerPos = 2;
                botPos = 5;
            }
            else if (result == -2) {
                playerPos = 4;
                botPos = 7;
            }
            else {
                playerPos = 3;
                botPos = 6;
            }
            initAllActionArrays(playerActionsPrev, playerActionsCurr, playerActionsNext, botActionsPrev, botActionsCurr, botActionsNext);
            result = 0;
            printf("Round %d:\n\n", round);
            while (result == 0) {
                announceGameState(playerActionsPrev, playerActionsCurr, playerActionsNext, botActionsPrev, botActionsCurr, botActionsNext, playerPos, botPos, playerScore, botScore, gamemode);
                printf("==================================================\n\n");
                playerTurn(playerActionsPrev, playerActionsCurr, playerActionsNext, 0);
                printf("==================================================\n\n");
                botTurn(botActionsPrev, botActionsCurr, botActionsNext, playerActionsPrev, playerPos, botPos);
                printf("==================================================\n\n");
                result = compareResults(playerActionsPrev, playerActionsCurr, botActionsPrev, botActionsCurr, &playerPos, &botPos, &playerScore, &botScore);
                if (result != 0) {
                    announceGameState(playerActionsPrev, playerActionsCurr, playerActionsNext, botActionsPrev, botActionsCurr, botActionsNext, playerPos, botPos, playerScore, botScore, gamemode);
                    printf("==================================================\n\n");
                }
            }
            round++;
        }
        if (playerScore == maxScore) printf("You won!\n\n");
        else printf("You lost!\n\n");
    }
    else (gamemode == 1) {
        while (playerScore < maxScore && player2Score < maxScore) {
            if (result == -1) {
                playerPos = 2;
                player2Pos = 5;
            }
            else if (result == -2) {
                playerPos = 4;
                player2Pos = 7;
            }
            else {
                playerPos = 3;
                player2Pos = 6;
            }
            initAllActionArrays(playerActionsPrev, playerActionsCurr, playerActionsNext, player2ActionsPrev, player2ActionsCurr, player2ActionsNext);
            result = 0;
            printf("Round %d:\n\n", round);
            while (result == 0) {
                announceGameState(playerActionsPrev, playerActionsCurr, playerActionsNext, player2ActionsPrev, player2ActionsCurr, player2ActionsNext, playerPos, player2Pos, playerScore, player2Score, gamemode);
                printf("==================================================\n\n");
                playerTurn(playerActionsPrev, playerActionsCurr, playerActionsNext, 1);
                printf("==================================================\n\n");
                playerTurn(player2ActionsPrev, player2ActionsCurr, player2ActionsNext, 2);
                printf("==================================================\n\n");
                result = compareResults(playerActionsPrev, playerActionsCurr, player2ActionsPrev, player2ActionsCurr, &playerPos, &player2Pos, &playerScore, &player2Score);
                if (result != 0) {
                    announceGameState(playerActionsPrev, playerActionsCurr, playerActionsNext, player2ActionsPrev, player2ActionsCurr, player2ActionsNext, playerPos, player2Pos, playerScore, player2Score, gamemode);
                    printf("==================================================\n\n");
                }
            }
            round++;
        }
        else {
            printf("Wrong gamemode input.\n\n");
        }
        if (playerScore == maxScore) printf("Player 1 won!\n\n");
        else printf("Player 2 won!\n\n");
    }
    return 0;
}