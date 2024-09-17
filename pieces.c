#include "pieces.h"

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