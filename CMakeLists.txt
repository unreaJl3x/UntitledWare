cmake_minimum_required(VERSION 3.28)
project(UntitledWare)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(wssrc)

include_directories("C:\\directSDK\\Include")
link_directories("C:\\directSDK\\Lib\\x86")

add_executable(${PROJECT_NAME} main.cpp
        #           wssrc folder
        wssrc/app.h                 # Application date (HEADER)
        wssrc/app.cpp               # Application date
        #wssrc/FileSystem.h          # Interactive with filesystem (HEADER)
        #wssrc/FileSystem.cpp        # Interactive with filesystem
        wssrc/output.h              # Print text functions (HEADER)
        wssrc/output.cpp            # Print text fusnctions
        wssrc/ProcessManager.h      # Interactive with memory space (HEADER)
        wssrc/ProcessManager.cpp    # Interactive with memory space

        #           csgo folder
        csgo/AppCS.cpp
        csgo/AppCS.h
        csgo/CBasePlayer/CBasePlayer.h          # Interpretation CSGO class (HEADER)
        csgo/CBasePlayer/CBasePlayer.cpp        # Interpretation CSGO class
        csgo/hazedumper.h      # Hazedump (HEADER)

        #       csgo/functions folder
        csgo/CBasePlayer/CBasePlayerBuilder.cpp
        csgo/CBasePlayer/CBasePlayerBuilder.h
        tests/SimpleESP.cpp
        tests/SimpleESP.h
        tests/FovChanger.h
        dx_interface/dxOverlay.cpp
        dx_interface/dxOverlay.h
        dx_interface/dxRender.cpp
        dx_interface/dxRender.h
        wssrc/MenuController.cpp
        wssrc/MenuController.h
        wssrc/ConfController.cpp
        wssrc/ConfController.h
        wssrc/map_and_keys.h
        wssrc/WRECT.h

)

target_link_libraries(${PROJECT_NAME} PRIVATE
        d3dx9.lib d3d9.lib dwmapi.lib
)