cmake_minimum_required(VERSION 3.29)
project(UntitledWare)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

include_directories(wssrc)

add_executable(${PROJECT_NAME} main.cpp

        wssrc/output.cpp
        wssrc/output.h

        wssrc/app.cpp
        wssrc/app.h
)
