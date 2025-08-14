//
// Created by sigma on 10/08/2025.
//


#include "renderer.h"
static int CreateHWindow(lua_State* L) {
    const char* windowName = luaL_checkstring(L, 1);
    auto windowWidth  = (float) luaL_optnumber(L, 2, gui::WIDTH);
    auto windowHeight = (float) luaL_optnumber(L, 2, gui::HEIGHT);

    gui::CreateHWindow(windowName, windowWidth, windowHeight);

    lua_pushboolean(L, gui::window == nullptr);
    return 1;
}

static int CreateDevice(lua_State* L) {
    gui::CreateDevice();

    lua_pushboolean(L, gui::device == nullptr);
    return 1;
}

static int CreateImGui(lua_State* L) {
    gui::CreateImGui();
    return 0;
}

static const luaL_Reg rendererFunctions[] = {
        {"CreateHWindow", CreateHWindow},
        {"CreateDevice", CreateDevice},
        {"CreateImGui", CreateImGui},

        {"DestroyImGui", [](lua_State* L) -> int {
            gui::DestroyImGui();
            return 0;
        }},
        {"DestroyDevice", [](lua_State* L) -> int {
            gui::DestroyDevice();
            return 0;
        }},
        {"DestroyHWindow", [](lua_State* L) -> int {
            gui::DestroyHWindow();
            return 0;
        }},
        {"BeginRender", [](lua_State* L) -> int {
            gui::BeginRender();
            return 0;
        }},
        {"EndRender", [](lua_State* L) -> int {
            gui::EndRender();
            return 0;
        }},
        {NULL, NULL}
};

void registerRenderer(lua_State* L) {
    luaL_newlib(L, rendererFunctions);
    lua_setglobal(L, "renderer");
    lua_pop(L, 1);
}