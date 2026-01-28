#ifndef RENDERER_LUA
#define RENDERER_LUA

#include "env/wrapper.hpp"
#include "ImGuiWrapper/ImGuiWrapper.hpp"

static const luaL_Reg rendererFunctions[] = {
    {"Init", [](lua_State* L) -> int
    {
        if (wrapper == nullptr)
            wrapper = std::make_unique<ImGuiWrapper>(); // not required but just to be sure yk

        const auto name = lua_get<const char*>(L, 2);
        const auto width = lua_get<int>(L, 3);
        const auto height = lua_get<int>(L, 4);

        wrapper->Init(name, width, height);

        return lua_wrap<bool>(L, [&]() { return wrapper->m_window != nullptr && wrapper->m_initialized; });
    }},
    {"Shutdown", [](lua_State* L) -> int
    {
        if (wrapper == nullptr)
            return 0;

        wrapper->Shutdown();
        return 0;
    }},
    {"ShouldClose", [](lua_State* L) -> int
    {
       if (wrapper == nullptr)
           return 0;

        return lua_wrap<bool>(L, [&]() { return wrapper->ShouldClose(); });
    }},
    {"BeginFrame", [](lua_State* L) -> int
    {
       if (wrapper == nullptr)
           return 0;

       wrapper->BeginFrame();
       return 0;
    }},
    {"EndFrame", [](lua_State* L) -> int
    {
        if (wrapper == nullptr)
            return 0;

        wrapper->EndFrame();
        return 0;
    }},

    {NULL, NULL}
};

auto register_renderer(lua_State* L) -> void;

#endif