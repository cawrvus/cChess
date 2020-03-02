#include <stdlib.h>

#include "constants.h"

#include "board.h"
#include "piece.h"
#include "utils.h"

static void clean_board(Tile ***board);

Tile ***construct_board() {
    Tile ***board = new_mem(sizeof (Tile *), SIZE, (_Bool) 0);
    for (int i = 0; i < SIZE; i += 1) {
        board[i] = new_mem(sizeof (Tile *), SIZE, (_Bool) 0);
        for (int j = 0; j < SIZE; j += 1) {
            Tile *t = new_mem(sizeof (Tile), 1, (_Bool) 0);
            t->projections = new_mem(sizeof (Piece *), MAX_ATTACK, (_Bool) 0);
            t->rank = i;
            t->file = j;
            t->piece = NULL;
            board[i][j] = t;
        }
    }
    return board;
}

void destruct_board(Tile ***board) {
    for (int i = 0; i < SIZE; i += 1) {
        for (int j = 0; j < SIZE; j += 1) {
            Tile *t = board[i][j];
            free(t->projections);
            free(t);
        }
        free(board[i]);
    }
    free(board);
}

void refresh_board(Tile ***board, Piece **pieces, int piece_count) {
    clean_board(board);
    for (int i = 0; i < piece_count; i += 1) {
        Piece *p = pieces[i];
        if (!p) goto final;
        project(p, board, (_Bool) 0);
        if (p->type == PAWN)
            project(p, board, (_Bool) 1);
    }

final:
    return;
}

static void clean_board(Tile ***board) {
    for (int i = 0; i < SIZE; i += 1) {
        for (int j = 0; j < SIZE; j += 1) {
            board[i][j]->proj_count = 0;
            free(board[i][j]->projections);
            board[i][j]->projections = new_mem(sizeof (Piece *), MAX_ATTACK, (_Bool) 0);
        }
    }
}
