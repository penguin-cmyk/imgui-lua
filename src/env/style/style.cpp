//
// Created by sigma on 10/08/2025.
//

#include "style.h"

static int lua_imgui_colors_index(lua_State* L) {
    ImVec4** colors_ptr = (ImVec4**)luaL_checkudata(L, 1, "ImGuiColors");
    ImVec4* colors = *colors_ptr;
    int index = luaL_checkinteger(L, 2);

    if (index < 0 || index >= ImGuiCol_COUNT) {
        return luaL_error(L, "Color index out of range: %d (valid range: 0-%d)", index, ImGuiCol_COUNT - 1);
    }

    LUA_RETURN_IMVEC4(L, colors[index]);
}

static int lua_imgui_colors_newindex(lua_State* L) {
    ImVec4** colors_ptr = (ImVec4**)luaL_checkudata(L, 1, "ImGuiColors");
    ImVec4* colors = *colors_ptr;
    int index = luaL_checkinteger(L, 2);

    if (index < 0 || index >= ImGuiCol_COUNT) {
        return luaL_error(L, "Color index out of range: %d (valid range: 0-%d)", index, ImGuiCol_COUNT - 1);
    }

    luaL_checktype(L, 3, LUA_TTABLE);
    LUA_GET_IMVEC4(L, 3, colors[index]);

    return 0;
}

static int lua_imgui_style_index(lua_State* L) {
    ImGuiStyle** style_ptr = (ImGuiStyle**)luaL_checkudata(L, 1, "ImGuiStyle");
    ImGuiStyle* style = *style_ptr;
    std::string key = luaL_checkstring(L, 2);

    // Font scaling
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

    // Alpha
    if (key == "Alpha") {
        lua_pushnumber(L, style->Alpha);
        return 1;
    }
    if (key == "DisabledAlpha") {
        lua_pushnumber(L, style->DisabledAlpha);
        return 1;
    }

    // Window
    if (key == "WindowPadding") {
        LUA_RETURN_IMVEC2(L, style->WindowPadding);
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
        LUA_RETURN_IMVEC2(L, style->WindowMinSize);
    }
    if (key == "WindowTitleAlign") {
        LUA_RETURN_IMVEC2(L, style->WindowTitleAlign);
    }
    if (key == "WindowMenuButtonPosition") {
        lua_pushinteger(L, style->WindowMenuButtonPosition);
        return 1;
    }

    // Child
    if (key == "ChildRounding") {
        lua_pushnumber(L, style->ChildRounding);
        return 1;
    }
    if (key == "ChildBorderSize") {
        lua_pushnumber(L, style->ChildBorderSize);
        return 1;
    }

    // Popup
    if (key == "PopupRounding") {
        lua_pushnumber(L, style->PopupRounding);
        return 1;
    }
    if (key == "PopupBorderSize") {
        lua_pushnumber(L, style->PopupBorderSize);
        return 1;
    }

    // Frame
    if (key == "FramePadding") {
        LUA_RETURN_IMVEC2(L, style->FramePadding);
    }
    if (key == "FrameRounding") {
        lua_pushnumber(L, style->FrameRounding);
        return 1;
    }
    if (key == "FrameBorderSize") {
        lua_pushnumber(L, style->FrameBorderSize);
        return 1;
    }

    // Spacing
    if (key == "ItemSpacing") {
        LUA_RETURN_IMVEC2(L, style->ItemSpacing);
    }
    if (key == "ItemInnerSpacing") {
        LUA_RETURN_IMVEC2(L, style->ItemInnerSpacing);
    }
    if (key == "CellPadding") {
        LUA_RETURN_IMVEC2(L, style->CellPadding);
    }
    if (key == "TouchExtraPadding") {
        LUA_RETURN_IMVEC2(L, style->TouchExtraPadding);
    }
    if (key == "IndentSpacing") {
        lua_pushnumber(L, style->IndentSpacing);
        return 1;
    }
    if (key == "ColumnsMinSpacing") {
        lua_pushnumber(L, style->ColumnsMinSpacing);
        return 1;
    }

    // Scrollbar
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

    // Image
    if (key == "ImageBorderSize") {
        lua_pushnumber(L, style->ImageBorderSize);
        return 1;
    }

    // Tab
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

    // Table
    if (key == "TableAngledHeadersAngle") {
        lua_pushnumber(L, style->TableAngledHeadersAngle);
        return 1;
    }
    if (key == "TableAngledHeadersTextAlign") {
        LUA_RETURN_IMVEC2(L, style->TableAngledHeadersTextAlign);
    }

    // Tree
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

    // Color button
    if (key == "ColorButtonPosition") {
        lua_pushinteger(L, style->ColorButtonPosition);
        return 1;
    }

    // Text alignment
    if (key == "ButtonTextAlign") {
        LUA_RETURN_IMVEC2(L, style->ButtonTextAlign);
    }
    if (key == "SelectableTextAlign") {
        LUA_RETURN_IMVEC2(L, style->SelectableTextAlign);
    }

    // Separator
    if (key == "SeparatorTextBorderSize") {
        lua_pushnumber(L, style->SeparatorTextBorderSize);
        return 1;
    }
    if (key == "SeparatorTextAlign") {
        LUA_RETURN_IMVEC2(L, style->SeparatorTextAlign);
    }
    if (key == "SeparatorTextPadding") {
        LUA_RETURN_IMVEC2(L, style->SeparatorTextPadding);
    }

    // Display
    if (key == "DisplayWindowPadding") {
        LUA_RETURN_IMVEC2(L, style->DisplayWindowPadding);
    }
    if (key == "DisplaySafeAreaPadding") {
        LUA_RETURN_IMVEC2(L, style->DisplaySafeAreaPadding);
    }

    // Mouse
    if (key == "MouseCursorScale") {
        lua_pushnumber(L, style->MouseCursorScale);
        return 1;
    }

    // Anti-aliasing
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

    // Tessellation
    if (key == "CurveTessellationTol") {
        lua_pushnumber(L, style->CurveTessellationTol);
        return 1;
    }
    if (key == "CircleTessellationMaxError") {
        lua_pushnumber(L, style->CircleTessellationMaxError);
        return 1;
    }

    // Colors array
    if (key == "Colors") {
        lua_push_imgui_colors(L, style->Colors);
        return 1;
    }

    // Behaviors
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
    ImGuiStyle** style_ptr = (ImGuiStyle**)luaL_checkudata(L, 1, "ImGuiStyle");
    ImGuiStyle* style = *style_ptr;
    std::string key = luaL_checkstring(L, 2);

    // Font scaling
    if (key == "FontSizeBase") {
        style->FontSizeBase = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "FontScaleMain") {
        style->FontScaleMain = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "FontScaleDpi") {
        style->FontScaleDpi = (float)luaL_checknumber(L, 3);
        return 0;
    }

    // Alpha
    if (key == "Alpha") {
        style->Alpha = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "DisabledAlpha") {
        style->DisabledAlpha = (float)luaL_checknumber(L, 3);
        return 0;
    }

    // Window
    if (key == "WindowPadding") {
        luaL_checktype(L, 3, LUA_TTABLE);
        LUA_GET_IMVEC2(L, 3, style->WindowPadding);
        return 0;
    }
    if (key == "WindowRounding") {
        style->WindowRounding = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "WindowBorderSize") {
        style->WindowBorderSize = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "WindowBorderHoverPadding") {
        style->WindowBorderHoverPadding = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "WindowMinSize") {
        luaL_checktype(L, 3, LUA_TTABLE);
        LUA_GET_IMVEC2(L, 3, style->WindowMinSize);
        return 0;
    }
    if (key == "WindowTitleAlign") {
        luaL_checktype(L, 3, LUA_TTABLE);
        LUA_GET_IMVEC2(L, 3, style->WindowTitleAlign);
        return 0;
    }
    if (key == "WindowMenuButtonPosition") {
        style->WindowMenuButtonPosition = (ImGuiDir)luaL_checkinteger(L, 3);
        return 0;
    }

    // Child
    if (key == "ChildRounding") {
        style->ChildRounding = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "ChildBorderSize") {
        style->ChildBorderSize = (float)luaL_checknumber(L, 3);
        return 0;
    }

    // Popup
    if (key == "PopupRounding") {
        style->PopupRounding = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "PopupBorderSize") {
        style->PopupBorderSize = (float)luaL_checknumber(L, 3);
        return 0;
    }

    // Frame
    if (key == "FramePadding") {
        luaL_checktype(L, 3, LUA_TTABLE);
        LUA_GET_IMVEC2(L, 3, style->FramePadding);
        return 0;
    }
    if (key == "FrameRounding") {
        style->FrameRounding = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "FrameBorderSize") {
        style->FrameBorderSize = (float)luaL_checknumber(L, 3);
        return 0;
    }

    // Spacing
    if (key == "ItemSpacing") {
        luaL_checktype(L, 3, LUA_TTABLE);
        LUA_GET_IMVEC2(L, 3, style->ItemSpacing);
        return 0;
    }
    if (key == "ItemInnerSpacing") {
        luaL_checktype(L, 3, LUA_TTABLE);
        LUA_GET_IMVEC2(L, 3, style->ItemInnerSpacing);
        return 0;
    }
    if (key == "CellPadding") {
        luaL_checktype(L, 3, LUA_TTABLE);
        LUA_GET_IMVEC2(L, 3, style->CellPadding);
        return 0;
    }
    if (key == "TouchExtraPadding") {
        luaL_checktype(L, 3, LUA_TTABLE);
        LUA_GET_IMVEC2(L, 3, style->TouchExtraPadding);
        return 0;
    }
    if (key == "IndentSpacing") {
        style->IndentSpacing = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "ColumnsMinSpacing") {
        style->ColumnsMinSpacing = (float)luaL_checknumber(L, 3);
        return 0;
    }

    // Scrollbar
    if (key == "ScrollbarSize") {
        style->ScrollbarSize = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "ScrollbarRounding") {
        style->ScrollbarRounding = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "GrabMinSize") {
        style->GrabMinSize = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "GrabRounding") {
        style->GrabRounding = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "LogSliderDeadzone") {
        style->LogSliderDeadzone = (float)luaL_checknumber(L, 3);
        return 0;
    }

    // Continue with remaining properties...
    if (key == "ImageBorderSize") {
        style->ImageBorderSize = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "TabRounding") {
        style->TabRounding = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "TabBorderSize") {
        style->TabBorderSize = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "TabCloseButtonMinWidthSelected") {
        style->TabCloseButtonMinWidthSelected = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "TabCloseButtonMinWidthUnselected") {
        style->TabCloseButtonMinWidthUnselected = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "TabBarBorderSize") {
        style->TabBarBorderSize = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "TabBarOverlineSize") {
        style->TabBarOverlineSize = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "TableAngledHeadersAngle") {
        style->TableAngledHeadersAngle = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "TableAngledHeadersTextAlign") {
        luaL_checktype(L, 3, LUA_TTABLE);
        LUA_GET_IMVEC2(L, 3, style->TableAngledHeadersTextAlign);
        return 0;
    }
    if (key == "TreeLinesFlags") {
        style->TreeLinesFlags = (ImGuiTreeNodeFlags)luaL_checkinteger(L, 3);
        return 0;
    }
    if (key == "TreeLinesSize") {
        style->TreeLinesSize = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "TreeLinesRounding") {
        style->TreeLinesRounding = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "ColorButtonPosition") {
        style->ColorButtonPosition = (ImGuiDir)luaL_checkinteger(L, 3);
        return 0;
    }
    if (key == "ButtonTextAlign") {
        luaL_checktype(L, 3, LUA_TTABLE);
        LUA_GET_IMVEC2(L, 3, style->ButtonTextAlign);
        return 0;
    }
    if (key == "SelectableTextAlign") {
        luaL_checktype(L, 3, LUA_TTABLE);
        LUA_GET_IMVEC2(L, 3, style->SelectableTextAlign);
        return 0;
    }
    if (key == "SeparatorTextBorderSize") {
        style->SeparatorTextBorderSize = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "SeparatorTextAlign") {
        luaL_checktype(L, 3, LUA_TTABLE);
        LUA_GET_IMVEC2(L, 3, style->SeparatorTextAlign);
        return 0;
    }
    if (key == "SeparatorTextPadding") {
        luaL_checktype(L, 3, LUA_TTABLE);
        LUA_GET_IMVEC2(L, 3, style->SeparatorTextPadding);
        return 0;
    }
    if (key == "DisplayWindowPadding") {
        luaL_checktype(L, 3, LUA_TTABLE);
        LUA_GET_IMVEC2(L, 3, style->DisplayWindowPadding);
        return 0;
    }
    if (key == "DisplaySafeAreaPadding") {
        luaL_checktype(L, 3, LUA_TTABLE);
        LUA_GET_IMVEC2(L, 3, style->DisplaySafeAreaPadding);
        return 0;
    }
    if (key == "MouseCursorScale") {
        style->MouseCursorScale = (float)luaL_checknumber(L, 3);
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
        style->CurveTessellationTol = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "CircleTessellationMaxError") {
        style->CircleTessellationMaxError = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "HoverStationaryDelay") {
        style->HoverStationaryDelay = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "HoverDelayShort") {
        style->HoverDelayShort = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "HoverDelayNormal") {
        style->HoverDelayNormal = (float)luaL_checknumber(L, 3);
        return 0;
    }
    if (key == "HoverFlagsForTooltipMouse") {
        style->HoverFlagsForTooltipMouse = (ImGuiHoveredFlags)luaL_checkinteger(L, 3);
        return 0;
    }
    if (key == "HoverFlagsForTooltipNav") {
        style->HoverFlagsForTooltipNav = (ImGuiHoveredFlags)luaL_checkinteger(L, 3);
        return 0;
    }

    return luaL_error(L, "Unknown or read-only ImGuiStyle property: %s", key.c_str());
}



static int lua_push_imgui_style(lua_State* L, ImGuiStyle* style) {
    ImGuiStyle** udata = (ImGuiStyle**)lua_newuserdata(L, sizeof(ImGuiStyle*));
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
    ImVec4** udata = (ImVec4**)lua_newuserdata(L, sizeof(ImVec4*));
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
    ImGuiStyle** style_ptr = (ImGuiStyle**)luaL_checkudata(L, 1, "ImGuiStyle");
    ImGuiStyle* style = *style_ptr;
    float scale_factor = (float)luaL_checknumber(L, 2);

    style->ScaleAllSizes(scale_factor);
    return 0;
}

void registerImGuiStyle(lua_State* L) {
    lua_getglobal(L, "ImGui");

    lua_pushcfunction(L, lua_imgui_get_style);
    lua_setfield(L, -2, "GetStyle");

    lua_pushcfunction(L, lua_imgui_style_scale_all_sizes);
    lua_setfield(L, -2, "ScaleAllSizes");
    lua_pop(L, 1);
}
