#include "style.h"

static int lua_imgui_colors_index(lua_State* L) {
    auto** colors_ptr = static_cast<ImVec4 **>(luaL_checkudata(L, 1, "ImGuiColors"));
    if (!colors_ptr || !*colors_ptr) {
        return luaL_error(L, "Invalid ImGuiColors object");
    }
    const ImVec4* colors = *colors_ptr;
    const lua_Integer index = luaL_checkinteger(L, 2);

    if (index < 0 || index >= ImGuiCol_COUNT) {
        return luaL_error(L, "Color index out of range: %d (valid range: 0-%d)", index, ImGuiCol_COUNT - 1);
    }

    return lua_wrap<ImVec4>(L, [&]() {
        return colors[index];
    });
}

static int lua_imgui_colors_newindex(lua_State* L) {
    auto** colors_ptr = static_cast<ImVec4 **>(luaL_checkudata(L, 1, "ImGuiColors"));
    if (!colors_ptr || !*colors_ptr) {
        return luaL_error(L, "Invalid ImGuiColors object");
    }
    ImVec4* colors = *colors_ptr;
    const lua_Integer index = luaL_checkinteger(L, 2);

    if (index < 0 || index >= ImGuiCol_COUNT) {
        return luaL_error(L, "Color index out of range: %d (valid range: 0-%d)", index, ImGuiCol_COUNT - 1);
    }

    luaL_checktype(L, 3, LUA_TTABLE);
    colors[index] = lua_get<ImVec4>(L, 3);

    return 0;
}

static int lua_imgui_style_index(lua_State* L) {
    auto** style_ptr = static_cast<ImGuiStyle **>(luaL_checkudata(L, 1, "ImGuiStyle"));
    if (!style_ptr || !*style_ptr) {
        return luaL_error(L, "Invalid ImGuiStyle object");
    }
    ImGuiStyle* style = *style_ptr;
    const std::string key = luaL_checkstring(L, 2);

    if (key == "FontSizeBase") {
        lua_pushnumber(L, style->FontSizeBase);
        return 1;
    }
    if (key == "FontScaleMain") {
        lua_pushnumber(L, style->FontScaleMain);
        return 1;
    }
    if (key == "FontScaleDpi") {
        lua_pushnumber(L, style->FontScaleDpi);
        return 1;
    }

    if (key == "Alpha") {
        lua_pushnumber(L, style->Alpha);
        return 1;
    }
    if (key == "DisabledAlpha") {
        lua_pushnumber(L, style->DisabledAlpha);
        return 1;
    }

    if (key == "WindowPadding") {
        return lua_wrap<ImVec2>(L, [&]() {
            return style->WindowPadding;
        });
    }
    if (key == "WindowRounding") {
        lua_pushnumber(L, style->WindowRounding);
        return 1;
    }
    if (key == "WindowBorderSize") {
        lua_pushnumber(L, style->WindowBorderSize);
        return 1;
    }
    if (key == "WindowBorderHoverPadding") {
        lua_pushnumber(L, style->WindowBorderHoverPadding);
        return 1;
    }
    if (key == "WindowMinSize") {
        return lua_wrap<ImVec2>(L, [&]() {
            return style->WindowMinSize;
        });
    }
    if (key == "WindowTitleAlign") {
        return lua_wrap<ImVec2>(L, [&]() {
            return style->WindowTitleAlign;
        });
    }
    if (key == "WindowMenuButtonPosition") {
        lua_pushinteger(L, style->WindowMenuButtonPosition);
        return 1;
    }

    if (key == "ChildRounding") {
        lua_pushnumber(L, style->ChildRounding);
        return 1;
    }
    if (key == "ChildBorderSize") {
        lua_pushnumber(L, style->ChildBorderSize);
        return 1;
    }

    if (key == "PopupRounding") {
        lua_pushnumber(L, style->PopupRounding);
        return 1;
    }
    if (key == "PopupBorderSize") {
        lua_pushnumber(L, style->PopupBorderSize);
        return 1;
    }

    if (key == "FramePadding") {
        return lua_wrap<ImVec2>(L, [&]() {
            return style->FramePadding;
        });
    }
    if (key == "FrameRounding") {
        lua_pushnumber(L, style->FrameRounding);
        return 1;
    }
    if (key == "FrameBorderSize") {
        lua_pushnumber(L, style->FrameBorderSize);
        return 1;
    }

    if (key == "ItemSpacing") {
        return lua_wrap<ImVec2>(L, [&]() {
            return style->ItemSpacing;
        });
    }
    if (key == "ItemInnerSpacing") {
        return lua_wrap<ImVec2>(L, [&]() {
            return style->ItemInnerSpacing;
        });
    }
    if (key == "CellPadding") {
        return lua_wrap<ImVec2>(L, [&]() {
            return style->CellPadding;
        });
    }
    if (key == "TouchExtraPadding") {
        return lua_wrap<ImVec2>(L, [&]() {
            return style->TouchExtraPadding;
        });
    }
    if (key == "IndentSpacing") {
        lua_pushnumber(L, style->IndentSpacing);
        return 1;
    }
    if (key == "ColumnsMinSpacing") {
        lua_pushnumber(L, style->ColumnsMinSpacing);
        return 1;
    }

    if (key == "ScrollbarSize") {
        lua_pushnumber(L, style->ScrollbarSize);
        return 1;
    }
    if (key == "ScrollbarRounding") {
        lua_pushnumber(L, style->ScrollbarRounding);
        return 1;
    }
    if (key == "GrabMinSize") {
        lua_pushnumber(L, style->GrabMinSize);
        return 1;
    }
    if (key == "GrabRounding") {
        lua_pushnumber(L, style->GrabRounding);
        return 1;
    }
    if (key == "LogSliderDeadzone") {
        lua_pushnumber(L, style->LogSliderDeadzone);
        return 1;
    }

    if (key == "ImageBorderSize") {
        lua_pushnumber(L, style->ImageBorderSize);
        return 1;
    }

    if (key == "TabRounding") {
        lua_pushnumber(L, style->TabRounding);
        return 1;
    }
    if (key == "TabBorderSize") {
        lua_pushnumber(L, style->TabBorderSize);
        return 1;
    }
    if (key == "TabCloseButtonMinWidthSelected") {
        lua_pushnumber(L, style->TabCloseButtonMinWidthSelected);
        return 1;
    }
    if (key == "TabCloseButtonMinWidthUnselected") {
        lua_pushnumber(L, style->TabCloseButtonMinWidthUnselected);
        return 1;
    }
    if (key == "TabBarBorderSize") {
        lua_pushnumber(L, style->TabBarBorderSize);
        return 1;
    }
    if (key == "TabBarOverlineSize") {
        lua_pushnumber(L, style->TabBarOverlineSize);
        return 1;
    }

    if (key == "TableAngledHeadersAngle") {
        lua_pushnumber(L, style->TableAngledHeadersAngle);
        return 1;
    }
    if (key == "TableAngledHeadersTextAlign") {
        return lua_wrap<ImVec2>(L, [&]() {
            return style->TableAngledHeadersTextAlign;
        });
    }

    if (key == "TreeLinesFlags") {
        lua_pushinteger(L, style->TreeLinesFlags);
        return 1;
    }
    if (key == "TreeLinesSize") {
        lua_pushnumber(L, style->TreeLinesSize);
        return 1;
    }
    if (key == "TreeLinesRounding") {
        lua_pushnumber(L, style->TreeLinesRounding);
        return 1;
    }

    if (key == "ColorButtonPosition") {
        lua_pushinteger(L, style->ColorButtonPosition);
        return 1;
    }

    if (key == "ButtonTextAlign") {
        return lua_wrap<ImVec2>(L, [&]() {
            return style->ButtonTextAlign;
        });
    }
    if (key == "SelectableTextAlign") {
        return lua_wrap<ImVec2>(L, [&]() {
            return style->SelectableTextAlign;
        });
    }

    if (key == "SeparatorTextBorderSize") {
        lua_pushnumber(L, style->SeparatorTextBorderSize);
        return 1;
    }
    if (key == "SeparatorTextAlign") {
        return lua_wrap<ImVec2>(L, [&]() {
            return style->SeparatorTextAlign;
        });
    }
    if (key == "SeparatorTextPadding") {
        return lua_wrap<ImVec2>(L, [&]() {
            return style->SeparatorTextPadding;
        });
    }

    if (key == "DisplayWindowPadding") {
        return lua_wrap<ImVec2>(L, [&]() {
            return style->WindowPadding;
        });
    }
    if (key == "DisplaySafeAreaPadding") {
        return lua_wrap<ImVec2>(L, [&]() {
            return style->DisplaySafeAreaPadding;
        });
    }

    if (key == "MouseCursorScale") {
        lua_pushnumber(L, style->MouseCursorScale);
        return 1;
    }

    if (key == "AntiAliasedLines") {
        lua_pushboolean(L, style->AntiAliasedLines);
        return 1;
    }
    if (key == "AntiAliasedLinesUseTex") {
        lua_pushboolean(L, style->AntiAliasedLinesUseTex);
        return 1;
    }
    if (key == "AntiAliasedFill") {
        lua_pushboolean(L, style->AntiAliasedFill);
        return 1;
    }

    if (key == "CurveTessellationTol") {
        lua_pushnumber(L, style->CurveTessellationTol);
        return 1;
    }
    if (key == "CircleTessellationMaxError") {
        lua_pushnumber(L, style->CircleTessellationMaxError);
        return 1;
    }

    if (key == "Colors") {
        lua_push_imgui_colors(L, style->Colors);
        return 1;
    }

    if (key == "HoverStationaryDelay") {
        lua_pushnumber(L, style->HoverStationaryDelay);
        return 1;
    }
    if (key == "HoverDelayShort") {
        lua_pushnumber(L, style->HoverDelayShort);
        return 1;
    }
    if (key == "HoverDelayNormal") {
        lua_pushnumber(L, style->HoverDelayNormal);
        return 1;
    }
    if (key == "HoverFlagsForTooltipMouse") {
        lua_pushinteger(L, style->HoverFlagsForTooltipMouse);
        return 1;
    }
    if (key == "HoverFlagsForTooltipNav") {
        lua_pushinteger(L, style->HoverFlagsForTooltipNav);
        return 1;
    }

    return luaL_error(L, "Unknown ImGuiStyle property: %s", key.c_str());
}

static int lua_imgui_style_newindex(lua_State* L) {
    auto** style_ptr = static_cast<ImGuiStyle **>(luaL_checkudata(L, 1, "ImGuiStyle"));
    if (!style_ptr || !*style_ptr) {
        return luaL_error(L, "Invalid ImGuiStyle Object");
    }

    ImGuiStyle* style = *style_ptr;
    const std::string key = luaL_checkstring(L, 2);

    if (key == "FontSizeBase") {
        style->FontSizeBase = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "FontScaleMain") {
        style->FontScaleMain = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "FontScaleDpi") {
        style->FontScaleDpi = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }

    if (key == "Alpha") {
        style->Alpha = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "DisabledAlpha") {
        style->DisabledAlpha = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }

    if (key == "WindowPadding") {
        luaL_checktype(L, 3, LUA_TTABLE);
        style->WindowPadding = lua_get<ImVec2>(L, 3);
        return 0;
    }
    if (key == "WindowRounding") {
        style->WindowRounding = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "WindowBorderSize") {
        style->WindowBorderSize = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "WindowBorderHoverPadding") {
        style->WindowBorderHoverPadding = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "WindowMinSize") {
        luaL_checktype(L, 3, LUA_TTABLE);
        style->WindowMinSize = lua_get<ImVec2>(L, 3);
        return 0;
    }
    if (key == "WindowTitleAlign") {
        luaL_checktype(L, 3, LUA_TTABLE);
        style->WindowTitleAlign = lua_get<ImVec2>(L, 3);
        return 0;
    }
    if (key == "WindowMenuButtonPosition") {
        style->WindowMenuButtonPosition = static_cast<ImGuiDir>(luaL_checkinteger(L, 3));
        return 0;
    }

    if (key == "ChildRounding") {
        style->ChildRounding = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "ChildBorderSize") {
        style->ChildBorderSize = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }

    if (key == "PopupRounding") {
        style->PopupRounding = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "PopupBorderSize") {
        style->PopupBorderSize = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }

    if (key == "FramePadding") {
        luaL_checktype(L, 3, LUA_TTABLE);

        style->FramePadding = lua_get<ImVec2>(L, 3);
        return 0;
    }
    if (key == "FrameRounding") {
        style->FrameRounding = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "FrameBorderSize") {
        style->FrameBorderSize = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }

    if (key == "ItemSpacing") {
        luaL_checktype(L, 3, LUA_TTABLE);
        style->ItemSpacing = lua_get<ImVec2>(L, 3);
        return 0;
    }
    if (key == "ItemInnerSpacing") {
        luaL_checktype(L, 3, LUA_TTABLE);
        style->ItemInnerSpacing = lua_get<ImVec2>(L, 3);
        return 0;
    }
    if (key == "CellPadding") {
        luaL_checktype(L, 3, LUA_TTABLE);
        style->CellPadding = lua_get<ImVec2>(L, 3);
        return 0;
    }
    if (key == "TouchExtraPadding") {
        luaL_checktype(L, 3, LUA_TTABLE);
        style->TouchExtraPadding = lua_get<ImVec2>(L, 3);
        return 0;
    }
    if (key == "IndentSpacing") {
        style->IndentSpacing = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "ColumnsMinSpacing") {
        style->ColumnsMinSpacing = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }


    if (key == "ScrollbarSize") {
        style->ScrollbarSize = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "ScrollbarRounding") {
        style->ScrollbarRounding = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "GrabMinSize") {
        style->GrabMinSize = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "GrabRounding") {
        style->GrabRounding = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "LogSliderDeadzone") {
        style->LogSliderDeadzone = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }

    if (key == "ImageBorderSize") {
        style->ImageBorderSize = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "TabRounding") {
        style->TabRounding = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "TabBorderSize") {
        style->TabBorderSize = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "TabCloseButtonMinWidthSelected") {
        style->TabCloseButtonMinWidthSelected = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "TabCloseButtonMinWidthUnselected") {
        style->TabCloseButtonMinWidthUnselected = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "TabBarBorderSize") {
        style->TabBarBorderSize = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "TabBarOverlineSize") {
        style->TabBarOverlineSize = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "TableAngledHeadersAngle") {
        style->TableAngledHeadersAngle = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "TableAngledHeadersTextAlign") {
        luaL_checktype(L, 3, LUA_TTABLE);
        style->TableAngledHeadersTextAlign = lua_get<ImVec2>(L, 3);
        return 0;
    }
    if (key == "TreeLinesFlags") {
        style->TreeLinesFlags = static_cast<ImGuiTreeNodeFlags>(luaL_checkinteger(L, 3));
        return 0;
    }
    if (key == "TreeLinesSize") {
        style->TreeLinesSize = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "TreeLinesRounding") {
        style->TreeLinesRounding = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "ColorButtonPosition") {
        style->ColorButtonPosition = static_cast<ImGuiDir>(luaL_checkinteger(L, 3));
        return 0;
    }
    if (key == "ButtonTextAlign") {
        luaL_checktype(L, 3, LUA_TTABLE);
        style->ButtonTextAlign = lua_get<ImVec2>(L, 3);
        return 0;
    }
    if (key == "SelectableTextAlign") {
        luaL_checktype(L, 3, LUA_TTABLE);
        style->SelectableTextAlign = lua_get<ImVec2>(L, 3);
        return 0;
    }
    if (key == "SeparatorTextBorderSize") {
        style->SeparatorTextBorderSize = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "SeparatorTextAlign") {
        luaL_checktype(L, 3, LUA_TTABLE);
        style->SeparatorTextAlign = lua_get<ImVec2>(L, 3);
        return 0;
    }
    if (key == "SeparatorTextPadding") {
        luaL_checktype(L, 3, LUA_TTABLE);
        style->SeparatorTextPadding = lua_get<ImVec2>(L, 3);
        return 0;
    }
    if (key == "DisplayWindowPadding") {
        luaL_checktype(L, 3, LUA_TTABLE);
        style->DisplayWindowPadding = lua_get<ImVec2>(L, 3);
        return 0;
    }
    if (key == "DisplaySafeAreaPadding") {
        luaL_checktype(L, 3, LUA_TTABLE);
        style->DisplaySafeAreaPadding = lua_get<ImVec2>(L, 3);
        return 0;
    }
    if (key == "MouseCursorScale") {
        style->MouseCursorScale = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "AntiAliasedLines") {
        style->AntiAliasedLines = lua_toboolean(L, 3);
        return 0;
    }
    if (key == "AntiAliasedLinesUseTex") {
        style->AntiAliasedLinesUseTex = lua_toboolean(L, 3);
        return 0;
    }
    if (key == "AntiAliasedFill") {
        style->AntiAliasedFill = lua_toboolean(L, 3);
        return 0;
    }
    if (key == "CurveTessellationTol") {
        style->CurveTessellationTol = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "CircleTessellationMaxError") {
        style->CircleTessellationMaxError = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "HoverStationaryDelay") {
        style->HoverStationaryDelay = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "HoverDelayShort") {
        style->HoverDelayShort = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "HoverDelayNormal") {
        style->HoverDelayNormal = static_cast<float>(luaL_checknumber(L, 3));
        return 0;
    }
    if (key == "HoverFlagsForTooltipMouse") {
        style->HoverFlagsForTooltipMouse = static_cast<ImGuiHoveredFlags>(luaL_checkinteger(L, 3));
        return 0;
    }
    if (key == "HoverFlagsForTooltipNav") {
        style->HoverFlagsForTooltipNav = static_cast<ImGuiHoveredFlags>(luaL_checkinteger(L, 3));
        return 0;
    }

    return luaL_error(L, "Unknown or read-only ImGuiStyle property: %s", key.c_str());
}



static int lua_push_imgui_style(lua_State* L, ImGuiStyle* style) {
    if (!style) {
        return luaL_error(L, "attempt to push null ImGuiStyle");
    }

    auto** udata = static_cast<ImGuiStyle **>(lua_newuserdata(L, sizeof(ImGuiStyle *)));
    *udata = style;

    if (luaL_newmetatable(L, "ImGuiStyle")) {
        lua_pushcfunction(L, lua_imgui_style_index);
        lua_setfield(L, -2, "__index");

        lua_pushcfunction(L, lua_imgui_style_newindex);
        lua_setfield(L, -2, "__newindex");
    }

    lua_setmetatable(L, -2);
    return 1;
}

static int lua_push_imgui_colors(lua_State* L, ImVec4* colors) {
    if (!colors) {
        return luaL_error(L, "attempt to push null ImVec4 array");
    }

    auto** udata = static_cast<ImVec4**>(lua_newuserdata(L, sizeof(ImVec4*)));
    *udata = colors;

    if (luaL_newmetatable(L, "ImGuiColors")) {
        lua_pushcfunction(L, lua_imgui_colors_index);
        lua_setfield(L, -2, "__index");

        lua_pushcfunction(L, lua_imgui_colors_newindex);
        lua_setfield(L, -2, "__newindex");
    }

    lua_setmetatable(L, -2);
    return 1;
}



static int lua_imgui_get_style(lua_State* L) {
    ImGuiStyle& style = ImGui::GetStyle();
    lua_push_imgui_style(L, &style);
    return 1;
}

static int lua_imgui_style_scale_all_sizes(lua_State* L) {
    auto** style_ptr = static_cast<ImGuiStyle **>(luaL_checkudata(L, 1, "ImGuiStyle"));
    if (!style_ptr) {
        return luaL_error(L, "attempt to push null ImGuiStyle");
    }
    ImGuiStyle* style = *style_ptr;
    auto scale_factor = static_cast<float>(luaL_checknumber(L, 2));

    style->ScaleAllSizes(scale_factor);
    return 0;
}

void register_ImGuiStyle(lua_State*L) {
    lua_getglobal(L, "ImGui");

    lua_pushcfunction(L, lua_imgui_get_style);
    lua_setfield(L, -2, "GetStyle");

    lua_pushcfunction(L, lua_imgui_style_scale_all_sizes);
    lua_setfield(L, -2, "ScaleAllSizes");

    lua_pop(L, 1);
}
