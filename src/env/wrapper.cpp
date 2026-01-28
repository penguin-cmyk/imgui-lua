#include "wrapper.hpp"

#include "main/main.hpp"
#include "renderer/renderer.hpp"
#include "flags/flags.h"
#include "style/style.h"
#include "font/font.h"

auto register_all(lua_State *L) -> void
{
    register_renderer(L);
    register_imgui(L);
    register_flags(L);
    register_ImGuiStyle(L);
    register_ImFont(L);
    register_ImGuiIO(L);
    register_ImFontAtlas(L);
}

auto init_lua() -> lua_State*
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    register_all(L);

    return L;
}
