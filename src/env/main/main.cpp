#include "main.hpp"

auto register_imgui(lua_State* L) -> void
{
    luaL_newlib(L, imGuiFunctions);
    lua_setglobal(L, "ImGui");
}