#ifndef BOARD_H
#define BOARD_H

#include "types.h"

typedef enum file {
    _a, _b, _c, _d, _e, _f, _g, _h
} File;

typedef enum rank {
    _8, _7, _6, _5, _4, _3, _2, _1
} Rank;

typedef struct tile {
    Rank rank;
    File file;
    Piece *piece;
    Piece **projections;
    uint proj_count;
} Tile;

Tile ***construct_board();
void destruct_board(Tile ***board);
void refresh_board(Tile ***board, Piece **pieces, int piece_count);

#endif /* BOARD_H */
