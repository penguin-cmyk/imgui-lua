//
// Created by sigma on 12/08/2025.
//

#ifndef IMGUI_LIB_LUA_STYLE_H
#define IMGUI_LIB_LUA_STYLE_H

#include "../inclusions.h"
#include <string>

#define LUA_WRAP(args_code, call_code, ret_code) \
    [](lua_State *L) -> int {                    \
        args_code;                               \
        call_code;                               \
        ret_code;                                \
    }

#define setfield(L, field_name, value, func) \
    func(L, value);                           \
    lua_setfield(L, -2, field_name);

#define LUA_RETURN_IMVEC2(L, res) \
    lua_newtable(L);              \
    setfield(L, "x", res.x, lua_pushnumber)  \
    setfield(L, "y", res.y, lua_pushnumber)  \
    return 1

#define LUA_RETURN_IMVEC4(L, res) \
    lua_newtable(L);              \
    setfield(L, "x", res.x, lua_pushnumber)  \
    setfield(L, "y", res.y, lua_pushnumber)  \
    setfield(L, "z", res.z, lua_pushnumber)  \
    setfield(L, "w", res.w, lua_pushnumber)  \
    return 1

#define LUA_GET_IMVEC2(L, idx, result) \
    lua_getfield(L, idx, "x"); result.x = (float)lua_tonumber(L, -1); lua_pop(L, 1); \
    lua_getfield(L, idx, "y"); result.y = (float)lua_tonumber(L, -1); lua_pop(L, 1);

#define LUA_GET_IMVEC4(L, idx, result) \
    lua_getfield(L, idx, "x"); result.x = (float)lua_tonumber(L, -1); lua_pop(L, 1); \
    lua_getfield(L, idx, "y"); result.y = (float)lua_tonumber(L, -1); lua_pop(L, 1); \
    lua_getfield(L, idx, "z"); result.z = (float)lua_tonumber(L, -1); lua_pop(L, 1); \
    lua_getfield(L, idx, "w"); result.w = (float)lua_tonumber(L, -1); lua_pop(L, 1);

static int lua_push_imgui_colors(lua_State* L, ImVec4* colors);
void registerImGuiStyle(lua_State* L);

#endif //IMGUI_LIB_LUA_STYLE_H
