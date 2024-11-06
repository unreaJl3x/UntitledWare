cmake_minimum_required(VERSION 3.29)
project(UntitledWare)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(csgo)
include_directories(unreaJl3x)

add_executable(${PROJECT_NAME} main.cpp

        hack.cpp            # MAIN HACK LOOP

        unreaJl3x/Proc.cpp      # Inject by using Windows API
        unreaJl3x/Proc.h        # Inject by using Windows API (HEADER)
        unreaJl3x/mem.h         # Write\Read Process Memory (HEADER)
        csgo/game.h             # Victim app date
        csgo/game.cpp           # Victim app date (HEADER)
        unreaJl3x/globals.h     # Global variables (HEADER)
        unreaJl3x/globals.cpp   # Global variables
        unreaJl3x/output.h      # Print function (HEADER)
        unreaJl3x/output.cpp    # Print function (HEADER)

            # COUNTER-STRIKE: GLOBAL OFFENSIVE
        csgo/Player.h           # Local transfer CBasePlayer (HEADER)
        csgo/Player.cpp         # Local transfer CBasePlayer
        # Functions
        csgo/funcs.h
        csgo/funcs/RadarHack.h
        csgo/funcs/iFovChanger.h
        csgo/funcs/AntiFlash.h
)
