cmake_minimum_required(VERSION 3.30)
project(imgui_lib_lua)

set(CMAKE_CXX_STANDARD 20)

#######################################################################################################################
#######################################################################################################################
#######################################################################################################################
#######################################################################################################################


add_executable(
        imgui_lib_lua src/main.cpp

        dependencies/imgui/imgui.cpp
        dependencies/imgui/imgui_draw.cpp
        dependencies/imgui/imgui_tables.cpp
        dependencies/imgui/imgui_widgets.cpp
        dependencies/imgui/imgui_impl_win32.cpp
        dependencies/imgui/imgui_demo.cpp
        dependencies/imgui/imgui_impl_dx9.cpp
        src/env/renderer/renderer.cpp
        src/env/gui.h
        src/gui/gui.cpp
        src/env/style/style.cpp
        src/env/types/flags.cpp
        src/env/types/flags.h
        src/env/inclusions.h
        src/env/renderer/renderer.h
        src/env/main/ui.cpp
        src/env/main/ui.h
        src/env/style/style.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
)


#######################################################################################################################
#######################################################################################################################
#######################################################################################################################
#######################################################################################################################


target_include_directories(
        ${PROJECT_NAME} PRIVATE
        ${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui"
        ${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lua/includes"
)

#######################################################################################################################
#######################################################################################################################
#######################################################################################################################
#######################################################################################################################


add_library(lua_static STATIC
        dependencies/lua/core/state/lapi.c
        dependencies/lua/parser/lcode.c
        dependencies/lua/parser/lctype.c
        dependencies/lua/core/debug/ldebug.c
        dependencies/lua/core/vm/ldo.c
        dependencies/lua/core/io/ldump.c
        dependencies/lua/core/objects/lfunc.c
        dependencies/lua/core/memory/lgc.c
        dependencies/lua/parser/llex.c
        dependencies/lua/core/memory/lmem.c
        dependencies/lua/core/objects/lobject.c
        dependencies/lua/parser/lopcodes.c
        dependencies/lua/parser/lparser.c
        dependencies/lua/core/state/lstate.c
        dependencies/lua/lib/lstring.c
        dependencies/lua/lib/ltable.c
        dependencies/lua/core/objects/ltm.c
        dependencies/lua/core/io/lundump.c
        dependencies/lua/core/vm/lvm.c
        dependencies/lua/core/io/lzio.c
        dependencies/lua/includes/lauxlib.c
        dependencies/lua/lib/lbaselib.c
        dependencies/lua/lib/lcorolib.c
        dependencies/lua/lib/ldblib.c
        dependencies/lua/lib/liolib.c
        dependencies/lua/lib/lmathlib.c
        dependencies/lua/lib/loadlib.c
        dependencies/lua/lib/loslib.c
        dependencies/lua/lib/lstrlib.c
        dependencies/lua/lib/ltablib.c
        dependencies/lua/lib/lutf8lib.c
        dependencies/lua/lib/linit.c
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        lua_static
        d3d9
)

#######################################################################################################################
#######################################################################################################################
#######################################################################################################################
#######################################################################################################################
