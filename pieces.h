#ifndef PIECES_H
#define PIECES_H

#include "vector2.h"

typedef enum PieceType { O, L, RL, Z, S, I} PieceType;

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

#endif