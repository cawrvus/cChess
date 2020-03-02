#include <stdio.h>

#include "constants.h"

#include "ascii.h"
#include "piece.h"

static const char *_B_PAWN[] = {EMPTY_ASCII, " ()  ", " )(  ", "/__\\ "};
static const char *_W_PAWN[] = {EMPTY_ASCII, " ()  ", " )(  ", "/##\\ "};
static const char *_B_KNIGHT[] = {"_,, ", "\"-=\\~", " ) ( ", "/___\\"};
static const char *_W_KNIGHT[] = {"_,,  ", "\"-=\\~", " ) ( ", "/###\\"};
static const char *_B_BISHOP[] = {"  ,  ", " (v) ", " ) ( ", "/___\\"};
static const char *_W_BISHOP[] = {"  ,  ", " (v) ", " ) ( ", "/###\\"};
static const char *_B_ROOK[] = {EMPTY_ASCII, " [-] ", " ) ( ", "/___\\"};
static const char *_W_ROOK[] = {EMPTY_ASCII, " [-] ", " ) ( ", "/###\\"};
static const char *_B_QUEEN[] = {EMPTY_ASCII, " \\^/ ", " ) ( ", "/___\\"};
static const char *_W_QUEEN[] = {EMPTY_ASCII, " \\^/ ", " ) ( ", "/###\\"};
static const char *_B_KING[] = {EMPTY_ASCII, " \\+/ ", " ) ( ", "/___\\"};
static const char *_W_KING[] = {EMPTY_ASCII, " \\+/ ", " ) ( ", "/###\\"};
static const char *_EMPTY[] = {[0 ... 3] = EMPTY_ASCII};

const char **get_ascii(Type t, Color c) {
    const char **ascii;
    switch (t) {
        case Pawn:
            if (c == Black) ascii = _B_PAWN;
            else if (c == White) ascii = _W_PAWN;
            break;
        case Knight:
            if (c == Black) ascii = _B_KNIGHT;
            else if (c == White) ascii = _W_KNIGHT;
            break;
        case Bishop:
            if (c == Black) ascii = _B_BISHOP;
            else if (c == White) ascii = _W_BISHOP;
            break;
        case Rook:
            if (c == Black) ascii = _B_ROOK;
            else if (c == White) ascii = _W_ROOK;
            break;
        case Queen:
            if (c == Black) ascii = _B_QUEEN;
            else if (c == White) ascii = _W_QUEEN;
            break;
        case King:
            if (c == Black) ascii = _B_KING;
            else if (c == White) ascii = _W_KING;
            break;
        default:
            ascii = _EMPTY;
            break;
    }

    return ascii;
}
