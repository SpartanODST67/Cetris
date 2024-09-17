#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include <stdbool.h>

#include "vector2.h"
#include "pieces.h"

#define ROWS 21
#define COLUMNS 13
#define TIC_RATE 1

int initialize(char board[ROWS][COLUMNS]);
void initializePieces();
void initializeO();
void initializeL();
void initializeRL();
void initializeT();
void initializeZ();
void initializeS();
void initializeI();
int initializeBoard(char board[ROWS][COLUMNS]);
int drawBoard(char board[ROWS][COLUMNS], int score);
//bool movePiece(char board[ROWS][COLUMNS], Piece piece, Vector2 movementVector);
bool movePiece(char board[ROWS][COLUMNS], Vector2* piece);
//bool canMove(char board[ROWS][COLUMNS], Piece piece, Vector2 movementVector);
bool canMove(char board[ROWS][COLUMNS], Vector2 piece);

int main() {
    char board[ROWS][COLUMNS];
    int score = 0;
    Vector2 blockSpawnPoint;
    blockSpawnPoint.x = (COLUMNS - 2) / 2;
    blockSpawnPoint.y = 1;
    bool spawnedBlock = false;

    Vector2 tempBlock = blockSpawnPoint;

    initialize(board);

    while(1) {
        printf("\e[1;1H\e[2J"); //Clear screen;
        if(!spawnedBlock) {
            tempBlock = blockSpawnPoint;
            board[tempBlock.y][tempBlock.x] = 'X';
            spawnedBlock = true;
        }
        else {
            if(!movePiece(board, &tempBlock))
                spawnedBlock = false;
        }
        drawBoard(board, score);
        score++;
        Sleep(TIC_RATE * 1000);
    }

    return 0;
}

int initialize(char board[ROWS][COLUMNS]) {
    initializeBoard(board);
    initializePieces();
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

void initializePieces() {
    initializeO();
    initializeL();
    initializeRL();
    initializeT();
    initializeZ();
    initializeS();
    initializeI();
}

void initializeO() {
    oPiece.squares[0].x = 0;
    oPiece.squares[0].y = 0;

    oPiece.squares[1].x = 0;
    oPiece.squares[1].y = -1;

    oPiece.squares[2].x = 1;
    oPiece.squares[2].y = 0;

    oPiece.squares[3].x = 1;
    oPiece.squares[3].y = -1;
}

void initializeL() {
    lPiece.squares[0].x = -1;
    lPiece.squares[0].y = 0;

    lPiece.squares[1].x = -1;
    lPiece.squares[1].y = -1;

    lPiece.squares[2].x = 0;
    lPiece.squares[2].y = -1;

    lPiece.squares[3].x = 1;
    lPiece.squares[3].y = -1;
}

void initializeRL() {
    rLPiece.squares[0].x = -1;
    rLPiece.squares[0].y = -1;

    rLPiece.squares[1].x = 0;
    rLPiece.squares[1].y = -1;

    rLPiece.squares[2].x = 1;
    rLPiece.squares[2].y = -1;

    rLPiece.squares[3].x = 1;
    rLPiece.squares[3].y = 0;
}

void initializeT() {
    tPiece.squares[0].x = 0;
    tPiece.squares[0].y = 0;

    tPiece.squares[1].x = -1;
    tPiece.squares[1].y = 0;

    tPiece.squares[2].x = 1;
    tPiece.squares[2].y = 0;

    tPiece.squares[3].x = 0;
    tPiece.squares[3].y = -1;
}

void initializeZ() {
    zPiece.squares[0].x = -1;
    zPiece.squares[0].y = -1;

    zPiece.squares[1].x = 0;
    zPiece.squares[1].y = -1;

    zPiece.squares[2].x = 0;
    zPiece.squares[2].y = 0;

    zPiece.squares[3].x = 1;
    zPiece.squares[3].y = 0;
}

void initializeS() {
    sPiece.squares[0].x = -1;
    sPiece.squares[0].y = 0;

    sPiece.squares[1].x = 0;
    sPiece.squares[1].y = 0;

    sPiece.squares[2].x = 0;
    sPiece.squares[2].y = -1;

    sPiece.squares[3].x = 1;
    sPiece.squares[3].y = -1;
}

void initializeI() {
    iPiece.squares[0].x = -2;
    iPiece.squares[0].y = -1;

    iPiece.squares[1].x = -1;
    iPiece.squares[1].y = -1;

    iPiece.squares[2].x = 0;
    iPiece.squares[2].y = -1;

    iPiece.squares[3].x = 1;
    iPiece.squares[3].y = -1;
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

/*int movePiece(char board[ROWS][COLUMNS], Piece piece, Vector2 movementVector) {

}*/

//Only here for simple tests.
bool movePiece(char board[ROWS][COLUMNS], Vector2* piece) {
    if(canMove(board, *piece))
    {
        board[piece->y][piece->x] = ' ';
        piece->y = (piece->y) + 1;
        board[piece->y][piece->x] = 'X';
        return true;
    }
    return false;
}

/*bool canMove(char board[ROWS][COLUMNS], Piece piece, Vector2 movementVector) {

}*/

bool canMove(char board[ROWS][COLUMNS], Vector2 piece) {
    if(board[piece.y + 1][piece.x] != ' ')
        return false;
    return true;
}