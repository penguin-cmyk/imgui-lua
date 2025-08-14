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

    // Init initializes everything and opens the base libs
    lua_State* L = luaL_newstate();
    init(L);

    // this is only a placeholder, you will need to replace this of course
    int result = luaL_dofile(L, "demo.lua");
    if (result != LUA_OK) {
        const char* error = lua_tostring(L, -1);
        std::cout << error << "\n";
    }

    lua_close(L);
    FreeConsole();


    return 0;
}