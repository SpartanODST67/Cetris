#include <stdio.h>
#include <strings.h>

#define ROWS 21
#define COLUMNS 13

int initialize(char board[ROWS][COLUMNS]);
int initializeBoard(char board[ROWS][COLUMNS]);
int drawBoard(char board[ROWS][COLUMNS]);

int main() {
    char board[ROWS][COLUMNS];
    int score = 0;

    initialize(board);

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