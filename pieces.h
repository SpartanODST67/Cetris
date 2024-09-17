#ifndef PIECES_H
#define PIECES_H

#include "vector2.h"

typedef struct piece {
    vector2 center;
    vector2 squares[4];
} piece;

piece O;
piece L;
piece reverseL;
piece z;
piece s;
piece i;

#endif