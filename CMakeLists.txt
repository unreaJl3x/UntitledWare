cmake_minimum_required(VERSION 3.29)
project(UntitledWare)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(imgui)
include_directories(csgo)
include_directories(wssrc)

add_executable(${PROJECT_NAME} main.cpp
        #CSGOCheatFuncsStarter.h     # Entry point cheat functions (HEADER)
        #CSGOCheatFuncsStarter.cpp   # Entry point cheat functions
        #GUI.h                       # IMGUI (HEADER)
        #GUI.cpp                     # IMGUI

        #           wssrc folder
        wssrc/app.h                 # Application date (HEADER)
        wssrc/app.cpp               # Application date
        #wssrc/ConfigSys.h           # Settings for game function (HEADER)
        #wssrc/ConfigSys.cpp         # Settings for game function
        #wssrc/decomple.h            # Key decomple algorithm (HEADER)
        #wssrc/decomple.cpp          # Key decomple algorithm (HEADER)
        wssrc/FileSystem.h          # Interactive with filesystem (HEADER)
        wssrc/FileSystem.cpp        # Interactive with filesystem
        wssrc/output.h              # Print text functions (HEADER)
        wssrc/output.cpp            # Print text fusnctions
        wssrc/ProcessManager.h      # Interactive with memory space (HEADER)
  sssrc/ProcessManager.cpp    # Interactive with memory space
        #wssrc/Secure.h              # Checking valid app license (HEADER)
        #wssrc/Secure.cpp            # Checking valid app license

        #           csgo folder
        csgo/AppCS.cpp
        csgo/AppCS.h
        csgo/CBasePlayer.h          # Interpretation CSGO class (HEADER)
        csgo/CBasePlayer.cpp        # Interpretation CSGO class
        csgo/csgo_signatures.h      # Hazedump (HEADER)
        #csgo/globalDate.h           # Date for cheat function running in "thread" mode (HEADER)
        #csgo/globalDate.cpp         # Date for cheat function running in "thread" mode

        #       csgo/functions folder
        csgo/functions/RadarHack.h
        csgo/CBasePlayerBuilder.cpp
        csgo/CBasePlayerBuilder.h
        #RadarHack (HEADER)
)
