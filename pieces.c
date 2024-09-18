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
    oPiece.center.x = 0;
    oPiece.center.y = 0;

    oPiece.squares[0].x = 0;
    oPiece.squares[0].y = 0;

    oPiece.squares[1].x = 0;
    oPiece.squares[1].y = -1;

    oPiece.squares[2].x = 1;
    oPiece.squares[2].y = 0;

    oPiece.squares[3].x = 1;
    oPiece.squares[3].y = -1;

    oPiece.pieceType = O;
}

void initializeL() {
    lPiece.center.x = 0;
    lPiece.center.y = 0;

    lPiece.squares[0].x = -1;
    lPiece.squares[0].y = 0;

    lPiece.squares[1].x = -1;
    lPiece.squares[1].y = -1;

    lPiece.squares[2].x = 0;
    lPiece.squares[2].y = -1;

    lPiece.squares[3].x = 1;
    lPiece.squares[3].y = -1;

    lPiece.pieceType = L;
}

void initializeRL() {
    rLPiece.center.x = 0;
    rLPiece.center.y = 0;

    rLPiece.squares[0].x = -1;
    rLPiece.squares[0].y = -1;

    rLPiece.squares[1].x = 0;
    rLPiece.squares[1].y = -1;

    rLPiece.squares[2].x = 1;
    rLPiece.squares[2].y = -1;

    rLPiece.squares[3].x = 1;
    rLPiece.squares[3].y = 0;

    rLPiece.pieceType = RL;
}

void initializeT() {
    tPiece.center.x = 0;
    tPiece.center.y = 0;

    tPiece.squares[0].x = 0;
    tPiece.squares[0].y = 0;

    tPiece.squares[1].x = -1;
    tPiece.squares[1].y = 0;

    tPiece.squares[2].x = 1;
    tPiece.squares[2].y = 0;

    tPiece.squares[3].x = 0;
    tPiece.squares[3].y = -1;

    tPiece.pieceType = T;
}

void initializeZ() {
    zPiece.center.x = 0;
    zPiece.center.y = 0;

    zPiece.squares[0].x = -1;
    zPiece.squares[0].y = -1;

    zPiece.squares[1].x = 0;
    zPiece.squares[1].y = -1;

    zPiece.squares[2].x = 0;
    zPiece.squares[2].y = 0;

    zPiece.squares[3].x = 1;
    zPiece.squares[3].y = 0;

    zPiece.pieceType = Z;
}

void initializeS() {
    sPiece.center.x = 0;
    sPiece.center.y = 0;

    sPiece.squares[0].x = -1;
    sPiece.squares[0].y = 0;

    sPiece.squares[1].x = 0;
    sPiece.squares[1].y = 0;

    sPiece.squares[2].x = 0;
    sPiece.squares[2].y = -1;

    sPiece.squares[3].x = 1;
    sPiece.squares[3].y = -1;

    sPiece.pieceType = S;
}

void initializeI() {
    iPiece.center.x = 0;
    iPiece.center.y = 0;

    iPiece.squares[0].x = -2;
    iPiece.squares[0].y = -1;

    iPiece.squares[1].x = -1;
    iPiece.squares[1].y = -1;

    iPiece.squares[2].x = 0;
    iPiece.squares[2].y = -1;

    iPiece.squares[3].x = 1;
    iPiece.squares[3].y = -1;

    iPiece.pieceType = I;
}