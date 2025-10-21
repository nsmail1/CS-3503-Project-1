//
// Created by Nick on 10/19/2025.
//

#ifndef CS_3503_PROJECT_1_GAME_H
#define CS_3503_PROJECT_1_GAME_H

#include "board.h"


int ApplyMove(GameState *gs, int from, int to);

int HasAnyMoves(const GameState *gs, int player);

int CheckWinner(const GameState *gs);

#endif //CS_3503_PROJECT_1_GAME_H