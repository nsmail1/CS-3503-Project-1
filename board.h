//
// Created by Nick on 10/19/2025.
//

#ifndef CS_3503_PROJECT_1_BOARD_H
#define CS_3503_PROJECT_1_BOARD_H

#include "bitboard.h"

typedef struct {
    U64 p1_pieces;   /* player 1 regular pieces (red) */
    U64 p1_kings;    /* player 1 kings */
    U64 p2_pieces;   /* player 2 regular pieces (black) */
    U64 p2_kings;    /* player 2 kings */
    int current_player; /* 1 or 2 */
} GameState;

void InitGame(GameState *gs);

void PrintBoard(const GameState *gs);

int IsOccupied(const GameState *gs, int pos);
int IsValidSquare(int pos); /* dark squares only */
int IsKing(const GameState *gs, int player, int pos);

#endif //CS_3503_PROJECT_1_BOARD_H