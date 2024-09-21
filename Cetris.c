#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>

#include "vector2.h"
#include "pieces.h"
#include "LinkedList.h"

#define ROWS 21
#define COLUMNS 13
#define TIC_RATE 0.25f
#define NEXT_PREVIEW_ROWS 5
#define NEXT_PREVIEW_COLS 5

int initialize(char board[ROWS][COLUMNS], char nextPreview[NEXT_PREVIEW_ROWS][NEXT_PREVIEW_COLS]);
int initializeBoard(char board[ROWS][COLUMNS]);
int initializeRow(char row[COLUMNS]);
int initializeNextPreview(char nextPreview[NEXT_PREVIEW_ROWS][NEXT_PREVIEW_COLS]);
int updateNextPreview(char nextPreview[NEXT_PREVIEW_ROWS][NEXT_PREVIEW_COLS], Piece piece);
int drawBoard(char board[ROWS][COLUMNS], char nextPreview[NEXT_PREVIEW_ROWS][NEXT_PREVIEW_COLS], int score);
bool movePiece(char board[ROWS][COLUMNS], Piece* piece, Vector2 movementVector);
bool canMove(char board[ROWS][COLUMNS], Piece piece, Vector2 movementVector);
bool rotatePiece(char board[ROWS][COLUMNS], Piece* piece, int rotationDirection);
bool canRotate(char board[ROWS][COLUMNS], Piece piece, int rotationDirection);
int rotate(Piece* piece, int rotationDirection);
bool canSpawnPiece(char board[ROWS][COLUMNS], Piece piece);
bool isPositionTaken(char board[ROWS][COLUMNS], Vector2 targetPosition);
int scorePoints(char board[ROWS][COLUMNS]);
bool isFullLine(char line[COLUMNS]);

int main() {
    LinkedList pieceOrder = createLinkedList();
    for(int i = 0; i < 7; i++) {
        addNodeByValue(&pieceOrder, i);
    }

    char board[ROWS][COLUMNS];
    char nextPreview[NEXT_PREVIEW_ROWS][NEXT_PREVIEW_COLS];
    int score = 0;
    Vector2 blockSpawnPoint;
    blockSpawnPoint.x = (COLUMNS - 2) / 2;
    blockSpawnPoint.y = 1;
    bool spawnedBlock = false;

    const Vector2 down = {0, 1};
    int playerInput;
    Vector2 inputDirection;
    int inputRotation;
    Vector2 zero = {0, 0};
    Node* nextIndex;

    Piece nextPiece;
    Piece currentPiece;

    initialize(board, nextPreview);

    nextIndex = getNextNode(&pieceOrder);
    if(nextIndex == NULL) {
        destroyLinkedList(&pieceOrder);
        fprintf(stderr, "Failed to get node from linked list.\n");
        return -1;
    }
    nextPiece = pieces[nextIndex->value];

    while(1) {
        //printf("\e[1;1H\e[2J"); //Clear screen;
        
        //Spawn piece
        if(!spawnedBlock) {
            currentPiece = nextPiece;
            nextIndex = getNextNode(&pieceOrder);
            if(nextIndex == NULL) {
                shuffleList(&pieceOrder);
                nextIndex = getNextNode(&pieceOrder);
                if(nextIndex == NULL) {
                    fprintf(stderr, "Failed to get node midgame.\n");
                    destroyLinkedList(&pieceOrder);
                    return -1;
                }
            }
            nextPiece = pieces[nextIndex->value];
            updateNextPreview(nextPreview, nextPiece);
            currentPiece.center = blockSpawnPoint;
            if(!canSpawnPiece(board, currentPiece)) {
                drawBoard(board, nextPreview, score);
                break;
            }
            for(int i = 0; i < 4; i++) {
                board[currentPiece.center.y + currentPiece.squares[i].y][currentPiece.center.x + currentPiece.squares[i].x] = 'X';
            }
            spawnedBlock = true;
        }
        
        else {
            
            //Player Input
            inputRotation = 0;
            inputDirection = zero;
            if(kbhit()) {
                playerInput = getch();
                if(playerInput == 'q')
                    inputRotation = -1;
                else if(playerInput == 'e')
                    inputRotation = 1;
                else if(playerInput == 'a')
                    inputDirection.x = -1;
                else if(playerInput == 'd')
                    inputDirection.x = 1;
                rotatePiece(board, &currentPiece, inputRotation);
                movePiece(board, &currentPiece, inputDirection);
            }

            //Move piece down.
            if(!movePiece(board, &currentPiece, down)) { //Piece cannot be moved down.
                for(int i = 0; i < 4; i++) {
                    board[currentPiece.center.y + currentPiece.squares[i].y][currentPiece.center.x + currentPiece.squares[i].x] = 'Z';
                }
                score += scorePoints(board);
                spawnedBlock = false;
            }
        }
        drawBoard(board, nextPreview, score);
        Sleep(TIC_RATE * 1000);
    }

    destroyLinkedList(&pieceOrder);
    return 0;
}

int initialize(char board[ROWS][COLUMNS], char nextPreview[NEXT_PREVIEW_ROWS][NEXT_PREVIEW_COLS]) {
    initializeBoard(board);
    initializeNextPreview(nextPreview);
    initializePieces();
    return 0;
}

int initializeBoard(char board[ROWS][COLUMNS]) {
    for(int i = 0; i < ROWS; i++) {
        if(i < ROWS - 1) {                      //Regular Rows
            initializeRow(board[i]);
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

int initializeRow(char row[COLUMNS]) {
    for(int j = 0; j < COLUMNS; j++) {
        if(j == 0 || j == COLUMNS - 2)
            row[j] = '|';
        else if(j == COLUMNS - 1)
            row[j] = '\0';
        else
            row[j] = ' ';
    }
    return 0;
}

int initializeNextPreview(char nextPreview[NEXT_PREVIEW_ROWS][NEXT_PREVIEW_COLS]) {
    for(int i = 0; i < NEXT_PREVIEW_ROWS; i++) {
        for(int j = 0; j < NEXT_PREVIEW_COLS - 1; j++) {
            nextPreview[i][j] = '-';
        }
        nextPreview[i][NEXT_PREVIEW_COLS - 1] = '\0';
    }
    return 0;
}

int updateNextPreview(char nextPreview[NEXT_PREVIEW_ROWS][NEXT_PREVIEW_COLS], Piece piece) {
    initializeNextPreview(nextPreview);
    for(int i = 0; i < 4; i++) {
        nextPreview[2 + piece.squares[i].y][1 + piece.squares[i].x] = 'X';
    }
    return 0;
}

int drawBoard(char board[ROWS][COLUMNS], char nextPreview[NEXT_PREVIEW_ROWS][NEXT_PREVIEW_COLS], int score) {
    int nextPreviewRow = 0;
    for(int i = 0; i < ROWS; i++) {
        printf("%s", board[i]);
        if(i == 0) {
            printf("%6s", " ");
            printf("Next: |%s|", nextPreview[nextPreviewRow]);
            nextPreviewRow++;
        }
        if(i >= 1 && i <= 3) {
            printf("%12s", " ");
            printf("|%s|", nextPreview[nextPreviewRow]);
            nextPreviewRow++;
        }
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
    Vector2 targetPosition;
    for(int i = 0; i < 4; i++) {
        targetPosition.x = piece.center.x + piece.squares[i].x + movementVector.x;
        targetPosition.y = piece.center.y + piece.squares[i].y + movementVector.y;
        if(isPositionTaken(board, targetPosition))
            return false;
    }
    return true;
}

bool rotatePiece(char board[ROWS][COLUMNS], Piece* piece, int rotationDirection) {
    if(rotationDirection == 0) //No rotation.
        return true;
    
    if(piece->pieceType == O) //The O piece doesn't rotate.
        return true;
    
    if(canRotate(board, *piece, rotationDirection)) {
        for(int i = 0; i < 4; i++) {
            board[piece->center.y + piece->squares[i].y][piece->center.x + piece->squares[i].x] = ' ';
        }
        
        rotate(piece, rotationDirection);

        for(int i = 0; i < 4; i++) {
            board[piece->center.y + piece->squares[i].y][piece->center.x + piece->squares[i].x] = 'X';
        }
        return true;
    }
    return false;
}

bool canRotate(char board[ROWS][COLUMNS], Piece piece, int rotationDirection) {
    if(rotationDirection == 0) //If you're not going to rotate, why are your calling this?
        return false;

    rotate(&piece, rotationDirection);
    
    Vector2 targetPosition;
    for(int i = 0; i < 4; i++) {
        targetPosition.x = piece.center.x + piece.squares[i].x;
        targetPosition.y = piece.center.y + piece.squares[i].y;
        if(isPositionTaken(board, targetPosition))
            return false;
    }
    return true;
}

int rotate(Piece* piece, int rotationDirection) {
    if(rotationDirection == 0) //No rotation.
        return -1;
    
    if(piece->pieceType == O) //The O piece doesn't rotate.
        return 0;
    
    if(rotationDirection > 0) {
        for(int i = 0; i < 4; i++) {
            int temp = piece->squares[i].x;
            piece->squares[i].x = piece->squares[i].y * -1;
            piece->squares[i].y = temp;
        }
    }
    else {
        for(int i = 0; i < 4; i++) {
            int temp = piece->squares[i].x;
            piece->squares[i].x = piece->squares[i].y;
            piece->squares[i].y = temp * -1;
        }
    }
    return 0;
}

bool canSpawnPiece(char board[ROWS][COLUMNS], Piece piece) {
    Vector2 targetPosition;
    for(int i = 0; i < 4; i++) {
        targetPosition.x = piece.center.x + piece.squares[i].x;
        targetPosition.y = piece.center.y + piece.squares[i].y;
        if(isPositionTaken(board, targetPosition))
            return false;
    }
    return true;
}

bool isPositionTaken(char board[ROWS][COLUMNS], Vector2 targetPosition) {
    if(board[targetPosition.y][targetPosition.x] != ' ') {
        if(board[targetPosition.y][targetPosition.x] != 'X')
            return true;   
    }
    return false;
}

int scorePoints(char board[ROWS][COLUMNS]) {
    int sequentialLines = 0;
    int maxSequentialLines = 0;
    for(int i = 0; i < ROWS - 1; i++) {
        if(isFullLine(board[i])) {
            sequentialLines++;
            if(sequentialLines > maxSequentialLines)
                maxSequentialLines = sequentialLines;
        }
        else 
            sequentialLines = 0;
    }

    switch(maxSequentialLines) {
        case 1:
            return 100;
        case 2:
            return 300;
        case 3:
            return 500;
        case 4:
            return 800;
        default:
            return 0;
    }
}

bool isFullLine(char line[COLUMNS]) {
    for(int i = 0; i < COLUMNS; i++) {
        if(line[i] == '|' || line[i] == '\\' || line[i] == '/' || line[i] == '-') //Ignore borders.
            continue;
        if(line[i] == ' ')
            return false;
    }
    return true;
}