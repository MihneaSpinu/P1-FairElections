cmake_minimum_required(VERSION 3.29)
project(P1_Projekt C)

set(CMAKE_C_STANDARD 11)

add_executable(P1_Projekt main.c
        ranked.c
        rated.c
        FPTP.c
        initialisering.c
        functions.h
)
