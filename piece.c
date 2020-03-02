#include <stdlib.h>
#include <stdio.h>

#include "constants.h"

#include "piece.h"
#include "board.h"
#include "utils.h"

/*
 * definition of basic movement vectors of the pieces
 */

static int _PAWN_MOVESET[][2] = {
    {0, 1}
};
static int _PAWN_ALT_MOVESET[][2] = {
    {-1, 1},
    {1, 1}
};
static int _KNIGHT_MOVESET[][2] = {
    {-1, 2},
    {1, 2},
    {2, 1},
    {2, -1},
    {1, -2},
    {-1, -2},
    {-2, -1},
    {-2, 1}
};
static int _BISHOP_MOVESET[][2] = {
    {-1, 1},
    {1, 1},
    {1, -1},
    {-1, -1}
};
static int _ROOK_MOVESET[][2] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}
};
static int _QUEEN_MOVESET[8][2] = {
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1},
    {0, -1},
    {-1, -1},
    {-1, 0}
};
static int _KING_MOVESET[][2] = {
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1},
    {0, -1},
    {-1, -1},
    {-1, 0}
};

static int _MOVE_COUNTS[][2] = {
    {1, 2},
    {8, 8},
    {4, 4},
    {4, 4},
    {8, 8},
    {8, 8}
};

static move_t *get_moveset(Type t, _Bool alt);
static int get_range(Type t);
static _Bool is_checked(Color c, Tile ***board);
static _Bool validate(Piece *p, Tile *t, Tile ***board);
static Type get_type(char type);

const Piece *KINGS[2];

void move(Piece *p, Tile *t, Tile ***board, Piece **pieces) {
    if (!p) goto final;

    Piece *end_p = t->piece;
    p->tile->piece = NULL;
    p->tile = t;
    t->piece = p;
    if (end_p) end_p->tile = NULL;
    refresh_board(board, pieces, PIECE_COUNT);

final:
    return;
}

Piece **construct_pieces(Tile ***board, FILE *config) {
    Piece **pieces = new_mem(sizeof (Piece *), PIECE_COUNT, (_Bool) 1);
    int cursor = 0;
    for (int i = 0; i < SIZE; i += 1) {
        for (int j = 0; j < SIZE; j += 1) {
            char type;
            char color;
            fscanf(config, "%c%c ", &color, &type);
            if (type == EMPTY) continue;

            Piece *p = new_mem(sizeof (Piece), 1, (_Bool) 0);
            p->type = get_type(type);
            p->color = atoi(&color);
            p->tile = board[i][j];

            if (p->type == King && p->color == Black)
                KINGS[Black] = p;
            if (p->type == King && p->color == White)
                KINGS[White] = p;

            board[i][j]->piece = p;
            pieces[cursor] = p;
            cursor += 1;
        }
    }
    return pieces;
}

void destruct_pieces(Piece **pieces) {
    for (int i = 0; i < PIECE_COUNT; i += 1) {
        free(pieces[i]);
    }
    free(pieces);
}

void project(Piece *p, Tile ***board, _Bool alt) {
    if (!p) goto final;
    int move_count = _MOVE_COUNTS[p->type][alt];
    move_t *moveset = get_moveset(p->type, alt);
    int range = get_range(p->type);

    for (int i = 0; i < move_count; i += 1) {
        int *move = moveset[i];

        int file = p->tile->file;
        int rank = p->tile->rank;
        while (IS_IN_BOUNDS(file + move[0], rank - move[1]) && range > 0) {
            file += move[0];
            rank -= move[1];
            range -= 1;

            Tile * t = board[rank][file];
            if (p->type == Pawn && !alt && t->piece)
                break;
            else if (!validate(p, t, board))
                break;
            else if (t->piece) {
                t->projections[t->proj_count] = p;
                t->proj_count += 1;
                break;
            } else {
                t->projections[t->proj_count] = p;
                t->proj_count += 1;
            }
        }
    }

final:
    return;
}

static _Bool validate(Piece *p, Tile *t, Tile ***board) {
    Tile *from = p->tile;
    Piece *capture = t->piece;

    from->piece = NULL;
    t->piece = p;

    _Bool is_valid = !is_checked(p->color, board);

    from->piece = p;
    t->piece = capture;

    return is_valid;
}

static _Bool is_checked(Color c, Tile ***board) {
    const Piece *king = KINGS[c];
    uint count = TYPE_COUNT - 1;

    _Bool is_checked = (_Bool) 0;
    for (uint i = 0; i < count; i += 1) {
        _Bool alt = i == Pawn;
        move_t *moveset = get_moveset(i, alt);
        int move_count = _MOVE_COUNTS[i][alt];
        int range = get_range(i);

        for (int j = 0; j < move_count; j += 1) {
            int *move = moveset[j];
            int rank = king->tile->rank;
            int file = king->tile->file;
            for (int k = 0; k < range; k += 1) {
                file += move[0];
                rank -= move[1];

                _Bool chk = IS_IN_BOUNDS(rank, file);
                Piece *p = chk ? board[rank][file]->piece
                        : NULL;

                if (!p)
                    continue;
                else if (p->type == i && p->color != c) {
                    is_checked = (_Bool) 1;
                    goto final;
                } else break;
            }
        }
    }

final:
    return is_checked;
}

static Type get_type(char type) {
    Type t;
    switch (type) {
        case PAWN:
            t = Pawn;
            break;
        case KNIGHT:
            t = Knight;
            break;
        case BISHOP:
            t = Bishop;
            break;
        case ROOK:
            t = Rook;
            break;
        case QUEEN:
            t = Queen;
            break;
        case KING:
            t = King;
            break;
        default:
            fprintf(stderr, "could not determine piece type");
            exit(1);
            break;
    }

    return t;
}

static int get_range(Type t) {
    int range;
    switch (t) {
        case Pawn:
        case Knight:
        case King:
            range = MIN_RANGE;
            break;
        case Bishop:
        case Rook:
        case Queen:
            range = MAX_RANGE;
            break;
        default:
            fprintf(stderr, "could not determine piece type");
            exit(1);
            break;
    }

    return range;
}

static move_t *get_moveset(Type t, _Bool alt) {
    move_t *moveset;
    switch (t) {
        case Pawn:
            moveset = alt ? _PAWN_ALT_MOVESET
                    : _PAWN_MOVESET;
            break;
        case Knight:
            moveset = _KNIGHT_MOVESET;
            break;
        case Bishop:
            moveset = _BISHOP_MOVESET;
            break;
        case Rook:
            moveset = _ROOK_MOVESET;
            break;
        case Queen:
            moveset = _QUEEN_MOVESET;
            break;
        case King:
            moveset = _KING_MOVESET;
            break;
        default:
            fprintf(stderr, "could not determine piece type");
            exit(1);
            break;
    }

    return moveset;
}
