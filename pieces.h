#ifndef PIECES_H
#define PIECES_H

#include "vector2.h"

typedef struct Piece {
    Vector2 center;
    Vector2 squares[4];
} Piece;

Piece O;
Piece L;
Piece reverseL;
Piece z;
Piece s;
Piece i;

#endif