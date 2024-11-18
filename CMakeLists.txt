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
        GUI.cpp
        GUI.h

        csgo/csgo_signatures.h
        csgo/CBasePlayer.cpp
        csgo/CBasePlayer.h

        imgui/imconfig.h
        imgui/imgui.cpp
        imgui/imgui.h
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_impl_dx9.cpp
        imgui/imgui_impl_dx9.h
        imgui/imgui_impl_win32.cpp
        imgui/imgui_impl_win32.h
        imgui/imgui_internal.h
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imstb_rectpack.h
        imgui/imstb_textedit.h
        imgui/imstb_truetype.h
)
