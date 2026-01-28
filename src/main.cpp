#include <iostream>

#include "ImGuiWrapper/ImGuiWrapper.hpp"
#include "env/wrapper.hpp"

auto main(const int argc, const char** argv) -> int {
    if (argc == 1) {
        std::cerr << "Usage: " << argv[0] << " <script-filename>" << std::endl;
        exit(1);
    }

    lua_State* L = init_lua();

    const char* fileName = argv[1];
    if (luaL_dofile(L, fileName) != LUA_OK) {
        const char* error = lua_tostring(L, -1);
        std::cerr << "Lua Error: " << error << std::endl;
        lua_pop(L, 1);
        lua_close(L);
        return 1;
    }

    lua_close(L);
    return 0;
}