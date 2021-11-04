#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

int initActionArrays(char* actionArray);
int initActionUsed(char* actionsNext);
void printActionArrays(char* actionArray);
void printUnknownActionArrays();

int chance() {
    int random = rand();
    const int max = (RAND_MAX / 100) * 100;
    while (random > max) {
        random = rand();
    }
    return (random % 100) + 1;
}

int botMove(int* lastMove, char* botActionsCurr, char* playerActionsPrev, int playerPos, int botPos) {
    int distance = botPos - playerPos;
    int random = chance();
    printf("%d", random);
    switch (distance) {
        case 1:
            if (botActionsCurr[0] == ' ') {
                if (playerActionsPrev[4] == '-' && playerActionsPrev[5] == '-') {
                    if (random <= 80) {
                        *lastMove = 1;
                        return 1;
                    }
                    else {
                        *lastMove = 6;
                        return 6;
                    }
                }
                else if (playerActionsPrev[4] == '-' && playerActionsPrev[5] == 'X' || playerActionsPrev[4] == 'X' && playerActionsPrev[5] == '>' || playerActionsPrev[4] == '^' && playerActionsPrev[5] == '_' || playerActionsPrev[4] == 'B' && playerActionsPrev[5] == 'B') return 3;
                else if (playerActionsPrev[2] == 'B' && playerActionsPrev[3] == 'B' && playerActionsPrev[4] == '_' && playerActionsPrev[5] == '_') {
                    *lastMove = 1;
                    return 1;
                }
                else {
                    if (random <= botPos * 10 + 10) return 6;
                    else {
                        int newRand = chance();
                        if (newRand <= 70) return 3;
                        else if (newRand <= 85) return 0;
                        else if (newRand <= 95) return 4;
                        else return 1;
                    }
                }
            }
            else if (botActionsCurr[2] == ' ') {
                if (*lastMove == -1) {
                    if (botActionsCurr[0] == 'X' && botActionsCurr[1] == '_') return 3;
                    else {
                        if (playerActionsPrev[4] == 'B' && playerActionsPrev[5] == 'B') {
                            if (random <= 25) return 1;
                            else if (random <= 50) return 2;
                            else if (random <= 75) return 3;
                            else {
                                *lastMove = 6;
                                return 6;
                            }
                        }
                        else if (playerActionsPrev[4] == '-' && playerActionsPrev[5] == 'X' || playerActionsPrev[4] == 'X' && playerActionsPrev[5] == '>' || playerActionsPrev[4] == '^' && playerActionsPrev[5] == '_') {
                            if (random <= botPos * 10 + 10) {
                                *lastMove = 6;
                                return 6;
                            }
                            else {
                                int newRand = chance();
                                if (newRand <= 75) return 3;
                                else if (newRand <= 90) return 1;
                                else if (newRand <= 95) return 4;
                                else return 0;
                            }
                        }
                    }
                }
                if (*lastMove == 6) {
                    *lastMove = 7;
                    return 7;
                }
            }
            else if (botActionsCurr[4] == ' ') {
                if (*lastMove == -1) {
                    if (botPos != 9) return 6;
                }
                else if (*lastMove == 1 || *lastMove == 7) return 3;
                else {
                    if (random <= botPos * 10 + 10) return 6;
                }
                return rand() % 7;
            }
            break;
        case 2:
            if (botActionsCurr[0] == ' ') {
                if (playerActionsPrev[2] == '-' && playerActionsPrev[3] == '-' && playerActionsPrev[4] == '-' && playerActionsPrev[5] == 'X') {
                    *lastMove = 73;
                    return 7;
                }
                else if (playerActionsPrev[2] == 'B' && playerActionsPrev[3] == 'B' && playerActionsPrev[4] == '_' && playerActionsPrev[5] == '_' || playerActionsPrev[4] == 'B' && playerActionsPrev[5] == 'B' || playerActionsPrev[4] == '-' && playerActionsPrev[5] == 'X' || playerActionsPrev[4] == 'X' && playerActionsPrev[5] == '>' || playerActionsPrev[4] == '^' && playerActionsPrev[5] == '_') {
                    int newRand = chance();
                    if (newRand <= 40) {
                        *lastMove = 732;
                        return 7;
                    }
                    else if (newRand <= 70) return 2;
                    else {
                        *lastMove = 5;
                        return 5;
                    }
                }
                else if (playerActionsPrev[4] == '-' && playerActionsPrev[5] == '-') {
                    int newRand = chance();
                    if (newRand <= 60) {
                        *lastMove = 73;
                        return 7;
                    }
                    else {
                        *lastMove = 5;
                        return 5;
                    }
                }
                else {
                    if (random <= 40) {
                        if (playerPos == 1) return 4;
                        else {
                            int newRand = chance();
                            if (newRand <= 80) return 0;
                            else return 2;
                        }
                    }
                    else if (random <= 75) {
                        if (botPos < 8) {
                            *lastMove = 6;
                            return 6;
                        }
                        else return 0;
                    }
                    else {
                        if (random <= 50) {
                            *lastMove = 7;
                            return 7;
                        }
                        else {
                            *lastMove = 5;
                            return 5;
                        }
                    }
                }
            }
            else if (botActionsCurr[2] == ' ') {
                switch (*lastMove) {
                    case -1:
                        if (random <= 70) {
                            if (botPos != 9) return 6;
                        }
                        else if (random <= 80) return 1;
                        else if (random <= 95) return 3;
                        else return 2;
                        break;
                    case 5:
                        *lastMove = 7;
                        return 7;
                        break;
                    case 6:
                        if (random <= 30) {
                            if (botPos != 9) {
                                *lastMove = 6;
                                return 6;
                            }
                            else {
                                *lastMove = 5;
                                return 5;
                            }
                        }
                        else {
                            *lastMove = 5;
                            return 5;
                        }
                        break;
                    case 7:
                        if (random <= 75) return 1;
                        else if (random <= 85) return 2;
                        else return 3;
                        break;
                    case 73:
                        return 3;
                        break;
                    default:
                        if (random <= 65) return 3;
                        else return 2;
                        break;
                }
            }
            else if (botActionsCurr[4] == ' ') {
                if (*lastMove == -1) {
                    if (botPos != 9) return 6;
                    else return rand() % 7;
                }
                else if (*lastMove == 5) return 7;
                else if (*lastMove == 6) return 5;
                else return 3;
            }
            break;
        case 3:
            if (*lastMove == -1) {
                if (random <= 60) return 2;
                else if (random <= 70) {
                    int newRand = chance();
                    if (newRand > botPos * 10 + 10) {
                        *lastMove = 6;
                        return 6;
                    }
                    else return 2;
                }
                else if (random <= 80) {
                    *lastMove == 5;
                    return 5;
                }
                else {
                    *lastMove = 7;
                    return 7;
                }
            }
            else if (*lastMove == 5) {
                if (rand() % 2 == 0) return 1;
                else return 0;
            }
            else if (*lastMove == 6) {
                int newRand = chance();
                if (newRand > botPos * 10 + 30) return 6;
                else {
                    *lastMove = 65;
                    return 5;
                }
            }
            else if (*lastMove == 7) {
                int newRand = chance();
                if (newRand <= 80) return 3;
                else if (newRand <= 90) return 1;
                else {
                    int newRand2 = chance();
                    if (newRand2 > botPos * 10 + 10) {
                        *lastMove = 6;
                        return 6;
                    }
                    else return 3;
                }
            }
            else if (*lastMove == 65) return 7;
            break;
        case 4:
            if (*lastMove == -1) {
                if (random <= botPos * 10 + 10 && botPos > 5) {
                    *lastMove = 7;
                    return 7;
                }
                else {
                    *lastMove = 6;
                    return 6;
                }
            }
            else if (*lastMove == 7) {
                if (random <= 35) return 0;
                else if (random <= 70) return 3;
                else {
                    *lastMove = 77;
                    return 7;
                }
            }
            else if (*lastMove == 77) {
                if (random <= 45) return 2;
                else if (random <= 90) return 3;
            }
            break;
        default:
            break;
    }
    return 3;
}

void botTurn(char* botActionsPrev, char* botActionsCurr, char* botActionsNext, char* playerActionsPrev, int playerPos, int botPos) {
    int i;
    char* actionsPrev = botActionsPrev;
    char* actionsCurr = botActionsCurr;
    char* actionsNext = botActionsNext;
    int actionsUsed = initActionUsed(actionsNext);
    memcpy(actionsPrev, actionsCurr, sizeof(actionsCurr));
    memcpy(actionsCurr, actionsNext, sizeof(actionsNext));
    initActionArrays(actionsNext);
    int lastMove = -1;
    while (actionsUsed < 6) {
        int move = botMove(&lastMove, botActionsCurr, playerActionsPrev, playerPos, botPos);
        for (i = 0; i < moveCosts[move]; i++) {
            if (actionsUsed < 6) actionsCurr[actionsUsed] = moveIcons[move][i];
            else actionsNext[actionsUsed - 6] = moveIcons[move][i];
            actionsUsed++;
        }
    }
    printf("Bot chosen move:\n");
    printf("  Actions last turn  |   Actions this turn  |  Actions next turn:\n");
    printActionArrays(actionsPrev);
    printf(" | ");
    printActionArrays(actionsCurr);
    printf(" | ");
    printUnknownActionArrays();
    printf("\n\n");
}