#ifndef IO_HPP
#define IO_HPP

#include "env/wrapper.hpp"

void register_ImGuiIO(lua_State* L);
void register_ImFontAtlas(lua_State* L);
void register_ImFont(lua_State* L);
auto lua_imgui_pushfont(lua_State* L) -> int;
auto lua_imgui_popfont(lua_State* L) -> int;




#endif