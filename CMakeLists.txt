cmake_minimum_required(VERSION 3.29)
project(UntitledWare)

set(CMAKE_GENERATOR_PLATFORM Win32)
set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(csgo)
include_directories(unreaJl3x)

add_executable(CheatCsgoExternal main.cpp
        hack.cpp
        hack.h
        unreaJl3x/Proc.cpp
        unreaJl3x/Proc.h
        unreaJl3x/mem.cpp
        unreaJl3x/mem.h
        csgo/csgo_signatures.h
        csgo/functions/functions.h
        csgo/functions/bunnyhope.cpp
        csgo/functions/bunnyhope.h
        csgo/functions/local.cpp
        csgo/game.h
        csgo/game.cpp
        unreaJl3x/globals.h
        unreaJl3x/globals.cpp

)
