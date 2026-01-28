#ifndef WRAPPER_IMP
#define WRAPPER_IMP

#include <iostream>
#include <type_traits>
#include <vector>

#include "lua.hpp"
#include "imgui.h"

template<typename T>
T lua_get(lua_State* L, int idx, T opt=T{}) {
    if constexpr (std::is_same_v<T, int>) {
        return static_cast<int>(luaL_optinteger(L, idx, opt));
    }

    else if constexpr (std::is_same_v<T, float>) {
        return static_cast<float>(luaL_optnumber(L, idx, opt));
    }

    else if constexpr (std::is_same_v<T, bool>) {
        if (lua_isnoneornil(L, idx)) {
            return opt;
        }
        return static_cast<bool>(lua_toboolean(L, idx));
    }

    else if constexpr (std::is_same_v<T, const char*>) {
        if (lua_isnoneornil(L, idx)) {
            return opt;
        }
        return luaL_checkstring(L, idx);
    }

    else if constexpr (std::is_same_v<T, size_t>) {
        return static_cast<size_t>(luaL_optinteger(L, idx, opt));
    }

    else if constexpr (std::is_same_v<T, double>) {
        return static_cast<double>(luaL_optnumber(L, idx, opt));
    }

    else if constexpr (std::is_same_v<T, ImGuiID>) {
        return static_cast<ImGuiID>(luaL_optinteger(L, idx, opt));
    }

    else if constexpr (std::is_same_v<T, ImU32>) {
        return static_cast<ImU32>(luaL_optinteger(L, idx, opt));
    }

    else if constexpr (std::is_same_v<T, ImVec2>) {
        ImVec2 v = opt;
        if (lua_istable(L, idx)) {
            lua_getfield(L, idx, "x"); v.x = static_cast<float>(lua_tonumber(L, -1)); lua_pop(L, 1);
            lua_getfield(L, idx, "y"); v.y = static_cast<float>(lua_tonumber(L, -1)); lua_pop(L, 1);
        }
        return v;
    }

    else if constexpr (std::is_same_v<T, ImVec4>) {
        ImVec4 v = opt;
        if (lua_istable(L, idx))
        {
            lua_getfield(L, idx, "x"); v.x = static_cast<float>(lua_tonumber(L, -1)); lua_pop(L, 1);
            lua_getfield(L, idx, "y"); v.y = static_cast<float>(lua_tonumber(L, -1)); lua_pop(L, 1);
            lua_getfield(L, idx, "z"); v.z = static_cast<float>(lua_tonumber(L, -1)); lua_pop(L, 1);
            lua_getfield(L, idx, "w"); v.w = static_cast<float>(lua_tonumber(L, -1)); lua_pop(L, 1);
        }
        return v;
    }

    else if constexpr (std::is_same_v<T, ImColor>) {
        ImColor c = opt;
        if (lua_istable(L, idx)) {
            lua_getfield(L, idx, "r"); c.Value.x = static_cast<float>(lua_tonumber(L, -1)); lua_pop(L, 1);
            lua_getfield(L, idx, "g"); c.Value.y = static_cast<float>(lua_tonumber(L, -1)); lua_pop(L, 1);
            lua_getfield(L, idx, "b"); c.Value.z = static_cast<float>(lua_tonumber(L, -1)); lua_pop(L, 1);
            lua_getfield(L, idx, "a"); c.Value.w = static_cast<float>(lua_tonumber(L, -1)); lua_pop(L, 1);
        }
        return c;
    }

    return T{};
}

template<typename Ret, typename F>
int lua_wrap(lua_State* L, F func) {
    if constexpr (std::is_same_v<Ret, void>) {
        func();
        return 0;
    }

    else if constexpr (std::is_same_v<Ret, bool>) {
        const bool res = func();
        lua_pushboolean(L, res);
        return 1;
    }

    else if constexpr (std::is_same_v<Ret, float>) {
        const float res = func();
        lua_pushnumber(L, res);
        return 1;
    }

    else if constexpr (std::is_same_v<Ret, int>) {
        const int res = func();
        lua_pushinteger(L, res);
        return 1;
    }

    else if constexpr (std::is_same_v<Ret, double>) {
        const int res = func();
        lua_pushinteger(L, res);
        return 1;
    }

    else if constexpr (std::is_same_v<Ret, const char*>) {
        const char* res = func();
        lua_pushstring(L, res);
        return 1;
    }

    else if constexpr (std::is_same_v<Ret, ImVec2>) {
        const ImVec2 res = func();
        lua_newtable(L);
        lua_pushnumber(L, res.x); lua_setfield(L, -2, "x");
        lua_pushnumber(L, res.y); lua_setfield(L, -2, "y");
        return 1;
    }

    else if constexpr (std::is_same_v<Ret, ImVec4>) {
        const ImVec4 res = func();
        lua_newtable(L);
        lua_pushnumber(L, res.x); lua_setfield(L, -2, "x");
        lua_pushnumber(L, res.y); lua_setfield(L, -2, "y");
        lua_pushnumber(L, res.z); lua_setfield(L, -2, "z");
        lua_pushnumber(L, res.w); lua_setfield(L, -2, "w");
        return 1;
    }

    else if constexpr (std::is_same_v<Ret, ImColor>) {
        const ImColor res = func();
        lua_newtable(L);
        lua_pushnumber(L, res.Value.x); lua_setfield(L, -2, "r");
        lua_pushnumber(L, res.Value.y); lua_setfield(L, -2, "g");
        lua_pushnumber(L, res.Value.z); lua_setfield(L, -2, "b");
        lua_pushnumber(L, res.Value.w); lua_setfield(L, -2, "a");
        return 1;
    }
    return 0;
}

auto init_lua() -> lua_State*;

#endif