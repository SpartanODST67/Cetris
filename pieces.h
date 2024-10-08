#ifndef PIECES_H
#define PIECES_H

#include "vector2.h"

typedef enum PieceType { O, L, RL, Z, S, I, T} PieceType;

typedef struct Piece {
    Vector2 center;
    Vector2 squares[4];
    PieceType pieceType;
} Piece;

Piece oPiece;
Piece lPiece;
Piece rLPiece;
Piece tPiece;
Piece zPiece;
Piece sPiece;
Piece iPiece;
Piece pieces[7];

void initializePieces();
void initializeO();
void initializeL();
void initializeRL();
void initializeT();
void initializeZ();
void initializeS();
void initializeI();

#endif