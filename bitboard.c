#include "bitboard.h"
#include <stdio.h>

U64 SetBit(U64 value, int position) {
    if (position < 0 || position >= 64) return value;
    return value | (1ULL << position);
}

U64 ClearBit(U64 value, int position) {
    if (position < 0 || position >= 64) return value;
    return value & ~(1ULL << position);
}

U64 ToggleBit(U64 value, int position) {
    if (position < 0 || position >= 64) return value;
    return value ^ (1ULL << position);
}

int GetBit(U64 value, int position) {
    if (position < 0 || position >= 64) return 0;
    return (int)((value >> position) & 1ULL);
}

int CountBits(U64 value) {
    return __builtin_popcountll(value);
}

U64 ShiftLeft(U64 value, int positions) {
    if (positions <= 0) return value;
    if (positions >= 64) return 0ULL;
    return value << positions;
}

U64 ShiftRight(U64 value, int positions) {
    if (positions <= 0) return value;
    if (positions >= 64) return 0ULL;
    return value >> positions;
}

void PrintBinaryU64(U64 value) {
    for (int r = 7; r >= 0; --r) {
        for (int c = 7; c >= 0; --c) {
            int pos = r * 8 + c;
            putchar(GetBit(value, pos) ? '1' : '0');
        }
        putchar('\n');
    }
}

void PrintHexU64(U64 value) {
    printf("0x%016llx\n", (unsigned long long)value);
}