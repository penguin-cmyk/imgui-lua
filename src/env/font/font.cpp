#include "font.h"

auto lua_fontatlas_addfont(lua_State* L) -> int
{
    const auto* atlas_ptr = static_cast<ImFontAtlas**>(luaL_checkudata(L, 1, "ImFontAtlas"));
    if (!atlas_ptr || !*atlas_ptr) { return luaL_error(L, "Invalid ImFontAtlas object"); }

    ImFontAtlas* atlas = *atlas_ptr;
    const char* font_path = lua_get<const char*>(L, 2);
    float size_pixels = lua_get<float>(L, 3);

    ImFont* font = atlas->AddFontFromFileTTF(font_path, size_pixels);

    if (!font) {
        return luaL_error(L, "Failed to load font: %s", font_path);
    }

    ImFont** font_ptr = static_cast<ImFont**>(lua_newuserdata(L, sizeof(ImFont*)));
    *font_ptr = font;
    luaL_getmetatable(L, "ImFont");
    lua_setmetatable(L, -2);
    return 1;
}

auto lua_fontatlas_adddefaultfont(lua_State* L) -> int
{
    const auto* atlas_ptr = static_cast<ImFontAtlas**>(luaL_checkudata(L, 1, "ImFontAtlas"));
    if (!atlas_ptr || !*atlas_ptr) { return luaL_error(L, "Invalid ImFontAtlas object"); }

    ImFontAtlas* atlas = *atlas_ptr;

    ImFont* font = atlas->AddFontDefault();

    ImFont** font_ptr = static_cast<ImFont**>(lua_newuserdata(L, sizeof(ImFont*)));
    *font_ptr = font;
    luaL_getmetatable(L, "ImFont");
    lua_setmetatable(L, -2);
    return 1;
}

auto lua_fontatlas_build(lua_State* L) -> int
{
    const auto* atlas_ptr = static_cast<ImFontAtlas**>(luaL_checkudata(L, 1, "ImFontAtlas"));
    if (!atlas_ptr || !*atlas_ptr) { return luaL_error(L, "Invalid ImFontAtlas object"); }

    ImFontAtlas* atlas = *atlas_ptr;

    return lua_wrap<bool>(L, [&]() {
        return atlas->Build();
    });
}

auto lua_imgui_pushfont(lua_State* L) -> int
{
    const auto* font_ptr = static_cast<ImFont**>(luaL_checkudata(L, 2, "ImFont"));
    if (!font_ptr || !*font_ptr) { return luaL_error(L, "Invalid ImFont object"); }

    ImFont* font = *font_ptr;

    return lua_wrap<void>(L, [&]() {
        ImGui::PushFont(font);
    });
}

auto lua_imgui_popfont(lua_State* L) -> int
{
    return lua_wrap<void>(L, [&]() {
        ImGui::PopFont();
    });
}

auto lua_io_getfontatlas(lua_State* L) -> int
{
    const auto* io_ptr = static_cast<ImGuiIO**>(luaL_checkudata(L, 1, "ImGuiIO"));
    if (!io_ptr || !*io_ptr) { return luaL_error(L, "Invalid ImGuiIO object"); }

    ImGuiIO* io = *io_ptr;
    ImFontAtlas* atlas = io->Fonts;

    ImFontAtlas** atlas_ptr = static_cast<ImFontAtlas**>(lua_newuserdata(L, sizeof(ImFontAtlas*)));
    *atlas_ptr = atlas;
    luaL_getmetatable(L, "ImFontAtlas");
    lua_setmetatable(L, -2);
    return 1;
}


auto lua_fontatlas_index(lua_State* L) -> int
{
    const auto* atlas_ptr = static_cast<ImFontAtlas**>(luaL_checkudata(L, 1, "ImFontAtlas"));
    if (!atlas_ptr || !*atlas_ptr) { return luaL_error(L, "Invalid ImFontAtlas object"); }

    ImFontAtlas* atlas = *atlas_ptr;
    const std::string key = luaL_checkstring(L, 2);

    if (key == "AddFont") {
        lua_pushcfunction(L, lua_fontatlas_addfont);
        return 1;
    }
    if (key == "AddFontDefault") {
        lua_pushcfunction(L, lua_fontatlas_adddefaultfont);
        return 1;
    }
    if (key == "Build") {
        lua_pushcfunction(L, lua_fontatlas_build);
        return 1;
    }

    if (key == "Flags") {
        return lua_wrap<int>(L, [&]() { return atlas->Flags; });
    }
    if (key == "TexDesiredFormat") {
        return lua_wrap<int>(L, [&]() { return atlas->TexDesiredFormat; });
    }
    if (key == "TexGlyphPadding") {
        return lua_wrap<int>(L, [&]() { return atlas->TexGlyphPadding; });
    }
    if (key == "TexMinWidth") {
        return lua_wrap<int>(L, [&]() { return atlas->TexMinWidth; });
    }
    if (key == "TexMinHeight") {
        return lua_wrap<int>(L, [&]() { return atlas->TexMinHeight; });
    }
    if (key == "TexMaxWidth") {
        return lua_wrap<int>(L, [&]() { return atlas->TexMaxWidth; });
    }
    if (key == "TexMaxHeight") {
        return lua_wrap<int>(L, [&]() { return atlas->TexMaxHeight; });
    }
    if (key == "Locked") {
        return lua_wrap<bool>(L, [&]() { return atlas->Locked; });
    }
    if (key == "RendererHasTextures") {
        return lua_wrap<bool>(L, [&]() { return atlas->RendererHasTextures; });
    }
    if (key == "TexIsBuilt") {
        return lua_wrap<bool>(L, [&]() { return atlas->TexIsBuilt; });
    }
    if (key == "TexPixelsUseColors") {
        return lua_wrap<bool>(L, [&]() { return atlas->TexPixelsUseColors; });
    }
    if (key == "TexUvScale") {
        return lua_wrap<ImVec2>(L, [&]() { return atlas->TexUvScale; });
    }
    if (key == "TexUvWhitePixel") {
        return lua_wrap<ImVec2>(L, [&]() { return atlas->TexUvWhitePixel; });
    }

    return 0;
}

auto lua_fontatlas_newindex(lua_State* L) -> int
{
    const auto* atlas_ptr = static_cast<ImFontAtlas**>(luaL_checkudata(L, 1, "ImFontAtlas"));
    if (!atlas_ptr || !*atlas_ptr) { return luaL_error(L, "Invalid ImFontAtlas object"); }

    ImFontAtlas* atlas = *atlas_ptr;
    const std::string key = luaL_checkstring(L, 2);

    if (key == "Flags") {
        atlas->Flags = static_cast<ImFontAtlasFlags>(lua_get<int>(L, 3));
        return 0;
    }
    if (key == "TexDesiredFormat") {
        atlas->TexDesiredFormat = static_cast<ImTextureFormat>(lua_get<int>(L, 3));
        return 0;
    }
    if (key == "TexGlyphPadding") {
        atlas->TexGlyphPadding = lua_get<int>(L, 3);
        return 0;
    }
    if (key == "TexMinWidth") {
        atlas->TexMinWidth = lua_get<int>(L, 3);
        return 0;
    }
    if (key == "TexMinHeight") {
        atlas->TexMinHeight = lua_get<int>(L, 3);
        return 0;
    }
    if (key == "TexMaxWidth") {
        atlas->TexMaxWidth = lua_get<int>(L, 3);
        return 0;
    }
    if (key == "TexMaxHeight") {
        atlas->TexMaxHeight = lua_get<int>(L, 3);
        return 0;
    }
    if (key == "TexPixelsUseColors") {
        atlas->TexPixelsUseColors = lua_get<bool>(L, 3);
        return 0;
    }

    return luaL_error(L, "Invalid ImFontAtlas property: %s", key.c_str());
}

auto lua_font_index(lua_State* L) -> int
{
    const auto* font_ptr = static_cast<ImFont**>(luaL_checkudata(L, 1, "ImFont"));
    if (!font_ptr || !*font_ptr) { return luaL_error(L, "Invalid ImFont object"); }

    ImFont* font = *font_ptr;
    const std::string key = luaL_checkstring(L, 2);

    if (key == "Flags") {
        return lua_wrap<int>(L, [&]() { return font->Flags; });
    }
    if (key == "CurrentRasterizerDensity") {
        return lua_wrap<float>(L, [&]() { return font->CurrentRasterizerDensity; });
    }
    if (key == "FontId") {
        return lua_wrap<int>(L, [&]() { return font->FontId; });
    }
    if (key == "LegacySize") {
        return lua_wrap<float>(L, [&]() { return font->LegacySize; });
    }
    if (key == "EllipsisChar") {
        return lua_wrap<int>(L, [&]() { return font->EllipsisChar; });
    }
    if (key == "FallbackChar") {
        return lua_wrap<int>(L, [&]() { return font->FallbackChar; });
    }
    if (key == "EllipsisAutoBake") {
        return lua_wrap<bool>(L, [&]() { return font->EllipsisAutoBake; });
    }
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    if (key == "Scale") {
        return lua_wrap<float>(L, [&]() { return font->Scale; });
    }
#endif

    return 0;
}

auto lua_font_newindex(lua_State* L) -> int
{
    const auto* font_ptr = static_cast<ImFont**>(luaL_checkudata(L, 1, "ImFont"));
    if (!font_ptr || !*font_ptr) { return luaL_error(L, "Invalid ImFont object"); }

    ImFont* font = *font_ptr;
    const std::string key = luaL_checkstring(L, 2);

    if (key == "Flags") {
        font->Flags = static_cast<ImFontFlags>(lua_get<int>(L, 3));
        return 0;
    }
    if (key == "CurrentRasterizerDensity") {
        font->CurrentRasterizerDensity = lua_get<float>(L, 3);
        return 0;
    }
    if (key == "EllipsisChar") {
        font->EllipsisChar = static_cast<ImWchar>(lua_get<int>(L, 3));
        return 0;
    }
    if (key == "FallbackChar") {
        font->FallbackChar = static_cast<ImWchar>(lua_get<int>(L, 3));
        return 0;
    }
    if (key == "EllipsisAutoBake") {
        font->EllipsisAutoBake = lua_get<bool>(L, 3);
        return 0;
    }
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    if (key == "Scale") {
        font->Scale = lua_get<float>(L, 3);
        return 0;
    }
#endif

    return luaL_error(L, "Invalid ImFont property: %s", key.c_str());
}

auto lua_io_addkeyevent(lua_State* L) -> int
{
    const auto* io_ptr = static_cast<ImGuiIO**>(luaL_checkudata(L, 1, "ImGuiIO"));
    if (!io_ptr || !*io_ptr) { return luaL_error(L, "Invalid ImGuiIO object"); }

    ImGuiIO* io = *io_ptr;
    ImGuiKey key = static_cast<ImGuiKey>(lua_get<int>(L, 2));
    bool down = lua_get<bool>(L, 3);

    return lua_wrap<void>(L, [&]() {
        io->AddKeyEvent(key, down);
    });
}

auto lua_io_addkeyanalog_event(lua_State* L) -> int
{
    const auto* io_ptr = static_cast<ImGuiIO**>(luaL_checkudata(L, 1, "ImGuiIO"));
    if (!io_ptr || !*io_ptr) { return luaL_error(L, "Invalid ImGuiIO object"); }

    ImGuiIO* io = *io_ptr;
    ImGuiKey key = static_cast<ImGuiKey>(lua_get<int>(L, 2));
    bool down = lua_get<bool>(L, 3);
    float v = lua_get<float>(L, 4);

    return lua_wrap<void>(L, [&]() {
        io->AddKeyAnalogEvent(key, down, v);
    });
}

auto lua_io_addmouseposevent(lua_State* L) -> int
{
    const auto* io_ptr = static_cast<ImGuiIO**>(luaL_checkudata(L, 1, "ImGuiIO"));
    if (!io_ptr || !*io_ptr) { return luaL_error(L, "Invalid ImGuiIO object"); }

    ImGuiIO* io = *io_ptr;
    float x = lua_get<float>(L, 2);
    float y = lua_get<float>(L, 3);

    return lua_wrap<void>(L, [&]() {
        io->AddMousePosEvent(x, y);
    });
}

auto lua_io_addmousebuttonevent(lua_State* L) -> int
{
    const auto* io_ptr = static_cast<ImGuiIO**>(luaL_checkudata(L, 1, "ImGuiIO"));
    if (!io_ptr || !*io_ptr) { return luaL_error(L, "Invalid ImGuiIO object"); }

    ImGuiIO* io = *io_ptr;
    int button = lua_get<int>(L, 2);
    bool down = lua_get<bool>(L, 3);

    return lua_wrap<void>(L, [&]() {
        io->AddMouseButtonEvent(button, down);
    });
}

auto lua_io_addmousewheelevent(lua_State* L) -> int
{
    const auto* io_ptr = static_cast<ImGuiIO**>(luaL_checkudata(L, 1, "ImGuiIO"));
    if (!io_ptr || !*io_ptr) { return luaL_error(L, "Invalid ImGuiIO object"); }

    ImGuiIO* io = *io_ptr;
    float wheel_x = lua_get<float>(L, 2);
    float wheel_y = lua_get<float>(L, 3);

    return lua_wrap<void>(L, [&]() {
        io->AddMouseWheelEvent(wheel_x, wheel_y);
    });
}

auto lua_io_addmousesourceevent(lua_State* L) -> int
{
    const auto* io_ptr = static_cast<ImGuiIO**>(luaL_checkudata(L, 1, "ImGuiIO"));
    if (!io_ptr || !*io_ptr) { return luaL_error(L, "Invalid ImGuiIO object"); }

    ImGuiIO* io = *io_ptr;
    ImGuiMouseSource source = static_cast<ImGuiMouseSource>(lua_get<int>(L, 2));

    return lua_wrap<void>(L, [&]() {
        io->AddMouseSourceEvent(source);
    });
}

auto lua_io_addfocusevent(lua_State* L) -> int
{
    const auto* io_ptr = static_cast<ImGuiIO**>(luaL_checkudata(L, 1, "ImGuiIO"));
    if (!io_ptr || !*io_ptr) { return luaL_error(L, "Invalid ImGuiIO object"); }

    ImGuiIO* io = *io_ptr;
    bool focused = lua_get<bool>(L, 2);

    return lua_wrap<void>(L, [&]() {
        io->AddFocusEvent(focused);
    });
}

auto lua_io_addinputcharacter(lua_State* L) -> int
{
    const auto* io_ptr = static_cast<ImGuiIO**>(luaL_checkudata(L, 1, "ImGuiIO"));
    if (!io_ptr || !*io_ptr) { return luaL_error(L, "Invalid ImGuiIO object"); }

    ImGuiIO* io = *io_ptr;
    unsigned int c = static_cast<unsigned int>(lua_get<int>(L, 2));

    return lua_wrap<void>(L, [&]() {
        io->AddInputCharacter(c);
    });
}

auto lua_io_addinputcharacterutf16(lua_State* L) -> int
{
    const auto* io_ptr = static_cast<ImGuiIO**>(luaL_checkudata(L, 1, "ImGuiIO"));
    if (!io_ptr || !*io_ptr) { return luaL_error(L, "Invalid ImGuiIO object"); }

    ImGuiIO* io = *io_ptr;
    ImWchar16 c = static_cast<ImWchar16>(lua_get<int>(L, 2));

    return lua_wrap<void>(L, [&]() {
        io->AddInputCharacterUTF16(c);
    });
}

auto lua_io_addinputcharactersutf8(lua_State* L) -> int
{
    const auto* io_ptr = static_cast<ImGuiIO**>(luaL_checkudata(L, 1, "ImGuiIO"));
    if (!io_ptr || !*io_ptr) { return luaL_error(L, "Invalid ImGuiIO object"); }

    ImGuiIO* io = *io_ptr;
    const char* str = lua_get<const char*>(L, 2);

    return lua_wrap<void>(L, [&]() {
        io->AddInputCharactersUTF8(str);
    });
}

auto lua_io_setkeyeventnativedata(lua_State* L) -> int
{
    const auto* io_ptr = static_cast<ImGuiIO**>(luaL_checkudata(L, 1, "ImGuiIO"));
    if (!io_ptr || !*io_ptr) { return luaL_error(L, "Invalid ImGuiIO object"); }

    ImGuiIO* io = *io_ptr;
    ImGuiKey key = static_cast<ImGuiKey>(lua_get<int>(L, 2));
    int native_keycode = lua_get<int>(L, 3);
    int native_scancode = lua_get<int>(L, 4);
    int native_legacy_index = lua_get<int>(L, 5, -1);

    return lua_wrap<void>(L, [&]() {
        io->SetKeyEventNativeData(key, native_keycode, native_scancode, native_legacy_index);
    });
}

auto lua_io_setappacceptingevents(lua_State* L) -> int
{
    const auto* io_ptr = static_cast<ImGuiIO**>(luaL_checkudata(L, 1, "ImGuiIO"));
    if (!io_ptr || !*io_ptr) { return luaL_error(L, "Invalid ImGuiIO object"); }

    ImGuiIO* io = *io_ptr;
    bool accepting_events = lua_get<bool>(L, 2);

    return lua_wrap<void>(L, [&]() {
        io->SetAppAcceptingEvents(accepting_events);
    });
}

auto lua_io_cleareventsqueue(lua_State* L) -> int
{
    const auto* io_ptr = static_cast<ImGuiIO**>(luaL_checkudata(L, 1, "ImGuiIO"));
    if (!io_ptr || !*io_ptr) { return luaL_error(L, "Invalid ImGuiIO object"); }

    ImGuiIO* io = *io_ptr;

    return lua_wrap<void>(L, [&]() {
        io->ClearEventsQueue();
    });
}

auto lua_io_clearinputkeys(lua_State* L) -> int
{
    const auto* io_ptr = static_cast<ImGuiIO**>(luaL_checkudata(L, 1, "ImGuiIO"));
    if (!io_ptr || !*io_ptr) { return luaL_error(L, "Invalid ImGuiIO object"); }

    ImGuiIO* io = *io_ptr;

    return lua_wrap<void>(L, [&]() {
        io->ClearInputKeys();
    });
}

auto lua_io_clearinputmouse(lua_State* L) -> int
{
    const auto* io_ptr = static_cast<ImGuiIO**>(luaL_checkudata(L, 1, "ImGuiIO"));
    if (!io_ptr || !*io_ptr) { return luaL_error(L, "Invalid ImGuiIO object"); }

    ImGuiIO* io = *io_ptr;

    return lua_wrap<void>(L, [&]() {
        io->ClearInputMouse();
    });
}

auto lua_io_index(lua_State* L) -> int
{
    const auto* io_ptr = static_cast<ImGuiIO**>(luaL_checkudata(L, 1, "ImGuiIO"));
    if (!io_ptr || !*io_ptr) { return luaL_error(L, "Invalid ImGuiIO object"); }

    ImGuiIO* io = *io_ptr;
    const std::string key = luaL_checkstring(L, 2);

    if (key == "Fonts") {
        lua_pushcfunction(L, lua_io_getfontatlas);
        return 1;
    }

    if (key == "AddKeyEvent") {
        lua_pushcfunction(L, lua_io_addkeyevent);
        return 1;
    }
    if (key == "AddKeyAnalogEvent") {
        lua_pushcfunction(L, lua_io_addkeyanalog_event);
        return 1;
    }
    if (key == "AddMousePosEvent") {
        lua_pushcfunction(L, lua_io_addmouseposevent);
        return 1;
    }
    if (key == "AddMouseButtonEvent") {
        lua_pushcfunction(L, lua_io_addmousebuttonevent);
        return 1;
    }
    if (key == "AddMouseWheelEvent") {
        lua_pushcfunction(L, lua_io_addmousewheelevent);
        return 1;
    }
    if (key == "AddMouseSourceEvent") {
        lua_pushcfunction(L, lua_io_addmousesourceevent);
        return 1;
    }
    if (key == "AddFocusEvent") {
        lua_pushcfunction(L, lua_io_addfocusevent);
        return 1;
    }
    if (key == "AddInputCharacter") {
        lua_pushcfunction(L, lua_io_addinputcharacter);
        return 1;
    }
    if (key == "AddInputCharacterUTF16") {
        lua_pushcfunction(L, lua_io_addinputcharacterutf16);
        return 1;
    }
    if (key == "AddInputCharactersUTF8") {
        lua_pushcfunction(L, lua_io_addinputcharactersutf8);
        return 1;
    }
    if (key == "SetKeyEventNativeData") {
        lua_pushcfunction(L, lua_io_setkeyeventnativedata);
        return 1;
    }
    if (key == "SetAppAcceptingEvents") {
        lua_pushcfunction(L, lua_io_setappacceptingevents);
        return 1;
    }
    if (key == "ClearEventsQueue") {
        lua_pushcfunction(L, lua_io_cleareventsqueue);
        return 1;
    }
    if (key == "ClearInputKeys") {
        lua_pushcfunction(L, lua_io_clearinputkeys);
        return 1;
    }
    if (key == "ClearInputMouse") {
        lua_pushcfunction(L, lua_io_clearinputmouse);
        return 1;
    }

    if (key == "ConfigFlags") {
        return lua_wrap<int>(L, [&]() { return io->ConfigFlags; });
    }
    if (key == "BackendFlags") {
        return lua_wrap<int>(L, [&]() { return io->BackendFlags; });
    }
    if (key == "DisplaySize") {
        return lua_wrap<ImVec2>(L, [&]() { return io->DisplaySize; });
    }
    if (key == "DisplayFramebufferScale") {
        return lua_wrap<ImVec2>(L, [&]() { return io->DisplayFramebufferScale; });
    }
    if (key == "DeltaTime") {
        return lua_wrap<float>(L, [&]() { return io->DeltaTime; });
    }
    if (key == "IniSavingRate") {
        return lua_wrap<float>(L, [&]() { return io->IniSavingRate; });
    }
    if (key == "IniFilename") {
        return lua_wrap<const char*>(L, [&]() { return io->IniFilename; });
    }
    if (key == "LogFilename") {
        return lua_wrap<const char*>(L, [&]() { return io->LogFilename; });
    }
    if (key == "FontAllowUserScaling") {
        return lua_wrap<bool>(L, [&]() { return io->FontAllowUserScaling; });
    }
    if (key == "ConfigNavSwapGamepadButtons") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigNavSwapGamepadButtons; });
    }
    if (key == "ConfigNavMoveSetMousePos") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigNavMoveSetMousePos; });
    }
    if (key == "ConfigNavCaptureKeyboard") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigNavCaptureKeyboard; });
    }
    if (key == "ConfigNavEscapeClearFocusItem") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigNavEscapeClearFocusItem; });
    }
    if (key == "ConfigNavEscapeClearFocusWindow") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigNavEscapeClearFocusWindow; });
    }
    if (key == "ConfigNavCursorVisibleAuto") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigNavCursorVisibleAuto; });
    }
    if (key == "ConfigNavCursorVisibleAlways") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigNavCursorVisibleAlways; });
    }
    if (key == "MouseDrawCursor") {
        return lua_wrap<bool>(L, [&]() { return io->MouseDrawCursor; });
    }
    if (key == "ConfigMacOSXBehaviors") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigMacOSXBehaviors; });
    }
    if (key == "ConfigInputTrickleEventQueue") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigInputTrickleEventQueue; });
    }
    if (key == "ConfigInputTextCursorBlink") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigInputTextCursorBlink; });
    }
    if (key == "ConfigInputTextEnterKeepActive") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigInputTextEnterKeepActive; });
    }
    if (key == "ConfigDragClickToInputText") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigDragClickToInputText; });
    }
    if (key == "ConfigWindowsResizeFromEdges") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigWindowsResizeFromEdges; });
    }
    if (key == "ConfigWindowsMoveFromTitleBarOnly") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigWindowsMoveFromTitleBarOnly; });
    }
    if (key == "ConfigWindowsCopyContentsWithCtrlC") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigWindowsCopyContentsWithCtrlC; });
    }
    if (key == "ConfigScrollbarScrollByPage") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigScrollbarScrollByPage; });
    }
    if (key == "ConfigMemoryCompactTimer") {
        return lua_wrap<float>(L, [&]() { return io->ConfigMemoryCompactTimer; });
    }
    if (key == "MouseDoubleClickTime") {
        return lua_wrap<float>(L, [&]() { return io->MouseDoubleClickTime; });
    }
    if (key == "MouseDoubleClickMaxDist") {
        return lua_wrap<float>(L, [&]() { return io->MouseDoubleClickMaxDist; });
    }
    if (key == "MouseDragThreshold") {
        return lua_wrap<float>(L, [&]() { return io->MouseDragThreshold; });
    }
    if (key == "KeyRepeatDelay") {
        return lua_wrap<float>(L, [&]() { return io->KeyRepeatDelay; });
    }
    if (key == "KeyRepeatRate") {
        return lua_wrap<float>(L, [&]() { return io->KeyRepeatRate; });
    }
    if (key == "ConfigErrorRecovery") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigErrorRecovery; });
    }
    if (key == "ConfigErrorRecoveryEnableAssert") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigErrorRecoveryEnableAssert; });
    }
    if (key == "ConfigErrorRecoveryEnableDebugLog") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigErrorRecoveryEnableDebugLog; });
    }
    if (key == "ConfigErrorRecoveryEnableTooltip") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigErrorRecoveryEnableTooltip; });
    }
    if (key == "ConfigDebugIsDebuggerPresent") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigDebugIsDebuggerPresent; });
    }
    if (key == "ConfigDebugHighlightIdConflicts") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigDebugHighlightIdConflicts; });
    }
    if (key == "ConfigDebugHighlightIdConflictsShowItemPicker") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigDebugHighlightIdConflictsShowItemPicker; });
    }
    if (key == "ConfigDebugBeginReturnValueOnce") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigDebugBeginReturnValueOnce; });
    }
    if (key == "ConfigDebugBeginReturnValueLoop") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigDebugBeginReturnValueLoop; });
    }
    if (key == "ConfigDebugIgnoreFocusLoss") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigDebugIgnoreFocusLoss; });
    }
    if (key == "ConfigDebugIniSettings") {
        return lua_wrap<bool>(L, [&]() { return io->ConfigDebugIniSettings; });
    }
    if (key == "BackendPlatformName") {
        return lua_wrap<const char*>(L, [&]() { return io->BackendPlatformName; });
    }
    if (key == "BackendRendererName") {
        return lua_wrap<const char*>(L, [&]() { return io->BackendRendererName; });
    }
    if (key == "WantCaptureMouse") {
        return lua_wrap<bool>(L, [&]() { return io->WantCaptureMouse; });
    }
    if (key == "WantCaptureKeyboard") {
        return lua_wrap<bool>(L, [&]() { return io->WantCaptureKeyboard; });
    }
    if (key == "WantTextInput") {
        return lua_wrap<bool>(L, [&]() { return io->WantTextInput; });
    }
    if (key == "WantSetMousePos") {
        return lua_wrap<bool>(L, [&]() { return io->WantSetMousePos; });
    }
    if (key == "WantSaveIniSettings") {
        return lua_wrap<bool>(L, [&]() { return io->WantSaveIniSettings; });
    }
    if (key == "NavActive") {
        return lua_wrap<bool>(L, [&]() { return io->NavActive; });
    }
    if (key == "NavVisible") {
        return lua_wrap<bool>(L, [&]() { return io->NavVisible; });
    }
    if (key == "Framerate") {
        return lua_wrap<float>(L, [&]() { return io->Framerate; });
    }
    if (key == "MetricsRenderVertices") {
        return lua_wrap<int>(L, [&]() { return io->MetricsRenderVertices; });
    }
    if (key == "MetricsRenderIndices") {
        return lua_wrap<int>(L, [&]() { return io->MetricsRenderIndices; });
    }
    if (key == "MetricsRenderWindows") {
        return lua_wrap<int>(L, [&]() { return io->MetricsRenderWindows; });
    }
    if (key == "MetricsActiveWindows") {
        return lua_wrap<int>(L, [&]() { return io->MetricsActiveWindows; });
    }
    if (key == "MouseDelta") {
        return lua_wrap<ImVec2>(L, [&]() { return io->MouseDelta; });
    }
    if (key == "MousePos") {
        return lua_wrap<ImVec2>(L, [&]() { return io->MousePos; });
    }
    if (key == "MouseWheel") {
        return lua_wrap<float>(L, [&]() { return io->MouseWheel; });
    }
    if (key == "MouseWheelH") {
        return lua_wrap<float>(L, [&]() { return io->MouseWheelH; });
    }
    if (key == "MouseSource") {
        return lua_wrap<int>(L, [&]() { return io->MouseSource; });
    }
    if (key == "KeyCtrl") {
        return lua_wrap<bool>(L, [&]() { return io->KeyCtrl; });
    }
    if (key == "KeyShift") {
        return lua_wrap<bool>(L, [&]() { return io->KeyShift; });
    }
    if (key == "KeyAlt") {
        return lua_wrap<bool>(L, [&]() { return io->KeyAlt; });
    }
    if (key == "KeySuper") {
        return lua_wrap<bool>(L, [&]() { return io->KeySuper; });
    }
    if (key == "KeyMods") {
        return lua_wrap<int>(L, [&]() { return io->KeyMods; });
    }
    if (key == "PenPressure") {
        return lua_wrap<float>(L, [&]() { return io->PenPressure; });
    }
    if (key == "AppFocusLost") {
        return lua_wrap<bool>(L, [&]() { return io->AppFocusLost; });
    }
    if (key == "AppAcceptingEvents") {
        return lua_wrap<bool>(L, [&]() { return io->AppAcceptingEvents; });
    }
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    if (key == "FontGlobalScale") {
        return lua_wrap<float>(L, [&]() { return io->FontGlobalScale; });
    }
#endif

    return 0;
}

auto lua_io_newindex(lua_State* L) -> int
{
    const auto* io_ptr = static_cast<ImGuiIO**>(luaL_checkudata(L, 1, "ImGuiIO"));
    if (!io_ptr || !*io_ptr) { return luaL_error(L, "Invalid ImGuiIO object"); }

    ImGuiIO* io = *io_ptr;
    const std::string key = luaL_checkstring(L, 2);

    if (key == "ConfigFlags") {
        io->ConfigFlags = static_cast<ImGuiConfigFlags>(lua_get<int>(L, 3));
        return 0;
    }
    if (key == "DisplaySize") {
        io->DisplaySize = lua_get<ImVec2>(L, 3);
        return 0;
    }
    if (key == "DisplayFramebufferScale") {
        io->DisplayFramebufferScale = lua_get<ImVec2>(L, 3);
        return 0;
    }
    if (key == "DeltaTime") {
        io->DeltaTime = lua_get<float>(L, 3);
        return 0;
    }
    if (key == "IniSavingRate") {
        io->IniSavingRate = lua_get<float>(L, 3);
        return 0;
    }
    if (key == "IniFilename") {
        io->IniFilename = lua_get<const char*>(L, 3);
        return 0;
    }
    if (key == "LogFilename") {
        io->LogFilename = lua_get<const char*>(L, 3);
        return 0;
    }
    if (key == "FontAllowUserScaling") {
        io->FontAllowUserScaling = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigNavSwapGamepadButtons") {
        io->ConfigNavSwapGamepadButtons = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigNavMoveSetMousePos") {
        io->ConfigNavMoveSetMousePos = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigNavCaptureKeyboard") {
        io->ConfigNavCaptureKeyboard = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigNavEscapeClearFocusItem") {
        io->ConfigNavEscapeClearFocusItem = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigNavEscapeClearFocusWindow") {
        io->ConfigNavEscapeClearFocusWindow = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigNavCursorVisibleAuto") {
        io->ConfigNavCursorVisibleAuto = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigNavCursorVisibleAlways") {
        io->ConfigNavCursorVisibleAlways = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "MouseDrawCursor") {
        io->MouseDrawCursor = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigMacOSXBehaviors") {
        io->ConfigMacOSXBehaviors = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigInputTrickleEventQueue") {
        io->ConfigInputTrickleEventQueue = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigInputTextCursorBlink") {
        io->ConfigInputTextCursorBlink = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigInputTextEnterKeepActive") {
        io->ConfigInputTextEnterKeepActive = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigDragClickToInputText") {
        io->ConfigDragClickToInputText = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigWindowsResizeFromEdges") {
        io->ConfigWindowsResizeFromEdges = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigWindowsMoveFromTitleBarOnly") {
        io->ConfigWindowsMoveFromTitleBarOnly = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigWindowsCopyContentsWithCtrlC") {
        io->ConfigWindowsCopyContentsWithCtrlC = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigScrollbarScrollByPage") {
        io->ConfigScrollbarScrollByPage = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigMemoryCompactTimer") {
        io->ConfigMemoryCompactTimer = lua_get<float>(L, 3);
        return 0;
    }
    if (key == "MouseDoubleClickTime") {
        io->MouseDoubleClickTime = lua_get<float>(L, 3);
        return 0;
    }
    if (key == "MouseDoubleClickMaxDist") {
        io->MouseDoubleClickMaxDist = lua_get<float>(L, 3);
        return 0;
    }
    if (key == "MouseDragThreshold") {
        io->MouseDragThreshold = lua_get<float>(L, 3);
        return 0;
    }
    if (key == "KeyRepeatDelay") {
        io->KeyRepeatDelay = lua_get<float>(L, 3);
        return 0;
    }
    if (key == "KeyRepeatRate") {
        io->KeyRepeatRate = lua_get<float>(L, 3);
        return 0;
    }
    if (key == "ConfigErrorRecovery") {
        io->ConfigErrorRecovery = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigErrorRecoveryEnableAssert") {
        io->ConfigErrorRecoveryEnableAssert = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigErrorRecoveryEnableDebugLog") {
        io->ConfigErrorRecoveryEnableDebugLog = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigErrorRecoveryEnableTooltip") {
        io->ConfigErrorRecoveryEnableTooltip = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigDebugIsDebuggerPresent") {
        io->ConfigDebugIsDebuggerPresent = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigDebugHighlightIdConflicts") {
        io->ConfigDebugHighlightIdConflicts = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigDebugHighlightIdConflictsShowItemPicker") {
        io->ConfigDebugHighlightIdConflictsShowItemPicker = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigDebugBeginReturnValueOnce") {
        io->ConfigDebugBeginReturnValueOnce = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigDebugBeginReturnValueLoop") {
        io->ConfigDebugBeginReturnValueLoop = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigDebugIgnoreFocusLoss") {
        io->ConfigDebugIgnoreFocusLoss = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "ConfigDebugIniSettings") {
        io->ConfigDebugIniSettings = lua_get<bool>(L, 3);
        return 0;
    }
    if (key == "WantSaveIniSettings") {
        io->WantSaveIniSettings = lua_get<bool>(L, 3);
        return 0;
    }
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    if (key == "FontGlobalScale") {
        io->FontGlobalScale = lua_get<float>(L, 3);
        return 0;
    }
#endif

    return luaL_error(L, "Invalid ImGuiIO property: %s", key.c_str());
}

auto lua_imgui_get_io(lua_State* L) -> int
{
    ImGuiIO& io = ImGui::GetIO();
    ImGuiIO** io_ptr = static_cast<ImGuiIO**>(lua_newuserdata(L, sizeof(ImGuiIO*)));
    *io_ptr = &io;
    luaL_getmetatable(L, "ImGuiIO");
    lua_setmetatable(L, -2);
    return 1;
}



void register_ImGuiIO(lua_State* L) {
    luaL_newmetatable(L, "ImGuiIO");

    lua_pushcfunction(L, lua_io_index);
    lua_setfield(L, -2, "__index");

    lua_pushcfunction(L, lua_io_newindex);
    lua_setfield(L, -2, "__newindex");

    lua_pop(L, 1);

    lua_getglobal(L, "ImGui");

    lua_pushcfunction(L, lua_imgui_get_io);
    lua_setfield(L, -2, "GetIO");

    lua_pop(L, 1);
}

void register_ImFontAtlas(lua_State* L) {
    luaL_newmetatable(L, "ImFontAtlas");

    lua_pushcfunction(L, lua_fontatlas_index);
    lua_setfield(L, -2, "__index");

    lua_pushcfunction(L, lua_fontatlas_newindex);
    lua_setfield(L, -2, "__newindex");

    lua_pop(L, 1);
}

void register_ImFont(lua_State* L) {
    luaL_newmetatable(L, "ImFont");

    lua_pushcfunction(L, lua_font_index);
    lua_setfield(L, -2, "__index");

    lua_pushcfunction(L, lua_font_newindex);
    lua_setfield(L, -2, "__newindex");

    lua_pop(L, 1);
}