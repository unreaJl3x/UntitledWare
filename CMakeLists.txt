cmake_minimum_required(VERSION 3.29)
project(UntitledWare)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(imgui)
include_directories(csgo)
include_directories(wssrc)

add_executable(${PROJECT_NAME} main.cpp
        wssrc/app.cpp
        wssrc/app.h
        wssrc/FileSystem.cpp
        wssrc/FileSystem.h
        wssrc/output.cpp
        wssrc/output.h
        wssrc/ProcessManager.cpp
        wssrc/ProcessManager.h


        csgo/csgo_signatures.h
        csgo/functions/RadarHack.h
        csgo/globalDate.cpp
        csgo/globalDate.h
        wssrc/ConfigSys.cpp
        wssrc/ConfigSys.h
        wssrc/Secure.cpp
        wssrc/Secure.h
        wssrc/decomple.cpp
        hack.cpp
        hack.h
)
