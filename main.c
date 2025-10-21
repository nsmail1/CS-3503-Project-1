#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "game.h"

int main(void) {
    GameState gs;
    InitGame(&gs);

    printf("BitBoard Checkers (simple 2-player)\n");
    printf("Moves are entered as: from to   (e.g. `12 16`)\n");
    printf("Squares are 0..63 (row*8 + col). Dark squares are playable.\n");
    printf("Type 'q' or EOF (Ctrl+D/Ctrl+Z) to quit.\n");

    while (1) {
        PrintBoard(&gs);
        int winner = CheckWinner(&gs);
        if (winner != 0) {
            printf("Game over! Winner: %s\n", winner == 1 ? "Red (Player 1)" : "Black (Player 2)");
            break;
        }

        printf("Player %d (%s) enter move: ", gs.current_player, gs.current_player == 1 ? "Red" : "Black");
        char line[128];
        if (!fgets(line, sizeof(line), stdin)) {
            printf("\nInput ended. Exiting.\n");
            break;
        }
        char *p = line;
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == 'q' || *p == 'Q') {
            printf("Quitting.\n");
            break;
        }
        int from, to;
        if (sscanf(p, "%d %d", &from, &to) != 2) {
            /* maybe comma */
            if (sscanf(p, "%d,%d", &from, &to) != 2) {
                printf("Invalid input. Use: from to  (e.g. 12 16)\n");
                continue;
            }
        }
        if (!IsValidSquare(from) || !IsValidSquare(to)) {
            printf("Invalid squares: both must be dark playable squares between 0 and 63.\n");
            continue;
        }
        int ok = ApplyMove(&gs, from, to);
        if (ok == 1) {
            continue;
        } else if (ok == 0) {
            printf("Illegal move. Try again.\n");
            continue;
        } else {
            printf("Input/quit error.\n");
            break;
        }
    }

    return 0;
}