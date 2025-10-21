#include "board.h"
#include <stdio.h>

static void set_initial_positions(GameState *gs) {
    gs->p1_pieces = 0ULL;
    gs->p1_kings = 0ULL;
    gs->p2_pieces = 0ULL;
    gs->p2_kings = 0ULL;

    for (int r = 0; r <= 2; ++r) {
        for (int c = 0; c < 8; ++c) {
            if ((r + c) % 2 == 1) {
                int pos = r * 8 + c;
                gs->p2_pieces = SetBit(gs->p2_pieces, pos);
            }
        }
    }
    for (int r = 5; r <= 7; ++r) {
        for (int c = 0; c < 8; ++c) {
            if ((r + c) % 2 == 1) {
                int pos = r * 8 + c;
                gs->p1_pieces = SetBit(gs->p1_pieces, pos);
            }
        }
    }
    gs->current_player = 1;
}

void InitGame(GameState *gs) {
    set_initial_positions(gs);
}

int IsValidSquare(int pos) {
    if (pos < 0 || pos >= 64) return 0;
    int r = pos / 8, c = pos % 8;
    return ((r + c) % 2) == 1;
}

int IsOccupied(const GameState *gs, int pos) {
    U64 all = gs->p1_pieces | gs->p1_kings | gs->p2_pieces | gs->p2_kings;
    return GetBit(all, pos);
}

int IsKing(const GameState *gs, int player, int pos) {
    if (player == 1) return GetBit(gs->p1_kings, pos);
    else return GetBit(gs->p2_kings, pos);
}

void PrintBoard(const GameState *gs) {
    putchar('\n');
    printf("    0 1 2 3 4 5 6 7  (col)\n");
    printf("   -----------------\n");
    for (int r = 0; r < 8; ++r) {
        printf("%d | ", r);
        for (int c = 0; c < 8; ++c) {
            int pos = r * 8 + c;
            char ch = '.';
            if (IsOccupied(gs, pos)) {
                if (GetBit(gs->p1_pieces, pos)) ch = 'r'; /* red */
                else if (GetBit(gs->p1_kings, pos)) ch = 'R';
                else if (GetBit(gs->p2_pieces, pos)) ch = 'b'; /* black */
                else if (GetBit(gs->p2_kings, pos)) ch = 'B';
            } else {
                /* keep '.' for empty */
                ch = '.';
            }
            printf("%c ", ch);
        }
        printf("\n");
    }
    printf("\n");
    printf("Current player: %s (%d)\n", gs->current_player == 1 ? "Red" : "Black", gs->current_player);
    printf("Legend: r=red, R=red-king, b=black, B=black-king\n");
}