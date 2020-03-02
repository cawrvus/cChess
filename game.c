#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

#include "board.h"
#include "piece.h"
#include "game.h"
#include "ascii.h"

// TODO: better organize functions

static Piece **init_game(Tile ***board, const char *config_path);
///*static*/ void print_game(/*Tile ***board*/);
static void run_game();

void new_game(const char *config_path) {
    Tile ***board = construct_board();
    Piece **pieces = init_game(board, config_path);
    print_game(board);

    // run game
    run_game();

    // end game
    destruct_pieces(pieces);
    destruct_board(board);
}

static void run_game() {

}

void print_game(Tile ***board) {
    for (int i = 0; i < SIZE; i += 1) {
        printf(DIV_ASCII);
        for (int k = 0; k < ASCII_HEIGHT; k += 1) {
            for (int j = 0; j < SIZE; j += 1) {
                Piece *p = board[i][j]->piece;
                Type type = p ? p->type : (unsigned char) - 1;
                Color color = p ? p->color : (unsigned char) - 1;
                const char **ascii = get_ascii(type, color);

                printf("|");
                printf(PADDING_ASCII);
                printf(ascii[k]);
                printf(PADDING_ASCII);
            }
            printf("|");
            printf("\n");
        }
    }
    printf(DIV_ASCII);
}

static Piece **init_game(Tile ***board, const char *config_path) {
    FILE *config = fopen(config_path, "r");
    Piece **pieces = construct_pieces(board, config);
    fclose(config);

    refresh_board(board, pieces, PIECE_COUNT);

    return pieces;
}
