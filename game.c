#include "game.h"
#include <stdio.h>
#include <stdlib.h>

static inline int row_of(int pos) { return pos / 8; }
static inline int col_of(int pos) { return pos % 8; }

static void remove_piece_at(GameState *gs, int player, int pos) {
    if (player == 1) {
        gs->p1_pieces = ClearBit(gs->p1_pieces, pos);
        gs->p1_kings = ClearBit(gs->p1_kings, pos);
    } else {
        gs->p2_pieces = ClearBit(gs->p2_pieces, pos);
        gs->p2_kings = ClearBit(gs->p2_kings, pos);
    }
}

static void place_piece_at(GameState *gs, int player, int pos, int king) {
    if (player == 1) {
        gs->p1_pieces = ClearBit(gs->p1_pieces, pos);
        gs->p1_kings = ClearBit(gs->p1_kings, pos);
        if (king) gs->p1_kings = SetBit(gs->p1_kings, pos);
        else gs->p1_pieces = SetBit(gs->p1_pieces, pos);
    } else {
        gs->p2_pieces = ClearBit(gs->p2_pieces, pos);
        gs->p2_kings = ClearBit(gs->p2_kings, pos);
        if (king) gs->p2_kings = SetBit(gs->p2_kings, pos);
        else gs->p2_pieces = SetBit(gs->p2_pieces, pos);
    }
}

static int belongs_to_player(const GameState *gs, int player, int pos) {
    if (player == 1) {
        return GetBit(gs->p1_pieces, pos) || GetBit(gs->p1_kings, pos);
    } else {
        return GetBit(gs->p2_pieces, pos) || GetBit(gs->p2_kings, pos);
    }
}

static int is_forward_move(int player, int from, int to) {
    int dr = row_of(to) - row_of(from);
    if (player == 1) return dr < 0;
    else return dr > 0;
}

static int is_king_piece(const GameState *gs, int player, int pos) {
    return IsKing(gs, player, pos);
}

int ApplyMove(GameState *gs, int from, int to) {
    if (from < 0 || from >= 64 || to < 0 || to >= 64) return 0;
    if (!IsValidSquare(from) || !IsValidSquare(to)) return 0;
    if (!belongs_to_player(gs, gs->current_player, from)) return 0;
    if (IsOccupied(gs, to)) return 0;
    int dr = row_of(to) - row_of(from);
    int dc = col_of(to) - col_of(from);
    int absdr = dr < 0 ? -dr : dr;
    int absdc = dc < 0 ? -dc : dc;

    int player = gs->current_player;
    int king = is_king_piece(gs, player, from);

    if (absdr == 1 && absdc == 1) {
        if (!king && !is_forward_move(player, from, to)) return 0; /* cannot move backwards if not king */
        remove_piece_at(gs, player, from);
        int promote = 0;
        if (!king) {
            if (player == 1 && row_of(to) == 0) promote = 1;
            if (player == 2 && row_of(to) == 7) promote = 1;
        }
        place_piece_at(gs, player, to, king || promote);
        gs->current_player = (player == 1) ? 2 : 1;
        return 1;
    }

    if (absdr == 2 && absdc == 2) {
        int midr = (row_of(from) + row_of(to)) / 2;
        int midc = (col_of(from) + col_of(to)) / 2;
        int midpos = midr * 8 + midc;
        int opp = (player == 1) ? 2 : 1;
        if (!belongs_to_player(gs, opp, midpos)) return 0;
        if (!king && !is_forward_move(player, from, to)) return 0; /* non-king cannot capture backwards in our simple rules */
        remove_piece_at(gs, opp, midpos);
        remove_piece_at(gs, player, from);
        int promote = 0;
        if (!king) {
            if (player == 1 && row_of(to) == 0) promote = 1;
            if (player == 2 && row_of(to) == 7) promote = 1;
        }
        place_piece_at(gs, player, to, king || promote);
        gs->current_player = (player == 1) ? 2 : 1;
        return 1;
    }

    return 0;
}

int HasAnyMoves(const GameState *gs, int player) {
    for (int pos = 0; pos < 64; ++pos) {
        if (!IsValidSquare(pos)) continue;
        if (!belongs_to_player(gs, player, pos)) continue;
        int king = is_king_piece(gs, player, pos);
        int dirs[4][2] = { {1,1},{1,-1},{-1,1},{-1,-1} };
        for (int d = 0; d < 4; ++d) {
            int dr = dirs[d][0], dc = dirs[d][1];
            int nr = row_of(pos) + dr, nc = col_of(pos) + dc;
            int npos = nr*8 + nc;
            if (nr >= 0 && nr < 8 && nc >= 0 && nc < 8 && IsValidSquare(npos)) {
                if (!IsOccupied(gs, npos)) {
                    if (king || (player == 1 ? dr < 0 : dr > 0)) return 1;
                } else {
                    int orr = nr + dr, occ = nc + dc;
                    int tpos = orr*8 + occ;
                    if (orr >= 0 && orr < 8 && occ >= 0 && occ < 8 && IsValidSquare(tpos) && !IsOccupied(gs, tpos)) {
                        int opp = (player == 1) ? 2 : 1;
                        if (belongs_to_player(gs, opp, npos)) {
                            if (king || (player == 1 ? dr < 0 : dr > 0)) return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int CheckWinner(const GameState *gs) {
    int p1_count = CountBits(gs->p1_pieces) + CountBits(gs->p1_kings);
    int p2_count = CountBits(gs->p2_pieces) + CountBits(gs->p2_kings);
    if (p2_count == 0) return 1;
    if (p1_count == 0) return 2;
    if (!HasAnyMoves(gs, 1)) return 2;
    if (!HasAnyMoves(gs, 2)) return 1;
    return 0;
}