#ifndef PIECES_H
#define PIECES_H

#include "vector2.h"

typedef struct Piece {
    Vector2 center;
    Vector2 squares[4];
} Piece;

Piece oPiece;
Piece lPiece;
Piece reverseLPiece;
Piece zPiece;
Piece sPiece;
Piece iPiece;

#endif