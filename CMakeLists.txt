cmake_minimum_required(VERSION 3.29)
project(UntitledWare)

set(CMAKE_CXX_STANDARD 20)



include_directories(.)
include_directories(csgo)
include_directories(unreaJl3x)

add_executable(${PROJECT_NAME} main.cpp
        hack.cpp
        hack.h
        unreaJl3x/Proc.cpp
        unreaJl3x/Proc.h
        unreaJl3x/mem.h
        csgo/csgo_signatures.h
        csgo/game.h
        csgo/game.cpp
        unreaJl3x/globals.h
        unreaJl3x/globals.cpp
        unreaJl3x/output.h
        unreaJl3x/output.cpp
)
