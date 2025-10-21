cmake_minimum_required(VERSION 4.0)
project(CS_3503_Project_1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(CS_3503_Project_1
        bitboard.c
        bitboard.h
        board.c
        board.h
        game.c
        game.h
        main.c)
