#include <stdio.h>

#include "main.h"

void initActionArrays(char* actionArray) {
    int i;
    for (i = 0; i < 6; i++) {
        actionArray[i] = ' ';
    }
}

void initAllActionArrays(char* playerActionsPrev, char* playerActionsCurr, char* playerActionsNext, char* botActionsPrev, char* botActionsCurr, char* botActionsNext) {
    initActionArrays(playerActionsPrev);
    initActionArrays(playerActionsCurr);
    initActionArrays(playerActionsNext);
    initActionArrays(botActionsPrev);
    initActionArrays(botActionsCurr);
    initActionArrays(botActionsNext);
}

int initActionUsed(char* actionsNext) {
    int actionsUsed = 0;
    int i;
    for (i = 0; i < 6; i++) {
        if (actionsNext[i] != ' ') actionsUsed++;
        else break;
    }
    return actionsUsed;
}

void printActionArrays(char* actionArray) {
    int i;
    for (i = 0; i < 6; i++) {
        if (i != 0 && i % 2 == 0) printf(" ");
        printf("[%c]", actionArray[i]);
    }
}

void printUnknownActionArrays() {
    int i;
    for (i = 0; i < 6; i++) {
        if (i != 0 && i % 2 == 0) printf(" ");
        printf("[?]");
    }
}

void announceGameState(char* playerActionsPrev, char* playerActionsCurr, char* playerActionsNext, char* botActionsPrev, char* botActionsCurr, char* botActionsNext, int playerPos, int botPos, int playerScore, int botScore, int gamemode) {
    int i;
    int adjacent = (playerPos != botPos - 1) ? 0 : 1;
    if (gamemode == 0) printf("Score:\nP : B\n%d : %d\n\n", playerScore, botScore);
    else printf("Score:\nP1 : P2\n%d  : %d\n\n", playerScore, botScore);
    printf("Piste:\n");
    for (i = 0; i < 10; i++) {
        char c;
        if (i == playerPos) {
            if (gamemode == 0) c = 'P';
            else c = '1';
        }
        else if (i == botPos) {
            if (gamemode == 0) c = 'B';
            else c = '2';
        }
        else c = ' ';
        printf("[%c] ", c);
    }
    printf("\n\n");
    if (gamemode == 0) printf("Player vs Bot actions:\n");
    else printf("Player 1 vs Player 2 actions:\n");
    printf("  Actions last turn  |   Actions this turn  |  Actions next turn:\n");
    printActionArrays(playerActionsPrev);
    printf(" | ");
    printActionArrays(playerActionsCurr);
    printf(" | ");
    if (gamemode == 1) printUnknownActionArrays();
    else printActionArrays(playerActionsNext);
    printf("\n");
    printActionArrays(botActionsPrev);
    printf(" | ");
    printActionArrays(botActionsCurr);
    printf(" | ");
    printUnknownActionArrays();
    printf("\n\n");
}

char ifXX(char* playerActionsPrev, char* playerActionsCurr, char* botActionsPrev, char* botActionsCurr, int index) {
    index--;
    while (index >= 0) {
        if (playerActionsCurr[index] == '-' && botActionsCurr[index] == '-') index--;
        else if (playerActionsCurr[index] == '-' && botActionsCurr[index] != '-') return 'p';
        else if (playerActionsCurr[index] != '-' && botActionsCurr[index] == '-') return 'b';
        else return 'a';
    }
    index = 5;
    while (index >= 0) {
        if (playerActionsPrev[index] == '-' && botActionsPrev[index] == '-') index--;
        else if (playerActionsPrev[index] == '-' && botActionsPrev[index] != '-') return 'p';
        else if (playerActionsPrev[index] != '-' && botActionsPrev[index] == '-') return 'b';
        else return 'a';
    }
}

int ifX(char defender) {
    if (defender != 'B') return 1;
    else return 0;
}

int ifDollarSign(char* opponentActionsPrev, char* opponentActionsCurr, int index) {
    int counter = 0;
    while (index >= 0) {
        if (counter > 3) return 0;
        if (opponentActionsCurr[index] == '^' || opponentActionsCurr[index] == '>') return 1;
        else index--;
        counter++;
    }
    index = 5;
    while (index >= 0) {
        if (counter > 3) return 0;
        if (opponentActionsCurr[index] == '^' || opponentActionsCurr[index] == '>') return 1;
        else index--;
        counter++;
    }
}

int compareResults(char* playerActionsPrev, char* playerActionsCurr, char* botActionsPrev, char* botActionsCurr, int* playerPos, int* botPos, int* playerScore, int* botScore) {
    int scored = 0;
    int i;
    for (i = 0; i < 6; i++) {
        int distance = *botPos - *playerPos;
        char priority = 'a';
        if (playerActionsCurr[i] == '<') --*playerPos;
        else if (botActionsCurr[i] == '<') ++*botPos;
        distance = *botPos - *playerPos;
        if (playerActionsCurr[i] == 'X' && botActionsCurr[i] == 'X') {
            priority = ifXX(playerActionsPrev, playerActionsCurr, botActionsPrev, botActionsCurr, i);
            if (distance == 1) {
                if (priority == 'p') ++*playerScore;
                else if (priority == 'b') ++*botScore;
                else {
                    ++*playerScore;
                    ++*botScore;
                }
                scored = 1;
                break;
            }
        }
        else if (playerActionsCurr[i] == 'X') {
            if (distance == 1) {
                int j = ifX(botActionsCurr[i]);
                if (j == 1) {
                    ++*playerScore;
                    scored = 1;
                    break;
                }
            }
        }
        else if (botActionsCurr[i] == 'X') {
            if (distance == 1) {
                int j = ifX(playerActionsCurr[i]);
                if (j == 1) {
                    ++*botScore;
                    scored = 1;
                    break;
                }
            }
        }
        if (playerActionsCurr[i] == '^' && botActionsCurr[i] == '^') {
            if (distance <= 6) {
                *playerPos = *playerPos + ((distance - 1) / 2);
                *botPos = *botPos - ((distance - 1) / 2);
                if (distance % 2 == 0) {
                    if (priority == 'p') ++*playerPos;
                    else if (priority == 'b') --*botPos;
                }
            }
            else {
                *playerPos = *playerPos + 3;
                *botPos = *botPos - 3;
            }
        }
        else if (playerActionsCurr[i] == '^') {
            if (distance <= 3) {
                *playerPos = *playerPos + 3;
                *botPos = *botPos + (3 - distance + 1);
            }
            else *playerPos = *playerPos + 3;
        }
        else if (botActionsCurr[i] == '^') {
            if (distance <= 3) {
                *botPos = *botPos - 3;
                *playerPos = *playerPos - (3 - distance + 1);
            }
            else *botPos = *botPos - 3;
        }
        else {
            if (playerActionsCurr[i] == '>' && botActionsCurr[i] == '>') {
                if (distance == 1 && i > 0) {
                    if (playerActionsCurr[i-1] == 'X' && botActionsCurr[i-1] == 'X') {
                        if (priority == 'p') {
                            ++*playerPos;
                            ++*botPos;
                        }
                        else if (priority == 'b') {
                            --*botPos;
                            --*playerPos;
                        }
                    }
                    else if (playerActionsCurr[i-1] == 'X') {
                        ++*playerPos;
                        ++*botPos;
                    }
                    else if (botActionsCurr[i-1] == 'X') {
                        --*botPos;
                        --*playerPos;
                    }
                }
                else if (distance == 1 && i == 0) {
                    if (playerActionsPrev[5] == 'X' && botActionsPrev[5] == 'X') {
                        if (priority == 'p') {
                            ++*playerPos;
                            ++*botPos;
                        }
                        else if (priority == 'b') {
                            --*botPos;
                            --*playerPos;
                        }
                    }
                    else if (playerActionsPrev[5] == 'X') {
                        ++*playerPos;
                        ++*botPos;
                    }
                    else if (botActionsPrev[5] == 'X') {
                        --*botPos;
                        --*playerPos;
                    }
                }
                else if (distance == 2 && i > 0) {
                    if (playerActionsCurr[i-1] == 'X' && botActionsCurr[i-1] == 'X') {
                        if (priority == 'p') ++*playerPos;
                        else if (priority == 'b') --*botPos;
                    }
                    else if (playerActionsCurr[i-1] == 'X') ++*playerPos;
                    else if (botActionsCurr[i-1] == 'X') --*botPos;
                }
                else if (distance == 2 && i == 0) {
                    if (playerActionsPrev[i-1] == 'X' && botActionsPrev[i-1] == 'X') {
                        if (priority == 'p') ++*playerPos;
                        else if (priority == 'b') --*botPos;
                    }
                    else if (playerActionsPrev[i-1] == 'X') ++*playerPos;
                    else if (botActionsPrev[i-1] == 'X') --*botPos;
                }
                else if (distance > 2) {
                    *playerPos = *playerPos + 1;
                    *botPos = *botPos - 1;
                }
            }
            else if (playerActionsCurr[i] == '>') {
                if (distance == 1 && i > 0) {
                    if (playerActionsCurr[i-1] == 'X') {
                        ++*playerPos;
                        ++*botPos;
                    }
                }
                else if (distance == 1 && i == 0) {
                    if (playerActionsPrev[5] == 'X') {
                        ++*playerPos;
                        ++*botPos;
                    }
                }
                else if (distance > 1) ++*playerPos;
            }
            else if (botActionsCurr[i] == '>') {
                if (distance == 1 && i > 0) {
                    if (botActionsCurr[i-1] == 'X') {
                        --*botPos;
                        --*playerPos;
                    }
                }
                else if (distance == 1 && i == 0) {
                    if (botActionsPrev[5] == 'X') {
                        --*botPos;
                        --*playerPos;
                    }
                }
                else if (distance > 1) --*botPos;
            }
        }
        if (playerActionsCurr[i] == '$') {
            if (distance == 1) {
                int j = ifDollarSign(botActionsPrev, botActionsCurr, i);
                if (j == 1) ++*botPos;
            }
        }
        else if (botActionsCurr[i] == '$') {
            if (distance == 1) {
                int j = ifDollarSign(playerActionsPrev, playerActionsCurr, i);
                if (j == 1) --*playerPos;
            }
        }
        if (*playerPos < 0) {
            ++*botScore;
            scored = -1;
            break;
        }
        else if (*botPos > 9) {
            ++*playerScore;
            scored = -2;
            break;
        }
    }
    return scored;
}