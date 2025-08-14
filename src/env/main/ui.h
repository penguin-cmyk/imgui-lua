//
// Created by sigma on 10/08/2025.
//

#ifndef IMGUI_LIB_LUA_UI_H
#define IMGUI_LIB_LUA_UI_H

#include "../inclusions.h"

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

#define LUA_RET_NONE return 0
#define LUA_RET_BOOL(v) lua_pushboolean(L, v); return 1
#define LUA_RET_FLOAT(v) lua_pushnumber(L, v); return 1
#define LUA_RET_VEC2(v) LUA_RETURN_IMVEC2(L, v)
#define LUA_RET_INT(v) lua_pushinteger(L, v); return 1
#define LUA_RET_CHAR(v) lua_pushstring(L, v); return 1

#define LUA_ARGS_NONE

#define LUA_ARGS_INT(var, idx, def) int var = (int)luaL_optnumber(L, idx, def)
#define LUA_ARGS_FLOAT(var, idx, def) float var = (float)luaL_optnumber(L, idx, def)
#define LUA_ARGS_FLOAT2(vx, vy) \
    float vx = (float)luaL_checknumber(L, 2); \
    float vy = (float)luaL_checknumber(L, 3)

#define LUA_ARGS_POPUP(vx, vy, def) \
    const char* vx = luaL_checkstring(L, 2); \
    int vy = (int)luaL_optnumber(L, 3, def)

#define LUA_GET_IMVEC2(L, idx, result) \
    lua_getfield(L, idx, "x"); result.x = (float)lua_tonumber(L, -1); lua_pop(L, 1); \
    lua_getfield(L, idx, "y"); result.y = (float)lua_tonumber(L, -1); lua_pop(L, 1);


#define LUA_ARGS_CHAR(var, idx) const char* var = luaL_checkstring(L, idx)

#define voidReturn_noargs(func) \
    LUA_WRAP(LUA_ARGS_NONE, func(), LUA_RET_NONE)

#define voidReturn_boolean(func) \
    LUA_WRAP(LUA_ARGS_NONE, bool result = func(), LUA_RET_BOOL(result))

#define floatReturn_noargs(func) \
    LUA_WRAP(LUA_ARGS_NONE, float result = func(), LUA_RET_FLOAT(result))

#define floatReturn_args(func, def) \
    LUA_WRAP(LUA_ARGS_FLOAT(val, 2, def), func(val), LUA_RET_NONE)

#define floatReturn_boolean(func, def) \
    LUA_WRAP(LUA_ARGS_FLOAT(val, 2, def), bool result = func(val), LUA_RET_BOOL(result))


#define intReturn_args(func, def) \
    LUA_WRAP(LUA_ARGS_INT(val, 2, def), func(val), LUA_RET_NONE)

#define intReturn_boolean(func, def) \
    LUA_WRAP(LUA_ARGS_INT(val, 2, def), bool result = func(val), LUA_RET_BOOL(result))


#define imVec2_args(func) \
    LUA_WRAP(LUA_ARGS_FLOAT2(x, y), func({x, y}), LUA_RET_NONE)


#define popup_args(func, def) \
    LUA_WRAP(LUA_ARGS_POPUP(str_id, flags, def), func(str_id, flags), LUA_RET_NONE)

#define popup_args_ret(func, def) \
    LUA_WRAP(LUA_ARGS_POPUP(str_id, flags, def), bool result = func(str_id, flags), LUA_RET_BOOL(result))

#define imVec2_noargs(func) \
    LUA_WRAP(LUA_ARGS_NONE, ImVec2 result = func(), LUA_RET_VEC2(result))

#define char_args(func) \
    LUA_WRAP(LUA_ARGS_CHAR(name, 2), func(name), LUA_RET_NONE)

#define char_args_fmt(func) \
    LUA_WRAP(LUA_ARGS_CHAR(name, 2), func("%s", name), LUA_RET_NONE)

#define char_noargs_ret(func) \
    LUA_WRAP(LUA_ARGS_NONE, const char* result = func(), LUA_RET_CHAR(result))
    
#define LUA_GET_IMVEC4(L, idx, result) \
    lua_getfield(L, idx, "x"); result.x = (float)lua_tonumber(L, -1); lua_pop(L, 1); \
    lua_getfield(L, idx, "y"); result.y = (float)lua_tonumber(L, -1); lua_pop(L, 1); \
    lua_getfield(L, idx, "z"); result.z = (float)lua_tonumber(L, -1); lua_pop(L, 1); \
    lua_getfield(L, idx, "w"); result.w = (float)lua_tonumber(L, -1); lua_pop(L, 1);

#define LUA_GET_COLOR3(idx) \
    float col[3];        \
    lua_getfield(L, idx, "r"); col[0] = (float)lua_tonumber(L, -1); lua_pop(L, 1); \
    lua_getfield(L, idx, "g"); col[1] = (float)lua_tonumber(L, -1); lua_pop(L, 1); \
    lua_getfield(L, idx, "b"); col[2] = (float)lua_tonumber(L, -1); lua_pop(L, 1);

#define LUA_GET_COLOR4(idx) \
    float col[4];        \
    lua_getfield(L, idx, "r"); col[0] = (float)lua_tonumber(L, -1); lua_pop(L, 1); \
    lua_getfield(L, idx, "g"); col[1] = (float)lua_tonumber(L, -1); lua_pop(L, 1); \
    lua_getfield(L, idx, "b"); col[2] = (float)lua_tonumber(L, -1); lua_pop(L, 1); \
    lua_getfield(L, idx, "a"); col[3] = (float)lua_tonumber(L, -1); lua_pop(L, 1);


#define LUA_COLOR3(func) \
    const char* label = luaL_checkstring(L, 2); \
    auto flags = (ImGuiColorEditFlags) luaL_optnumber(L, 4, 0); \
                                                    \
    LUA_GET_COLOR3(3)                                \
    auto ret = func(label, col, flags);               \
                                                       \
    lua_newtable(L);                                    \
    setfield(L, "r", col[0], lua_pushnumber);            \
    setfield(L, "g", col[1], lua_pushnumber);             \
    setfield(L, "b", col[2], lua_pushnumber);              \
                                                            \
    lua_pushboolean(L, ret);

#define LUA_COLOR4(func) \
    const char* label = luaL_checkstring(L, 2); \
    auto flags = (ImGuiColorEditFlags) luaL_optnumber(L, 4, 0); \
                                                    \
    LUA_GET_COLOR4(3)                                 \
    auto ret = func(label, col, flags);                \
                                                        \
    lua_newtable(L);                                     \
    setfield(L, "r", col[0], lua_pushnumber);             \
    setfield(L, "g", col[1], lua_pushnumber);              \
    setfield(L, "b", col[2], lua_pushnumber);               \
    setfield(L, "a", col[3], lua_pushnumber);                \
                                                              \
    lua_pushboolean(L, ret);


void registerImgui(lua_State* L);




#endif //IMGUI_LIB_LUA_UI_H
