#include "renderer.hpp"

auto register_renderer(lua_State* L) -> void
{
    luaL_newlib(L, rendererFunctions);
    lua_setglobal(L, "renderer");
}
