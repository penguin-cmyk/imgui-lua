//
// Created by sigma on 10/08/2025.
//

#ifndef IMGUI_LIB_LUA_GUI_H
#define IMGUI_LIB_LUA_GUI_H

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
};

#include "../gui/gui.h"
#include "types/flags.h"
#include "renderer/renderer.h"
#include "style/style.h"

#include "main/ui.h"

void init(lua_State* L) {
    luaL_openlibs(L);

    registerFlags(L);
    registerRenderer(L);
    registerImgui(L);
    registerImGuiStyle(L);
}

#endif //IMGUI_LIB_LUA_GUI_H
