#include <iostream>
#include "env/gui.h"
#include "gui/gui.h"

int __stdcall wWinMain(
        HINSTANCE instance,
        HINSTANCE previousInstance,
        PWSTR arguments,
        int commandShoW
) {
    AllocConsole();
    FILE* dummy;
    freopen_s(&dummy, "CONOUT$", "w", stdout);

    lua_State* L = luaL_newstate();
    init(L);

    int result = luaL_dofile(L, "yes.lua");

    if (result != LUA_OK) {
        const char* error = lua_tostring(L, -1);
        std::cout << error << "\n";
    }

    lua_close(L);
    FreeConsole();


    return 0;
}