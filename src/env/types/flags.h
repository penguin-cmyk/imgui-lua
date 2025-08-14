//
// Created by sigma on 10/08/2025.
//

#ifndef IMGUI_LIB_LUA_FLAGS_H
#define IMGUI_LIB_LUA_FLAGS_H

#include "../inclusions.h"

typedef struct {
    const char* name;
    int value;
} FlagEntry;

void registerFlags(lua_State* L);

#endif //IMGUI_LIB_LUA_FLAGS_H
