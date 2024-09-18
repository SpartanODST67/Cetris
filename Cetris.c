#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include <stdbool.h>

#include "vector2.h"
#include "pieces.h"

#define ROWS 21
#define COLUMNS 13
#define TIC_RATE 0.25f

int initialize(char board[ROWS][COLUMNS]);
int initializeBoard(char board[ROWS][COLUMNS]);
int drawBoard(char board[ROWS][COLUMNS], int score);
bool movePiece(char board[ROWS][COLUMNS], Piece* piece, Vector2 movementVector);
bool canMove(char board[ROWS][COLUMNS], Piece piece, Vector2 movementVector);

int main() {
    char board[ROWS][COLUMNS];
    int score = 0;
    Vector2 blockSpawnPoint;
    blockSpawnPoint.x = (COLUMNS - 2) / 2;
    blockSpawnPoint.y = 1;
    bool spawnedBlock = false;

    const Vector2 down = {0, 1};
    int directionInput;
    Vector2 inputDirection;
    Vector2 zero = {0, 0};
    Piece currentPiece;

    initialize(board);

    while(1) {
        //printf("\e[1;1H\e[2J"); //Clear screen;
        inputDirection = zero;
        if(!spawnedBlock) {
            currentPiece = zPiece;
            currentPiece.center = blockSpawnPoint;
            for(int i = 0; i < 4; i++) {
                board[currentPiece.center.y + currentPiece.squares[i].y][currentPiece.center.x + currentPiece.squares[i].x] = 'X';
            }
            spawnedBlock = true;
        }
        else {
            
            //Move Piece left and right.
            directionInput = getchar();
            if(directionInput == 'a')
                inputDirection.x = -1;
            else if(directionInput == 'd')
                inputDirection.x = 1;
            movePiece(board, &currentPiece, inputDirection);

            //Move piece down.
            if(!movePiece(board, &currentPiece, down)) {
                for(int i = 0; i < 4; i++) {
                    board[currentPiece.center.y + currentPiece.squares[i].y][currentPiece.center.x + currentPiece.squares[i].x] = 'Z';
                }
                spawnedBlock = false;
            }
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

bool movePiece(char board[ROWS][COLUMNS], Piece* piece, Vector2 movementVector) {
    if(canMove(board, *piece, movementVector)) {
        for(int i = 0; i < 4; i++) {
            board[piece->center.y + piece->squares[i].y][piece->center.x + piece->squares[i].x] = ' ';
        }
        piece->center.x += movementVector.x;
        piece->center.y += movementVector.y;
        for(int i = 0; i < 4; i++) {
            board[piece->center.y + piece->squares[i].y][piece->center.x + piece->squares[i].x] = 'X';
        }
        return true;
    }
    return false;
}

bool canMove(char board[ROWS][COLUMNS], Piece piece, Vector2 movementVector) {
    for(int i = 0; i < 4; i++) {
        if(board[piece.center.y + piece.squares[i].y + movementVector.y][piece.center.x + piece.squares[i].x + movementVector.x] != ' ') {
            if(board[piece.center.y + piece.squares[i].y + movementVector.y][piece.center.x + piece.squares[i].x + movementVector.x] != 'X')
                return false;   
        }
    }
    return true;
}