//
// Created by Nick on 10/19/2025.
//

#ifndef CS_3503_PROJECT_1_BITBOARD_H
#define CS_3503_PROJECT_1_BITBOARD_H


#include <stdint.h>

typedef unsigned long long U64;


U64 SetBit(U64 value, int position);
U64 ClearBit(U64 value, int position);
U64 ToggleBit(U64 value, int position);
int GetBit(U64 value, int position);


int CountBits(U64 value);


U64 ShiftLeft(U64 value, int positions);
U64 ShiftRight(U64 value, int positions);


void PrintBinaryU64(U64 value);
void PrintHexU64(U64 value);


#endif //CS_3503_PROJECT_1_BITBOARD_H