//
// Created by sigma on 10/08/2025.
//

#include <vector>
#include <iostream>
#include <unordered_map>
#include "ui.h"

// General
static int SetNextWindowPos(lua_State* L) {
    auto x = (float) luaL_optnumber(L, 2, 0.0);
    auto y = (float) luaL_optnumber(L, 3, 0.0);

    ImGui::SetNextWindowPos({ x, y });
    return 0;
}

static int SetNextWindowSize(lua_State* L) {
    auto width  = (float) luaL_optnumber(L, 2, gui::WIDTH);
    auto height = (float) luaL_optnumber(L, 3, gui::HEIGHT);

    ImGui::SetNextWindowSize({ width, height });
    return 0;
}

static int Begin(lua_State* L) {
    int defaultFlags = ImGuiWindowFlags_NoResize |
                       ImGuiWindowFlags_NoSavedSettings |
                       ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoMove;

    auto name = luaL_checkstring(L, 2);
    auto flags = (int) luaL_optinteger(L, 3, defaultFlags);

    bool success = ImGui::Begin(name, &gui::isRunning, flags);
    LUA_RET_BOOL(success);
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// Buttons

static int Button(lua_State* L) {
    auto name = luaL_checkstring(L, 2);
    ImVec2 size;
    LUA_GET_IMVEC2(L, 3, size);


    bool clicked = ImGui::Button( name, size );
    LUA_RET_BOOL(clicked);
}

static int InvisibleButton(lua_State* L) {
    auto name = luaL_checkstring(L, 2);
    ImVec2 size;
    LUA_GET_IMVEC2(L, 3, size);
    int flags = (int) luaL_optnumber(L, 4, 0);

    auto clicked = ImGui::InvisibleButton(name, size, flags);
    LUA_RET_BOOL(clicked);
}

// TODO: Add dir types

static int ArrowButton(lua_State* L) {
    auto name = luaL_checkstring(L, 2);
    auto direction = (ImGuiDir) luaL_optnumber(L, 3, ImGuiDir_Right);

    auto clicked = ImGui::ArrowButton(name, direction);
    LUA_RET_BOOL(clicked);
}

static int Checkbox(lua_State* L) {
    auto name = luaL_checkstring(L, 2);
    bool value = lua_toboolean(L, 3);

    bool modifiedValue = value;

    ImGui::Checkbox(name, &modifiedValue);
    LUA_RET_BOOL(modifiedValue);
}

static int BeginPopupModal(lua_State* L) {
    auto name = luaL_checkstring(L, 2);
    bool open = lua_toboolean(L, 3);
    auto flags = (int) luaL_optnumber(L, 4, 0);

    auto isOpen = ImGui::BeginPopupModal(name, &open, flags);
    LUA_RET_BOOL(isOpen);
}

static int CheckboxFlags(lua_State* L) {
    auto name = luaL_checkstring(L, 2);
    auto flags = luaL_checknumber(L, 3);
    auto flags_value = (int) luaL_checknumber(L, 4);

    auto check = ImGui::CheckboxFlags(name, reinterpret_cast<int *>(&flags), flags_value);
    LUA_RET_BOOL(check);
}

static int RadioButton(lua_State* L) {
    auto name = luaL_checkstring(L, 2);
    bool value = lua_toboolean(L, 2);

    auto clicked = ImGui::RadioButton(name, value);
    LUA_RET_BOOL(clicked);
}

static int ProgressBar(lua_State* L) {
    auto fraction = (float) luaL_checknumber(L, 2);
    ImVec2 size;
    LUA_GET_IMVEC2(L, 3, size);
    auto overlay = luaL_checkstring(L, 4);

    ImGui::ProgressBar(fraction, size, overlay);
    return 0;
}

static int BeginTable(lua_State* L) {
    auto str_id = luaL_checkstring(L, 2);
    auto columns = (int) luaL_checknumber(L, 3);

    auto flags = (ImGuiTableFlags) luaL_optnumber(L, 4, 0);
    ImVec2 size;
    LUA_GET_IMVEC2(L, 5, size);
    auto inner_width = (float) luaL_optnumber(L, 6, 0.0);

    auto check = ImGui::BeginTable(str_id, columns, flags, size, inner_width);
    LUA_RET_BOOL(check);
}



static int TableNextRow(lua_State* L) {
    auto flags = (ImGuiTableRowFlags) luaL_optnumber(L, 2, 0);
    auto min_row_height = (float) luaL_optnumber(L, 3, 0);
    ImGui::TableNextRow(flags, min_row_height);
    return 0;
}


static std::unordered_map<std::string, std::string> g_inputBuffers;
static const luaL_Reg imguiFunctions[] = {
        // General stuff

        {"SetNextWindowPos", SetNextWindowPos},
        {"SetNextWindowSize", SetNextWindowSize},
        {"Begin", Begin},
        {"isRunning", [](lua_State *L) -> int {
            LUA_RET_BOOL(gui::isRunning);
        }},
        {"setIsRunning", [](lua_State *L) -> int {
            auto newState = (bool) luaL_checknumber(L, 2);
            gui::isRunning = newState;
            return 0;
        }},
        {"End", [](lua_State *L) -> int {
            ImGui::End();
            return 0;
        }},

        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////

        // Widgets: Main

        {"Button", Button},
        {"InvisibleButton", InvisibleButton},
        {"RadioButton", RadioButton},
        {"ArrowButton", ArrowButton},
        {"SmallButton", [](lua_State *L) -> int {
            auto name = luaL_checkstring(L, 2);

            bool clicked = ImGui::SmallButton( name );
            lua_pushboolean(L, clicked);
            return 1;
        }},

        {"Bullet", [](lua_State *L) -> int {
            ImGui::Bullet();
            return 0;
        }},

        {"Checkbox", Checkbox},
        {"CheckboxFlags", CheckboxFlags},

        {"ProgressBar", ProgressBar},

        {"TextLink", [](lua_State *L) -> int {
            auto name = luaL_checkstring(L, 2);
            auto clicked = ImGui::TextLink(name);

            lua_pushboolean(L, clicked);
            return clicked;
        }},
        {"TextLinkOpenURL", [](lua_State *L) -> int {
            auto name = luaL_checkstring(L, 2);
            auto url = luaL_checkstring(L, 3);

            auto clicked = ImGui::TextLinkOpenURL(name, url);

            lua_pushboolean(L, clicked);
            return clicked;
        }},

        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////

        // Layout
        {"SameLine", [](lua_State *L) -> int {
            auto offset_from_start_x = (float) luaL_optnumber(L, 2, 0.0);
            auto spacing = (float) luaL_optnumber(L, 3, -1);

            ImGui::SameLine(offset_from_start_x, spacing);
            return 0;
        }},
        {"Separator", voidReturn_noargs(ImGui::Separator)},
        {"NewLine", voidReturn_noargs(ImGui::NewLine)},
        {"Spacing", voidReturn_noargs(ImGui::Spacing)},
        {"BeginGroup", voidReturn_noargs(ImGui::BeginGroup)},
        {"EndGroup", voidReturn_noargs(ImGui::EndGroup)},
        {"AlignTextToFramePadding", voidReturn_noargs(ImGui::AlignTextToFramePadding)},

        {"GetTextLineHeight", floatReturn_noargs(ImGui::GetTextLineHeight)},
        {"GetTextLineHeightWithSpacing", floatReturn_noargs(ImGui::GetTextLineHeightWithSpacing)},
        {"GetFrameHeight", floatReturn_noargs(ImGui::GetFrameHeight)},
        {"GetFrameHeightWithSpacing", floatReturn_noargs(ImGui::GetFrameHeightWithSpacing)},

        {"Indent", floatReturn_args(ImGui::Indent, 0.0)},
        {"Unindent", floatReturn_args(ImGui::Unindent, 0.0)},
        {"Dummy", imVec2_args(ImGui::Dummy)},

        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////

        // Layout cursor positioning

        {"GetCursorPosX", floatReturn_noargs(ImGui::GetCursorPosX)},
        {"GetCursorPosY", floatReturn_noargs(ImGui::GetCursorPosY)},

        {"GetCursorPos", imVec2_noargs(ImGui::GetCursorPos)},
        {"GetContentRegionAvail", imVec2_noargs(ImGui::GetContentRegionAvail)},
        {"GetCursorScreenPos", imVec2_noargs(ImGui::GetCursorScreenPos)},
        {"GetCursorStartPos", imVec2_noargs(ImGui::GetCursorStartPos)},

        {"SetCursorScreenPos", imVec2_args(ImGui::SetCursorScreenPos)},
        {"SetCursorPos", imVec2_args(ImGui::SetCursorPos)},
        {"SetCursorPosX", floatReturn_args(ImGui::SetCursorPosX, 0)},
        {"SetCursorPosY", floatReturn_args(ImGui::SetCursorPosY, 0)},

        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////

        // Tables

        {"BeginTable", BeginTable},
        {"EndTable", voidReturn_noargs(ImGui::EndTable)},
        {"TableNextRow", TableNextRow},
        {"TableNextColumn", voidReturn_boolean(ImGui::TableNextColumn)},
        {"TableSetColumnIndex", intReturn_args(ImGui::TableSetColumnIndex, 0.0)},

        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////

        // Popups

        {"BeginPopup", popup_args_ret(ImGui::BeginPopup, 0)},
        {"BeginPopupModal", BeginPopupModal},
        {"EndPopup", voidReturn_noargs(ImGui::EndPopup)},

        {"OpenPopup", popup_args(ImGui::OpenPopup, 0)},
        {"OpenPopupOnItemClick", popup_args(ImGui::OpenPopupOnItemClick, 1)},
        {"CloseCurrentPopup", voidReturn_noargs(ImGui::CloseCurrentPopup)},

        {"BeginPopupContextItem", popup_args_ret(ImGui::BeginPopupContextItem, 1)},
        {"BeginPopupContextWindow", popup_args_ret(ImGui::BeginPopupContextWindow, 1)},
        {"BeginPopupContextVoid", popup_args_ret(ImGui::BeginPopupContextVoid, 1)},

        {"IsPopupOpen", popup_args_ret(ImGui::IsPopupOpen, 0)},

        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////

        // Tooltips next

        {"BeginTooltip", voidReturn_boolean(ImGui::BeginTooltip)},
        {"EndTooltip", voidReturn_noargs(ImGui::EndTooltip)},
        {"SetTooltip", char_args_fmt(ImGui::SetTooltip)},

        {"BeginItemTooltip", voidReturn_boolean(ImGui::BeginItemTooltip)},
        {"SetItemTooltip", char_args_fmt(ImGui::SetItemTooltip)},

        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////

        // Item/Widgets Utilities and Query Functions
        {"IsItemHovered", intReturn_boolean(ImGui::IsItemHovered, 0)},
        {"IsItemClicked", intReturn_boolean(ImGui::IsItemClicked, 0)},

        {"IsItemActive", voidReturn_boolean(ImGui::IsItemActive)},
        {"IsItemFocused", voidReturn_boolean(ImGui::IsItemFocused)},
        {"IsItemVisible", voidReturn_boolean(ImGui::IsItemVisible)},
        {"IsItemEdited", voidReturn_boolean(ImGui::IsItemEdited)},
        {"IsItemActivated", voidReturn_boolean(ImGui::IsItemActivated)},
        {"IsItemDeactivated", voidReturn_boolean(ImGui::IsItemDeactivated)},
        {"IsItemDeactivatedAfterEdit", voidReturn_boolean(ImGui::IsItemDeactivatedAfterEdit)},
        {"IsItemToggledOpen", voidReturn_boolean(ImGui::IsItemToggledOpen)},
        {"IsAnyItemHovered", voidReturn_boolean(ImGui::IsAnyItemHovered)},
        {"IsAnyItemActive", voidReturn_boolean(ImGui::IsAnyItemActive)},
        {"IsAnyItemFocused", voidReturn_boolean(ImGui::IsAnyItemFocused)},

        {"GetItemRectMin", imVec2_noargs(ImGui::GetItemRectMin)},
        {"GetItemRectMax", imVec2_noargs(ImGui::GetItemRectMax)},
        {"GetItemRectSize", imVec2_noargs(ImGui::GetItemRectSize)},

        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////

        // Clipboard

        {"SetClipboardText", char_args(ImGui::SetClipboardText)},
        {"GetClipboardText", char_noargs_ret(ImGui::GetClipboardText)},

        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////

        // Tabs
        {"EndTabBar", voidReturn_noargs(ImGui::EndTabBar)},
        {"EndTabItem", voidReturn_noargs(ImGui::EndTabItem)},
        {"SetTabItemClosed", char_args(ImGui::SetTabItemClosed)},
        {"BeginTabBar", popup_args_ret(ImGui::BeginTabBar, 0)},
        {"TabItemButton", popup_args_ret(ImGui::TabItemButton, 0)},
        {"BeginTabItem", [](lua_State *L) -> int {
            auto label = luaL_checkstring(L, 2);
            bool p_open = lua_toboolean(L, 3);
            auto flags = (ImGuiTabItemFlags) luaL_optnumber(L, 4, 0);

            auto selected = ImGui::BeginTabItem(label, &p_open, flags);
            LUA_RET_BOOL(selected);
        }},

        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////

        // Treenodes

        {"TreePush", char_args(ImGui::TreePush)},
        {"GetTreeNodeToLabelSpacing", floatReturn_noargs(ImGui::GetTreeNodeToLabelSpacing)},
        {"TreePop", voidReturn_noargs(ImGui::TreePop)},

        {"TreeNode",[](lua_State *L) -> int {
            auto str_id = luaL_checkstring(L, 2);
            auto other = luaL_checkstring(L, 3);

            auto open = ImGui::TreeNode(str_id, "%s", other);
            LUA_RET_BOOL(open);
        }},
        {"TreeNodeEx",[](lua_State *L) -> int {
            auto str_id = luaL_checkstring(L, 2);
            auto flags = (ImGuiTreeNodeFlags) luaL_checknumber(L, 3);
            auto other = luaL_checkstring(L, 4);

            auto open = ImGui::TreeNodeEx(str_id, flags, "%s", other);
            LUA_RET_BOOL(open);
        }},

        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////

        // Size
        {"IsWindowAppearing", voidReturn_boolean(ImGui::IsWindowAppearing)},
        {"IsWindowCollapsed", voidReturn_boolean(ImGui::IsWindowCollapsed)},
        {"IsWindowFocused", intReturn_boolean(ImGui::IsWindowFocused, 0)},
        {"IsWindowHovered", intReturn_boolean(ImGui::IsWindowHovered, 0)},
        {"GetWindowPos", imVec2_noargs(ImGui::GetWindowPos)},
        {"GetWindowSize", imVec2_noargs(ImGui::GetWindowSize)},
        {"GetWindowWidth", floatReturn_noargs(ImGui::GetWindowWidth)},
        {"GetWindowHeight", floatReturn_noargs(ImGui::GetWindowHeight)},

        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////

        // Text

        {"Text", char_args_fmt(ImGui::Text)},
        {"TextDisabled", char_args_fmt(ImGui::TextDisabled)},
        {"TextWrapped", char_args_fmt(ImGui::TextWrapped)},
        {"BulletText", char_args_fmt(ImGui::BulletText)},
        {"SeparatorText", char_args(ImGui::SeparatorText)},

        {"TextColored", [](lua_State *L) -> int {
            ImVec4 col;
            LUA_GET_IMVEC4(L, 2, col);

            const char* str = luaL_checkstring(L, 3);
            ImGui::TextColored(col, "%s", str);
            return 0;
        }},
        {"LabelText", [](lua_State *L) -> int {
            const char* label = luaL_checkstring(L, 2);
            const char* content = luaL_checkstring(L, 3);

            ImGui::LabelText(label, "%s", content);
            return 0;
        }},

        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////

        // Inputs

        {"InputText", [](lua_State *L) -> int {
            const char* label = luaL_checkstring(L, 2);
            const char* currentText = luaL_checkstring(L, 3);
            int bufSize = (int) (luaL_checknumber(L, 4));
            int flags = (int) (luaL_optnumber(L, 5, 0));

            std::string bufferId = std::string("input_") + label;

            if (g_inputBuffers.find(bufferId) == g_inputBuffers.end()) {
                g_inputBuffers[bufferId] = currentText;
            }

            g_inputBuffers[bufferId].resize(bufSize);

            bool changed = ImGui::InputText(label, &g_inputBuffers[bufferId][0], bufSize, flags);
            g_inputBuffers[bufferId].resize(strlen(g_inputBuffers[bufferId].c_str()));

            lua_pushstring(L, g_inputBuffers[bufferId].c_str());
            lua_pushboolean(L, changed);

            return 2;
        }},

        {"InputTextMultiline", [](lua_State *L) -> int {
            const char* label = luaL_checkstring(L, 2);
            const char* currentText = luaL_checkstring(L, 3);
            int bufSize = (int) (luaL_checknumber(L, 4));
            ImVec2 size;
            LUA_GET_IMVEC2(L, 5, size);
            int flags = (int) (luaL_optnumber(L, 6, 0));

            std::string bufferId = std::string("multiline_") + label;

            if (g_inputBuffers.find(bufferId) == g_inputBuffers.end()) {
                g_inputBuffers[bufferId] = currentText;
            }

            g_inputBuffers[bufferId].resize(bufSize);

            bool changed = ImGui::InputTextMultiline(label, &g_inputBuffers[bufferId][0], bufSize, size, flags);

            g_inputBuffers[bufferId].resize(strlen(g_inputBuffers[bufferId].c_str()));

            lua_pushstring(L, g_inputBuffers[bufferId].c_str());
            lua_pushboolean(L, changed);

            return 2;
        }},

        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////

        // Child frames
        {"BeginChildFrame", [](lua_State *L) -> int {
            auto id = (ImGuiID) luaL_checknumber(L, 2);
            ImVec2 size;
            LUA_GET_IMVEC2(L, 3, size);

            auto flags = (ImGuiWindowFlags) luaL_optnumber(L, 4, 0);

            auto ret = ImGui::BeginChildFrame(id, size, flags);
            lua_pushboolean(L, ret);
            return 1;
        }},
        {"EndChildFrame", voidReturn_noargs(ImGui::EndChildFrame)},

        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////

        // Color edit

        {"ColorEdit3", [](lua_State *L) -> int {
            LUA_COLOR3(ImGui::ColorEdit3)
            return 2;
        }},
        {"ColorPicker3", [](lua_State *L) -> int {
            LUA_COLOR3(ImGui::ColorPicker3)
            return 2;
        }},

        {"ColorEdit4", [](lua_State *L) -> int {
            LUA_COLOR4(ImGui::ColorEdit4)
            return 2;
        }},
        {"ColorPicker4", [](lua_State *L) -> int {
            LUA_COLOR4(ImGui::ColorPicker4)
            return 2;
        }},

        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////

        // Slider

        //  IMGUI_API bool          SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);     // adjust format to decorate the value with a prefix or a suffix for in-slider labels or unit display.

        {"Slider", [](lua_State *L) -> int {
            const char* label = luaL_checkstring(L, 2);
            float value = luaL_checknumber(L, 3);
            float value_min = luaL_checknumber(L, 4);
            float value_max = luaL_checknumber(L, 5);
            int flags = luaL_optnumber(L, 5, 0);

            float v = value;

            auto changed = ImGui::SliderFloat(label, &v, value_min, value_max, "%.3f", flags);
            lua_pushnumber(L, v);
            lua_pushboolean(L, changed);
            return 2;
        }},

        // TODO:
        // Inputs Utilities: Keyboard/Mouse/Gamepad
        // Sliders

        {NULL, NULL}
};

void registerImgui(lua_State* L) {
    luaL_newlib(L, imguiFunctions);

    lua_setglobal(L, "ImGui");
    lua_pop(L, 1);
}