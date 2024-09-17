#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include <stdbool.h>

#include "vector2.h"
#include "pieces.h"

#define ROWS 21
#define COLUMNS 13
#define TIC_RATE 1/35

int initialize(char board[ROWS][COLUMNS]);
int initializeBoard(char board[ROWS][COLUMNS]);
int drawBoard(char board[ROWS][COLUMNS], int score);

int main() {
    char board[ROWS][COLUMNS];
    int score = 0;
    vector2 blockSpawnPoint;
    blockSpawnPoint.x = (COLUMNS - 2) / 2;
    blockSpawnPoint.y = 0;
    bool spawnedBlock = false;


    initialize(board);

    while(1) {
        //printf("\e[1;1H\e[2J"); //Clear screen;
        if(!spawnedBlock) {
            board[blockSpawnPoint.y][blockSpawnPoint.x] = 'X';
        }
        drawBoard(board, score);
        score++;
        Sleep(TIC_RATE * 1000);
    }

    return 0;
}

int initialize(char board[ROWS][COLUMNS]) {
    initializeBoard(board);
    return 0;
}

int initializeBoard(char board[ROWS][COLUMNS]) {
    for(int i = 0; i < ROWS; i++) {
        if(i < ROWS - 1) {                      //Regular Rows
            for(int j = 0; j < COLUMNS; j++) {
                if(j == 0 || j == COLUMNS - 2)
                    board[i][j] = '|';
                else if(j == COLUMNS - 1)
                    board[i][j] = '\0';
                else
                    board[i][j] = ' ';
            }
        }
        else {                                  //Bottom Row
            for(int k = 0; k < COLUMNS; k++) {
                if(k == 0)
                    board[i][k] = '\\';
                else if(k == COLUMNS - 2)
                    board[i][k] = '/';
                else if(k == COLUMNS - 1)
                    board[i][k] = '\0';
                else
                    board[i][k] = '-';
            }
        }
    }

    return 0;
}

int drawBoard(char board[ROWS][COLUMNS], int score) {
    for(int i = 0; i < ROWS; i++) {
        printf("%s", board[i]);
        if(i == 0)
            printf("%6s%s", " ", "Next: |----|");
        if(i >= 1 && i <= 3) 
            printf("%12s%s", " ", "|----|");
        if(i == 5)
            printf("%6s%s %d", " ", "Score:", score);
        printf("\n");
    }
}