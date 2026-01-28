cmake_minimum_required(VERSION 3.15)
project(ImGui_Lua)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LUA_DIR ${CMAKE_SOURCE_DIR}/deps/lua)

add_library(lua STATIC
        ${LUA_DIR}/lapi.c
        ${LUA_DIR}/lcode.c
        ${LUA_DIR}/lctype.c
        ${LUA_DIR}/ldebug.c
        ${LUA_DIR}/ldo.c
        ${LUA_DIR}/ldump.c
        ${LUA_DIR}/lfunc.c
        ${LUA_DIR}/lgc.c
        ${LUA_DIR}/llex.c
        ${LUA_DIR}/lmem.c
        ${LUA_DIR}/lobject.c
        ${LUA_DIR}/lopcodes.c
        ${LUA_DIR}/lparser.c
        ${LUA_DIR}/lstate.c
        ${LUA_DIR}/lstring.c
        ${LUA_DIR}/ltable.c
        ${LUA_DIR}/ltm.c
        ${LUA_DIR}/lundump.c
        ${LUA_DIR}/lvm.c
        ${LUA_DIR}/lzio.c

        ${LUA_DIR}/lauxlib.c
        ${LUA_DIR}/lbaselib.c
        ${LUA_DIR}/lcorolib.c
        ${LUA_DIR}/ldblib.c
        ${LUA_DIR}/liolib.c
        ${LUA_DIR}/lmathlib.c
        ${LUA_DIR}/loslib.c
        ${LUA_DIR}/lstrlib.c
        ${LUA_DIR}/ltablib.c
        ${LUA_DIR}/lutf8lib.c
        ${LUA_DIR}/loadlib.c
        ${LUA_DIR}/linit.c
)

target_include_directories(lua PUBLIC
        ${LUA_DIR}
)

find_package(OpenGL REQUIRED)

find_package(glfw3 QUIET)
if(NOT glfw3_FOUND)
    include(FetchContent)

    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw.git
            GIT_TAG 3.4
            GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(glfw)
endif()

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/deps/imgui)

set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
        src/env/renderer/renderer.cpp
)


add_executable(ImGui_Lua
        src/main.cpp
        src/env/renderer/renderer.hpp
        src/ImGuiWrapper/ImGuiWrapper.cpp


        src/env/wrapper.hpp
        src/env/main/main.hpp
        src/env/main/main.cpp
        src/env/wrapper.cpp
        src/env/flags/flags.cpp
        src/env/style/style.h
        src/env/style/style.cpp
        src/env/font/font.h
        src/env/font/font.cpp

        ${IMGUI_SOURCES}
)

target_include_directories(ImGui_Lua PUBLIC
        ${LUA_DIR}
        ${IMGUI_DIR}
        ${CMAKE_SOURCE_DIR}
        ${IMGUI_DIR}/backends
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(ImGui_Lua PRIVATE
        lua
        OpenGL::GL
        glfw
)

if(APPLE)
    target_link_libraries(ImGui_Lua PRIVATE
            "-framework CoreFoundation"
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreVideo"
    )
elseif(UNIX AND NOT APPLE)
    target_link_libraries(ImGui_Lua PRIVATE
            dl
            m
            pthread
            X11
            Xrandr
            Xi
            Xxf86vm
            Xcursor
            Xinerama
    )
elseif(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++ -pthread")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++ -pthread")

    target_link_libraries(ImGui_Lua PRIVATE
            opengl32
            gdi32
    )
endif()
