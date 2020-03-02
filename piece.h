#ifndef PIECE_H
#define PIECE_H

#include <stdio.h>

#include "types.h"

typedef enum color {
    Black,
    White
} Color;

typedef enum type {
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
} Type;

typedef struct piece {
    Type type;
    Color color;
    Tile *tile;
} Piece;

Piece **construct_pieces(Tile ***board, FILE *config);
void project(Piece *p, Tile ***board, _Bool alt);
void destruct_pieces(Piece **pieces);
void move(Piece *p, Tile *t, Tile ***board, Piece **pieces);

#endif /* PIECE_H */
