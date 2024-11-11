cmake_minimum_required(VERSION 3.29)
project(UntitledWare)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(csgo)
include_directories(unreaJl3x)

add_executable(${PROJECT_NAME} main.cpp
        main.cpp
)
