#ifndef IMGUI_LIB_LUA_STYLE_H
#define IMGUI_LIB_LUA_STYLE_H

#include "env/wrapper.hpp"

static int lua_push_imgui_colors(lua_State* L, ImVec4* colors);
void register_ImGuiStyle(lua_State* L);


#endif //IMGUI_LIB_LUA_STYLE_H
