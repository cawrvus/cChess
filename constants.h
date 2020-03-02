#ifndef CONSTANTS_H
#define CONSTANTS_H

// Board dimension
#define SIZE 8
// Maximum of attacks on one tile
#define MAX_ATTACK 12
// Maximum range of pieces
#define MAX_RANGE SIZE
// Minimum range of pieces
#define MIN_RANGE 1
// Pawn notation
#define PAWN 'p'
// Knight notation
#define KNIGHT 'n'
// Bishop notation
#define BISHOP 'b'
// Rook notation
#define ROOK 'r'
// Queen notation
#define QUEEN 'q'
// King notation
#define KING 'k'
// Zero notation
#define EMPTY '!'
// Total number of pieces on board
#define PIECE_COUNT 32
// Number of piece types
#define TYPE_COUNT 6
// Determine if dimensions are in bounds
#define IS_IN_BOUNDS(d1, d2) (d1 >= 0 && d1 < SIZE && d2 >= 0 && d2 < SIZE)

#endif /* CONSTANTS_H */
