#ifndef MAIN_HPP
#define MAIN_HPP


#include "env/wrapper.hpp"
#include "env/font/font.h"

inline void lua_push_imvec4(lua_State* L, const float* arr) {
    lua_newtable(L);
    lua_pushnumber(L, arr[0]); lua_setfield(L, -2, "x");
    lua_pushnumber(L, arr[1]); lua_setfield(L, -2, "y");
    lua_pushnumber(L, arr[2]); lua_setfield(L, -2, "z");
    lua_pushnumber(L, arr[3]); lua_setfield(L, -2, "w");
}

static const luaL_Reg imGuiFunctions[] = {
    {"Begin", [](lua_State* L) -> int
    {
        constexpr int defaultFlags = ImGuiWindowFlags_NoResize |
                                     ImGuiWindowFlags_NoSavedSettings |
                                     ImGuiWindowFlags_NoCollapse |
                                     ImGuiWindowFlags_NoMove;

        const auto name = lua_get<const char*>(L, 2);
        const auto flags = lua_get<int>(L, 3, defaultFlags);

        return lua_wrap<bool>(L, [&]() {
            return ImGui::Begin(name, nullptr, flags);
        });
    }},
    {"End", [](lua_State* L) -> int
    {
        return lua_wrap<void>(L, [&]() { ImGui::End(); });
    }},
    ////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    {"BeginTabBar", [](lua_State* L) -> int
    {
        const auto name = lua_get<const char*>(L, 2);
        const auto flags = lua_get<int>(L, 3);
        return lua_wrap<bool>(L, [&]() { return ImGui::BeginTabBar(name, flags); });
    }},
    {"EndTabBar", [](lua_State* L) -> int
    {
        return lua_wrap<void>(L, [&]() { ImGui::EndTabBar(); });
    }},
    {"BeginTabItem", [](lua_State* L) -> int
    {
        const auto name = lua_get<const char*>(L, 2);
        const auto p_open = lua_get<bool>(L, 3);
        const auto flags = lua_get<int>(L, 4);

        return lua_wrap<bool>(L, [&]() {
            bool copy_open = p_open;
            return ImGui::BeginTabItem(name, &copy_open, flags);
        });
    }},
    {"EndTabItem",[](lua_State* L) -> int
    {
        return lua_wrap<void>(L, [&]() { ImGui::EndTabItem(); });
    }},

    {"Button", [](lua_State* L) -> int
    {
        const auto name = lua_get<const char*>(L, 2);
        const auto size = lua_get<ImVec2>(L, 3);

        return lua_wrap<bool>(L, [&]() { return ImGui::Button(name, size); });
    }},
    {"InvisibleButton", [](lua_State* L) -> int
    {
        const auto name = lua_get<const char*>(L, 2);
        const auto size = lua_get<ImVec2>(L, 3);
        const auto flags = lua_get<int>(L, 4);

        return lua_wrap<bool>(L, [&]() { return ImGui::InvisibleButton(name, size, flags); });
    }},
    {"ArrowButton", [](lua_State* L) -> int
    {
        const auto name = lua_get<const char*>(L, 2);
        const auto direction = static_cast<ImGuiDir>(lua_get<int>(L, 3, ImGuiDir_Right));

        return lua_wrap<bool>(L, [&]() { return ImGui::ArrowButton(name, direction); });
    }},
    {"Checkbox", [](lua_State* L) -> int
    {
        const auto name = lua_get<const char*>(L, 2);
        auto value = lua_get<bool>(L, 3);

        bool changed = false;
        lua_wrap<void>(L, [&]() {
            changed = ImGui::Checkbox(name, &value);
        });

        lua_pushboolean(L, value);
        lua_pushboolean(L, changed);
        return 2;
    }},

    {"BeginPopupModal", [](lua_State* L) -> int
    {
        const auto name = lua_get<const char*>(L, 2);
        auto open = lua_get<bool>(L, 3);

        const auto flags = lua_get<int>(L, 4);
        return lua_wrap<bool>(L, [&]() { return ImGui::BeginPopupModal(name, &open, flags); });
    }},

    {"SetNextWindowPos", [](lua_State* L) -> int
    {
        const auto x = lua_get<float>(L, 2, 0);
        const auto y = lua_get<float>(L, 3, 0);

        return lua_wrap<void>(L, [&]() { ImGui::SetNextWindowPos({ x, y }); });
    }},

    {"SetNextWindowSize", [](lua_State* L) -> int
    {
        const auto height = lua_get<float>(L, 2, ImGui::GetWindowWidth());
        const auto width  = lua_get<float>(L, 3, ImGui::GetWindowHeight());

        return lua_wrap<void>(L, [&]() { ImGui::SetNextWindowSize({ height, width }); });
    }},
    {"SetNextWindowSizeConstraints", [](lua_State* L) -> int {
        const auto size_min = lua_get<ImVec2>(L, 2);
        const auto size_max = lua_get<ImVec2>(L, 3);

        return lua_wrap<void>(L, [&] { ImGui::SetNextWindowSizeConstraints(size_min, size_max); });
    }},
    {"SetNextWindowContentSize", [](lua_State* L) -> int {
        const auto size = lua_get<ImVec2>(L, 2);
        return lua_wrap<void>(L, [&] { ImGui::SetNextWindowContentSize(size); });
    }},
    {"SetNextWindowCollapsed", [](lua_State* L) -> int {
        const auto collapsed = lua_get<bool>(L, 2);
        const auto cond = lua_get<int>(L, 3);

        return lua_wrap<void>(L, [&]() { ImGui::SetNextWindowCollapsed(collapsed, cond); });
    }},
    {"SetNextWindowFocus", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::SetNextWindowFocus(); });
    }},
    {"SetNextWindowScroll", [](lua_State* L) -> int {
        const auto scroll = lua_get<ImVec2>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::SetNextWindowScroll(scroll); });
    }},
    {"SetNextWindowBgAlpha", [](lua_State* L) -> int {
        const auto alpha = lua_get<float>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::SetNextWindowBgAlpha(alpha); });
    }},
    {"SetWindowPos", [](lua_State* L) -> int {
        const auto pos = lua_get<ImVec2>(L, 2);
        const auto cond = lua_get<int>(L, 3);
        return lua_wrap<void>(L, [&]() { ImGui::SetWindowPos(pos, cond); });
    }},
    {"SetWindowSize", [](lua_State* L) -> int {
        const auto size = lua_get<ImVec2>(L, 2);
        const auto cond = lua_get<int>(L, 3);
        return lua_wrap<void>(L, [&]() { ImGui::SetWindowSize(size, cond); });
    }},

    {"GetScrollX", [](lua_State* L) -> int {
        return lua_wrap<float>(L, [&]() { return ImGui::GetScrollX(); });
    }},
    {"GetScrollY", [](lua_State* L) -> int {
        return lua_wrap<float>(L, [&]() { return ImGui::GetScrollY(); });
    }},
    {"GetScrollMaxX", [](lua_State* L) -> int {
        return lua_wrap<float>(L, [&]() { return ImGui::GetScrollMaxX(); });
    }},
    {"GetScrollMaxY", [](lua_State* L) -> int {
        return lua_wrap<float>(L, [&]() { return ImGui::GetScrollMaxY(); });
    }},
    {"SetScrollX", [](lua_State* L) -> int {
        const auto scroll_x = lua_get<float>(L, 2);
        return lua_wrap<void>(L, [&]() {
            ImGui::SetScrollX(scroll_x);
        });
    }},
    {"SetScrollY", [](lua_State* L) -> int {
        const auto scroll_y = lua_get<float>(L, 2);
        return lua_wrap<void>(L, [&]() {
            ImGui::SetScrollX(scroll_y);
        });
    }},
    {"SetScrollHereX", [](lua_State* L) -> int {
        const auto center_x_ratio = lua_get<float>(L, 2, 0.5);
        return lua_wrap<void>(L, [&]() {
            ImGui::SetScrollHereX(center_x_ratio);
        });
    }},
    {"SetScrollHereY", [](lua_State* L) -> int {
        const auto center_y_ratio = lua_get<float>(L, 2, 0.5);
        return lua_wrap<void>(L, [&]() {
            ImGui::SetScrollHereY(center_y_ratio);
        });
    }},
    {"SetScrollFromPosX", [](lua_State* L) -> int {
        const auto local_x  = lua_get<float>(L, 2);
        const auto center_x_ratio = lua_get<float>(L, 3, 0.5);

        return lua_wrap<void>(L, [&]() {
            ImGui::SetScrollFromPosX(local_x, center_x_ratio);
        });
    }},
    {"SetScrollFromPosY", [](lua_State* L) -> int {
        const auto local_y  = lua_get<float>(L, 2);
        const auto center_y_ratio = lua_get<float>(L, 3, 0.5);

        return lua_wrap<void>(L, [&]() {
            ImGui::SetScrollFromPosY(local_y, center_y_ratio);
        });
    }},
    {"PushStyleColor",[](lua_State* L) -> int {
        const auto idx = lua_get<int>(L, 2);
        const auto color = lua_get<ImColor>(L, 3);

        return lua_wrap<void>(L, [&]() {
            const ImU32 c_converted = ImGui::ColorConvertFloat4ToU32(color.Value);
            ImGui::PushStyleColor(idx, c_converted);
        });
    }},
    {"PopStyleColor", [](lua_State* L) -> int {
        const auto idx  = lua_get<int>(L, 2, 1);

        return lua_wrap<void>(L, [&]() { ImGui::PopStyleColor(idx); });
    }},
    {"PushStyleVar", [](lua_State* L) -> int {
        const auto idx  = lua_get<int>(L, 2, 1);
        const auto val = lua_get<ImVec2>(L, 3);

        return lua_wrap<void>(L, [&]() { ImGui::PushStyleVar(idx, val); });
    }},
    {"PopStyleVar", [](lua_State* L) -> int {
        const auto idx  = lua_get<int>(L, 2, 1);

        return lua_wrap<void>(L, [&]() { ImGui::PopStyleVar(idx); });
    }},
    {"PushItemFlag", [](lua_State* L) -> int {
        const auto option  = lua_get<int>(L, 2);
        const auto enabled = lua_get<bool>(L, 3);

        return lua_wrap<void>(L, [&]() { ImGui::PushItemFlag(option, enabled); });
    }},
    {"PopItemFlag", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::PopItemFlag(); });
    }},

    {"PushItemWidth", [](lua_State* L) -> int {
        const auto item_width  = lua_get<float>(L, 2, 1);
        return lua_wrap<void>(L, [&]() { ImGui::PushItemWidth(item_width); });
    }},
    {"PopItemWidth", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::PopItemWidth(); });
    }},
    {"SetNextItemWidth", [](lua_State* L) -> int {
        const auto item_width  = lua_get<float>(L, 2, 1);
        return lua_wrap<void>(L, [&]() { ImGui::SetNextItemWidth(item_width); });
    }},
    {"CalcItemWidth", [](lua_State* L) -> int {
        return lua_wrap<float>(L, [&]() { return ImGui::CalcItemWidth(); });
    }},
    {"PushTextWrapPos", [](lua_State* L) -> int {
        const auto wrap_local_pos_x  = lua_get<float>(L, 2, 1);
        return lua_wrap<void>(L, [&]() { ImGui::PushTextWrapPos(wrap_local_pos_x); });
    }},
    {"PopTextWrapPos", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::PopTextWrapPos(); });
    }},
    {"GetFontTexUvWhitePixel", [](lua_State* L) -> int {
        return lua_wrap<ImVec2>(L, [&]() { return ImGui::GetFontTexUvWhitePixel(); });
    }},
    {"ColorConvertFloat4ToU32", [](lua_State* L) -> int {
        const auto color = lua_get<ImColor>(L, 2);
        return lua_wrap<float>(L, [&]() {
            return ImGui::ColorConvertFloat4ToU32(color.Value);
        });
    }},
    {"GetColorU32", [](lua_State* L) -> int {
        const auto idx = lua_get<int>(L, 2);
        const auto alpha_mul = lua_get<float>(L, 3);

        return lua_wrap<int>(L, [&]() { return ImGui::GetColorU32(idx, alpha_mul); });
    }},
    {"GetStyleColorVec4", [](lua_State* L) -> int {
        const auto idx = lua_get<int>(L, 2);
        return lua_wrap<ImVec4>(L, [&]() { return ImGui::GetStyleColorVec4(idx); });
    }},

    {"GetCursorScreenPos", [](lua_State* L) -> int {
        return lua_wrap<ImVec2>(L, [&]() { return ImGui::GetCursorScreenPos(); });
    }},
    {"SetCursorScreenPos", [](lua_State* L) -> int {
        const auto pos = lua_get<ImVec2>(L, 2);
        return lua_wrap<void>(L, [&]() {  ImGui::SetCursorScreenPos(pos); });
    }},
    {"GetContentRegionAvail", [](lua_State* L) -> int {
        return lua_wrap<ImVec2>(L, [&]() { return ImGui::GetContentRegionAvail(); });
    }},
    {"GetCursorPos", [](lua_State* L) -> int {
        return lua_wrap<ImVec2>(L, [&]() { return ImGui::GetCursorPos(); });
    }},
    {"GetCursorPosX", [](lua_State* L) -> int {
        return lua_wrap<float>(L, [&]() { return ImGui::GetCursorPosX(); });
    }},
    {"GetCursorPosY", [](lua_State* L) -> int {
        return lua_wrap<float>(L, [&]() { return ImGui::GetCursorPosY(); });
    }},
    {"SetCursorPos", [](lua_State* L) -> int {
        const auto pos = lua_get<ImVec2>(L, 2);
        return lua_wrap<void>(L, [&]() {  ImGui::SetCursorPos(pos); });
    }},
    {"SetCursorPosX", [](lua_State* L) -> int {
        const auto local_x = lua_get<float>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::SetCursorPosX(local_x); });
    }},
    {"SetCursorPosY", [](lua_State* L) -> int {
        const auto local_y = lua_get<float>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::SetCursorPosY(local_y); });
    }},
    {"GetCursorStartPos", [](lua_State* L) -> int {
        return lua_wrap<ImVec2>(L, [&]() { return ImGui::GetCursorStartPos(); });
    }},

    {"Separator", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { return ImGui::Separator(); });
    }},
    {"SameLine", [](lua_State* L) -> int {
        const auto offset_from_start_x = lua_get<float>(L, 2, 0);
        const auto spacing = lua_get<float>(L, 2, -1.0);

        return lua_wrap<void>(L, [&]() { ImGui::SameLine(offset_from_start_x, spacing); });
    }},
    {"NewLine", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::NewLine(); });
    }},
    {"Spacing", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::Spacing(); });
    }},
    {"Dummy", [](lua_State* L) -> int {
        const auto size = lua_get<ImVec2>(L, 2);

        return lua_wrap<void>(L, [&]() { ImGui::Dummy(size); });
    }},
    {"Indent", [](lua_State* L) -> int {
        const auto indent_w = lua_get<float>(L, 2);

        return lua_wrap<void>(L, [&]() { ImGui::Indent(indent_w); });
    }},
    {"Unindent", [](lua_State* L) -> int {
        const auto indent_w = lua_get<float>(L, 2);

        return lua_wrap<void>(L, [&]() { ImGui::Indent(indent_w); });
    }},


{"BeginGroup", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::BeginGroup(); });
    }},
    {"EndGroup", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::EndGroup(); });
    }},
    {"AlignTextToFramePadding", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::AlignTextToFramePadding(); });
    }},
    {"GetTextLineHeight", [](lua_State* L) -> int {
        return lua_wrap<float>(L, [&]() { return ImGui::GetTextLineHeight(); });
    }},
    {"GetTextLineHeightWithSpacing", [](lua_State* L) -> int {
        return lua_wrap<float>(L, [&]() { return ImGui::GetTextLineHeightWithSpacing(); });
    }},
    {"GetFrameHeight", [](lua_State* L) -> int {
        return lua_wrap<float>(L, [&]() { return ImGui::GetFrameHeight(); });
    }},
    {"GetFrameHeightWithSpacing", [](lua_State* L) -> int {
        return lua_wrap<float>(L, [&]() { return ImGui::GetFrameHeightWithSpacing(); });
    }},

    {"PushID", [](lua_State* L) -> int {
        const auto str_id = lua_get<const char*>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::PushID(str_id); });
    }},
    {"PopID", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::PopID(); });
    }},
    {"GetID", [](lua_State* L) -> int {
        const auto str_id = lua_get<const char*>(L, 2);
        return lua_wrap<ImGuiID>(L, [&]() { return ImGui::GetID(str_id); });
    }},

    {"TextUnformatted", [](lua_State* L) -> int {
        const auto text = lua_get<const char*>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::TextUnformatted(text); });
    }},
    {"Text", [](lua_State* L) -> int {
        const auto text = lua_get<const char*>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::Text("%s", text); });
    }},
    {"TextColored", [](lua_State* L) -> int {
        const auto col = lua_get<ImVec4>(L, 2);
        const auto text = lua_get<const char*>(L, 3);
        return lua_wrap<void>(L, [&]() { ImGui::TextColored(col, "%s", text); });
    }},
    {"TextDisabled", [](lua_State* L) -> int {
        const auto text = lua_get<const char*>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::TextDisabled("%s", text); });
    }},
    {"TextWrapped", [](lua_State* L) -> int {
        const auto text = lua_get<const char*>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::TextWrapped("%s", text); });
    }},
    {"LabelText", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        const auto text = lua_get<const char*>(L, 3);
        return lua_wrap<void>(L, [&]() { ImGui::LabelText(label, "%s", text); });
    }},
    {"BulletText", [](lua_State* L) -> int {
        const auto text = lua_get<const char*>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::BulletText("%s", text); });
    }},
    {"SeparatorText", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::SeparatorText(label); });
    }},

    {"SmallButton", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        return lua_wrap<bool>(L, [&]() { return ImGui::SmallButton(label); });
    }},
    {"RadioButton", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        const auto active = lua_get<bool>(L, 3);
        return lua_wrap<bool>(L, [&]() { return ImGui::RadioButton(label, active); });
    }},
    {"ProgressBar", [](lua_State* L) -> int {
        const auto fraction = lua_get<float>(L, 2);
        const auto size_arg = lua_get<ImVec2>(L, 3, ImVec2(-FLT_MIN, 0));
        const auto overlay = lua_get<const char*>(L, 4, nullptr);
        return lua_wrap<void>(L, [&]() { ImGui::ProgressBar(fraction, size_arg, overlay); });
    }},
    {"Bullet", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::Bullet(); });
    }},
    {"TextLink", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        return lua_wrap<bool>(L, [&]() { return ImGui::TextLink(label); });
    }},
    {"TextLinkOpenURL", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        const auto url = lua_get<const char*>(L, 3, nullptr);
        return lua_wrap<bool>(L, [&]() { return ImGui::TextLinkOpenURL(label, url); });
    }},

    {"BeginCombo", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        const auto preview_value = lua_get<const char*>(L, 3);
        const auto flags = lua_get<int>(L, 4, 0);
        return lua_wrap<bool>(L, [&]() { return ImGui::BeginCombo(label, preview_value, flags); });
    }},
    {"EndCombo", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::EndCombo(); });
    }},

    {"DragFloat", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        auto v = lua_get<float>(L, 3);
        const auto v_speed = lua_get<float>(L, 4, 1.0f);
        const auto v_min = lua_get<float>(L, 5, 0.0f);
        const auto v_max = lua_get<float>(L, 6, 0.0f);
        const auto format = lua_get<const char*>(L, 7, "%.3f");
        const auto flags = lua_get<int>(L, 8, 0);

        bool changed = false;
        lua_wrap<void>(L, [&]() {
            changed = ImGui::DragFloat(label, &v, v_speed, v_min, v_max, format, flags);
        });

        lua_pushnumber(L, v);
        lua_pushboolean(L, changed);
        return 2;
    }},
    {"DragInt", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        auto v = lua_get<int>(L, 3);
        const auto v_speed = lua_get<float>(L, 4, 1.0f);
        const auto v_min = lua_get<int>(L, 5, 0);
        const auto v_max = lua_get<int>(L, 6, 0);
        const auto format = lua_get<const char*>(L, 7, "%d");
        const auto flags = lua_get<int>(L, 8, 0);

        bool changed = false;
        lua_wrap<void>(L, [&]() {
            changed = ImGui::DragInt(label, &v, v_speed, v_min, v_max, format, flags);
        });

        lua_pushinteger(L, v);
        lua_pushboolean(L, changed);
        return 2;
    }},

    {"SliderFloat", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        auto v = lua_get<float>(L, 3);
        const auto v_min = lua_get<float>(L, 4);
        const auto v_max = lua_get<float>(L, 5);
        const auto format = lua_get<const char*>(L, 6, "%.3f");
        const auto flags = lua_get<int>(L, 7, 0);

        bool changed = false;
        lua_wrap<void>(L, [&]() {
            changed = ImGui::SliderFloat(label, &v, v_min, v_max, format, flags);
        });

        lua_pushnumber(L, v);
        lua_pushboolean(L, changed);
        return 2;
    }},
    {"SliderInt", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        auto v = lua_get<int>(L, 3);
        const auto v_min = lua_get<int>(L, 4);
        const auto v_max = lua_get<int>(L, 5);
        const auto format = lua_get<const char*>(L, 6, "%d");
        const auto flags = lua_get<int>(L, 7, 0);

        bool changed = false;
        lua_wrap<void>(L, [&]() {
            changed = ImGui::SliderInt(label, &v, v_min, v_max, format, flags);
        });

        lua_pushinteger(L, v);
        lua_pushboolean(L, changed);
        return 2;
    }},
    {"SliderAngle", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        auto v_rad = lua_get<float>(L, 3);
        const auto v_degrees_min = lua_get<float>(L, 4, -360.0f);
        const auto v_degrees_max = lua_get<float>(L, 5, +360.0f);
        const auto format = lua_get<const char*>(L, 6, "%.0f deg");
        const auto flags = lua_get<int>(L, 7, 0);

        bool changed = false;
        lua_wrap<void>(L, [&]() {
            changed = ImGui::SliderAngle(label, &v_rad, v_degrees_min, v_degrees_max, format, flags);
        });

        lua_pushnumber(L, v_rad);
        lua_pushboolean(L, changed);
        return 2;
    }},
    {"VSliderFloat", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        const auto size = lua_get<ImVec2>(L, 3);
        auto v = lua_get<float>(L, 4);
        const auto v_min = lua_get<float>(L, 5);
        const auto v_max = lua_get<float>(L, 6);
        const auto format = lua_get<const char*>(L, 7, "%.3f");
        const auto flags = lua_get<int>(L, 8, 0);

        bool changed = false;
        lua_wrap<void>(L, [&]() {
            changed = ImGui::VSliderFloat(label, size, &v, v_min, v_max, format, flags);
        });

        lua_pushnumber(L, v);
        lua_pushboolean(L, changed);
        return 2;
    }},
    {"VSliderInt", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        const auto size = lua_get<ImVec2>(L, 3);
        auto v = lua_get<int>(L, 4);
        const auto v_min = lua_get<int>(L, 5);
        const auto v_max = lua_get<int>(L, 6);
        const auto format = lua_get<const char*>(L, 7, "%d");
        const auto flags = lua_get<int>(L, 8, 0);

        bool changed = false;
        lua_wrap<void>(L, [&]() {
            changed = ImGui::VSliderInt(label, size, &v, v_min, v_max, format, flags);
        });

        lua_pushinteger(L, v);
        lua_pushboolean(L, changed);
        return 2;
    }},

    {"InputText", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        const auto text = lua_get<const char*>(L, 3);
        const auto buf_size = lua_get<size_t>(L, 4, 256);
        const auto flags = lua_get<int>(L, 5, 0);

        char* buffer = new char[buf_size];
        strncpy(buffer, text, buf_size - 1);
        buffer[buf_size - 1] = '\0';

        bool changed = ImGui::InputText(label, buffer, buf_size, flags);

        lua_pushstring(L, buffer);
        lua_pushboolean(L, changed);
        delete[] buffer;
        return 2;
    }},

    {"InputTextMultiline", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        const auto text = lua_get<const char*>(L, 3);
        const auto buf_size = lua_get<size_t>(L, 4, 256);
        const auto size = lua_get<ImVec2>(L, 5, ImVec2(0, 0));
        const auto flags = lua_get<int>(L, 6, 0);

        char* buffer = new char[buf_size];
        strncpy(buffer, text, buf_size - 1);
        buffer[buf_size - 1] = '\0';

        bool changed = ImGui::InputTextMultiline(label, buffer, buf_size, size, flags);

        lua_pushstring(L, buffer);
        lua_pushboolean(L, changed);
        delete[] buffer;
        return 2;
    }},

    {"InputTextWithHint", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        const auto hint = lua_get<const char*>(L, 3);
        const auto text = lua_get<const char*>(L, 4);
        const auto buf_size = lua_get<size_t>(L, 5, 256);
        const auto flags = lua_get<int>(L, 6, 0);

        char* buffer = new char[buf_size];
        strncpy(buffer, text, buf_size - 1);
        buffer[buf_size - 1] = '\0';

        bool changed = ImGui::InputTextWithHint(label, hint, buffer, buf_size, flags);

        lua_pushstring(L, buffer);
        lua_pushboolean(L, changed);
        delete[] buffer;
        return 2;
    }},
    {"InputFloat", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        auto v = lua_get<float>(L, 3);
        const auto step = lua_get<float>(L, 4, 0.0f);
        const auto step_fast = lua_get<float>(L, 5, 0.0f);
        const auto format = lua_get<const char*>(L, 6, "%.3f");
        const auto flags = lua_get<int>(L, 7, 0);

        bool changed = false;
        lua_wrap<void>(L, [&]() {
            changed = ImGui::InputFloat(label, &v, step, step_fast, format, flags);
        });

        lua_pushnumber(L, v);
        lua_pushboolean(L, changed);
        return 2;
    }},
    {"InputInt", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        auto v = lua_get<int>(L, 3);
        const auto step = lua_get<int>(L, 4, 1);
        const auto step_fast = lua_get<int>(L, 5, 100);
        const auto flags = lua_get<int>(L, 6, 0);

        bool changed = false;
        lua_wrap<void>(L, [&]() {
            changed = ImGui::InputInt(label, &v, step, step_fast, flags);
        });

        lua_pushinteger(L, v);
        lua_pushboolean(L, changed);
        return 2;
    }},
    {"InputDouble", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        auto v = lua_get<double>(L, 3);
        const auto step = lua_get<double>(L, 4, 0.0);
        const auto step_fast = lua_get<double>(L, 5, 0.0);
        const auto format = lua_get<const char*>(L, 6, "%.6f");
        const auto flags = lua_get<int>(L, 7, 0);

        bool changed = false;
        lua_wrap<void>(L, [&]() {
            changed = ImGui::InputDouble(label, &v, step, step_fast, format, flags);
        });

        lua_pushnumber(L, v);
        lua_pushboolean(L, changed);
        return 2;
    }},

    {"ColorEdit3", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        auto col = lua_get<ImVec4>(L, 3);
        const auto flags = lua_get<int>(L, 4, 0);

        float col_arr[4] = {col.x, col.y, col.z, col.w};
        bool changed = false;
        lua_wrap<void>(L, [&]() {
            changed = ImGui::ColorEdit3(label, col_arr, flags);
        });

        lua_push_imvec4(L, col_arr);
        lua_pushboolean(L, changed);
        return 2;
    }},
    {"ColorEdit4", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        auto col = lua_get<ImVec4>(L, 3);
        const auto flags = lua_get<int>(L, 4, 0);

        float col_arr[4] = {col.x, col.y, col.z, col.w};
        bool changed = false;
        lua_wrap<void>(L, [&]() {
            changed = ImGui::ColorEdit4(label, col_arr, flags);
        });

        lua_push_imvec4(L, col_arr);
        lua_pushboolean(L, changed);
        return 2;
    }},
    {"ColorPicker3", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        auto col = lua_get<ImVec4>(L, 3);
        const auto flags = lua_get<int>(L, 4, 0);

        float col_arr[4] = {col.x, col.y, col.z, col.w};
        bool changed = false;
        lua_wrap<void>(L, [&]() {
            changed = ImGui::ColorPicker3(label, col_arr, flags);
        });

        lua_push_imvec4(L, col_arr);
        lua_pushboolean(L, changed);
        return 2;
    }},
    {"ColorPicker4", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        auto col = lua_get<ImVec4>(L, 3);
        const auto flags = lua_get<int>(L, 4, 0);

        float col_arr[4] = {col.x, col.y, col.z, col.w};
        bool changed = false;
        lua_wrap<void>(L, [&]() {
            changed = ImGui::ColorPicker4(label, col_arr, flags);
        });

        lua_push_imvec4(L, col_arr);
        lua_pushboolean(L, changed);
        return 2;
    }},
    {"ColorButton", [](lua_State* L) -> int {
        const auto desc_id = lua_get<const char*>(L, 2);
        const auto col = lua_get<ImVec4>(L, 3);
        const auto flags = lua_get<int>(L, 4, 0);
        const auto size = lua_get<ImVec2>(L, 5, ImVec2(0, 0));
        return lua_wrap<bool>(L, [&]() { return ImGui::ColorButton(desc_id, col, flags, size); });
    }},
    {"SetColorEditOptions", [](lua_State* L) -> int {
        const auto flags = lua_get<int>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::SetColorEditOptions(flags); });
    }},

    {"TreeNode", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        return lua_wrap<bool>(L, [&]() { return ImGui::TreeNode(label); });
    }},
    {"TreeNodeEx", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        const auto flags = lua_get<int>(L, 3, 0);
        return lua_wrap<bool>(L, [&]() { return ImGui::TreeNodeEx(label, flags); });
    }},
    {"TreePush", [](lua_State* L) -> int {
        const auto str_id = lua_get<const char*>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::TreePush(str_id); });
    }},
    {"TreePop", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::TreePop(); });
    }},
    {"GetTreeNodeToLabelSpacing", [](lua_State* L) -> int {
        return lua_wrap<float>(L, [&]() { return ImGui::GetTreeNodeToLabelSpacing(); });
    }},
    {"CollapsingHeader", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        const auto flags = lua_get<int>(L, 3, 0);
        return lua_wrap<bool>(L, [&]() { return ImGui::CollapsingHeader(label, flags); });
    }},
    {"SetNextItemOpen", [](lua_State* L) -> int {
        const auto is_open = lua_get<bool>(L, 2);
        const auto cond = lua_get<int>(L, 3, 0);
        return lua_wrap<void>(L, [&]() { ImGui::SetNextItemOpen(is_open, cond); });
    }},
    {"SetNextItemStorageID", [](lua_State* L) -> int {
        const auto storage_id = lua_get<ImGuiID>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::SetNextItemStorageID(storage_id); });
    }},

    {"Selectable", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        const auto selected = lua_get<bool>(L, 3, false);
        const auto flags = lua_get<int>(L, 4, 0);
        const auto size = lua_get<ImVec2>(L, 5, ImVec2(0, 0));
        return lua_wrap<bool>(L, [&]() { return ImGui::Selectable(label, selected, flags, size); });
    }},

    {"BeginListBox", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        const auto size = lua_get<ImVec2>(L, 3, ImVec2(0, 0));
        return lua_wrap<bool>(L, [&]() { return ImGui::BeginListBox(label, size); });
    }},
    {"EndListBox", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::EndListBox(); });
    }},

    {"BeginMenuBar", [](lua_State* L) -> int {
        return lua_wrap<bool>(L, [&]() { return ImGui::BeginMenuBar(); });
    }},
    {"EndMenuBar", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::EndMenuBar(); });
    }},
    {"BeginMainMenuBar", [](lua_State* L) -> int {
        return lua_wrap<bool>(L, [&]() { return ImGui::BeginMainMenuBar(); });
    }},
    {"EndMainMenuBar", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::EndMainMenuBar(); });
    }},
    {"BeginMenu", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        const auto enabled = lua_get<bool>(L, 3, true);
        return lua_wrap<bool>(L, [&]() { return ImGui::BeginMenu(label, enabled); });
    }},
    {"EndMenu", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::EndMenu(); });
    }},
    {"MenuItem", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        const auto shortcut = lua_get<const char*>(L, 3, nullptr);
        const auto selected = lua_get<bool>(L, 4, false);
        const auto enabled = lua_get<bool>(L, 5, true);
        return lua_wrap<bool>(L, [&]() { return ImGui::MenuItem(label, shortcut, selected, enabled); });
    }},

    {"BeginTooltip", [](lua_State* L) -> int {
        return lua_wrap<bool>(L, [&]() { return ImGui::BeginTooltip(); });
    }},
    {"EndTooltip", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::EndTooltip(); });
    }},
    {"SetTooltip", [](lua_State* L) -> int {
        const auto text = lua_get<const char*>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::SetTooltip("%s", text); });
    }},
    {"BeginItemTooltip", [](lua_State* L) -> int {
        return lua_wrap<bool>(L, [&]() { return ImGui::BeginItemTooltip(); });
    }},
    {"SetItemTooltip", [](lua_State* L) -> int {
        const auto text = lua_get<const char*>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::SetItemTooltip("%s", text); });
    }},

    {"BeginPopup", [](lua_State* L) -> int {
        const auto str_id = lua_get<const char*>(L, 2);
        const auto flags = lua_get<int>(L, 3, 0);
        return lua_wrap<bool>(L, [&]() { return ImGui::BeginPopup(str_id, flags); });
    }},
    {"EndPopup", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::EndPopup(); });
    }},
    {"OpenPopup", [](lua_State* L) -> int {
        const auto str_id = lua_get<const char*>(L, 2);
        const auto popup_flags = lua_get<int>(L, 3, 0);
        return lua_wrap<void>(L, [&]() { ImGui::OpenPopup(str_id, popup_flags); });
    }},
    {"OpenPopupOnItemClick", [](lua_State* L) -> int {
        const auto str_id = lua_get<const char*>(L, 2, nullptr);
        const auto popup_flags = lua_get<int>(L, 3, 0);
        return lua_wrap<void>(L, [&]() { ImGui::OpenPopupOnItemClick(str_id, popup_flags); });
    }},
    {"CloseCurrentPopup", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::CloseCurrentPopup(); });
    }},
    {"BeginPopupContextItem", [](lua_State* L) -> int {
        const auto str_id = lua_get<const char*>(L, 2, nullptr);
        const auto popup_flags = lua_get<int>(L, 3, 0);
        return lua_wrap<bool>(L, [&]() { return ImGui::BeginPopupContextItem(str_id, popup_flags); });
    }},
    {"BeginPopupContextWindow", [](lua_State* L) -> int {
        const auto str_id = lua_get<const char*>(L, 2, nullptr);
        const auto popup_flags = lua_get<int>(L, 3, 0);
        return lua_wrap<bool>(L, [&]() { return ImGui::BeginPopupContextWindow(str_id, popup_flags); });
    }},
    {"BeginPopupContextVoid", [](lua_State* L) -> int {
        const auto str_id = lua_get<const char*>(L, 2, nullptr);
        const auto popup_flags = lua_get<int>(L, 3, 0);
        return lua_wrap<bool>(L, [&]() { return ImGui::BeginPopupContextVoid(str_id, popup_flags); });
    }},
    {"IsPopupOpen", [](lua_State* L) -> int {
        const auto str_id = lua_get<const char*>(L, 2);
        const auto flags = lua_get<int>(L, 3, 0);
        return lua_wrap<bool>(L, [&]() { return ImGui::IsPopupOpen(str_id, flags); });
    }},

    {"BeginTable", [](lua_State* L) -> int {
        const auto str_id = lua_get<const char*>(L, 2);
        const auto columns = lua_get<int>(L, 3);
        const auto flags = lua_get<int>(L, 4, 0);
        const auto outer_size = lua_get<ImVec2>(L, 5, ImVec2(0.0f, 0.0f));
        const auto inner_width = lua_get<float>(L, 6, 0.0f);
        return lua_wrap<bool>(L, [&]() { return ImGui::BeginTable(str_id, columns, flags, outer_size, inner_width); });
    }},
    {"EndTable", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::EndTable(); });
    }},
    {"TableNextRow", [](lua_State* L) -> int {
        const auto row_flags = lua_get<int>(L, 2, 0);
        const auto min_row_height = lua_get<float>(L, 3, 0.0f);
        return lua_wrap<void>(L, [&]() { ImGui::TableNextRow(row_flags, min_row_height); });
    }},
    {"TableNextColumn", [](lua_State* L) -> int {
        return lua_wrap<bool>(L, [&]() { return ImGui::TableNextColumn(); });
    }},
    {"TableSetColumnIndex", [](lua_State* L) -> int {
        const auto column_n = lua_get<int>(L, 2);
        return lua_wrap<bool>(L, [&]() { return ImGui::TableSetColumnIndex(column_n); });
    }},
    {"TableSetupColumn", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        const auto flags = lua_get<int>(L, 3, 0);
        const auto init_width_or_weight = lua_get<float>(L, 4, 0.0f);
        const auto user_id = lua_get<ImGuiID>(L, 5, 0);
        return lua_wrap<void>(L, [&]() { ImGui::TableSetupColumn(label, flags, init_width_or_weight, user_id); });
    }},
    {"TableSetupScrollFreeze", [](lua_State* L) -> int {
        const auto cols = lua_get<int>(L, 2);
        const auto rows = lua_get<int>(L, 3);
        return lua_wrap<void>(L, [&]() { ImGui::TableSetupScrollFreeze(cols, rows); });
    }},
    {"TableHeader", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::TableHeader(label); });
    }},
    {"TableHeadersRow", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::TableHeadersRow(); });
    }},
    {"TableAngledHeadersRow", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::TableAngledHeadersRow(); });
    }},
    {"TableGetColumnCount", [](lua_State* L) -> int {
        return lua_wrap<int>(L, [&]() { return ImGui::TableGetColumnCount(); });
    }},
    {"TableGetColumnIndex", [](lua_State* L) -> int {
        return lua_wrap<int>(L, [&]() { return ImGui::TableGetColumnIndex(); });
    }},
    {"TableGetRowIndex", [](lua_State* L) -> int {
        return lua_wrap<int>(L, [&]() { return ImGui::TableGetRowIndex(); });
    }},
    {"TableGetColumnName", [](lua_State* L) -> int {
        const auto column_n = lua_get<int>(L, 2, -1);
        return lua_wrap<const char*>(L, [&]() { return ImGui::TableGetColumnName(column_n); });
    }},
    {"TableGetColumnFlags", [](lua_State* L) -> int {
        const auto column_n = lua_get<int>(L, 2, -1);
        return lua_wrap<int>(L, [&]() { return ImGui::TableGetColumnFlags(column_n); });
    }},
    {"TableSetColumnEnabled", [](lua_State* L) -> int {
        const auto column_n = lua_get<int>(L, 2);
        const auto v = lua_get<bool>(L, 3);
        return lua_wrap<void>(L, [&]() { ImGui::TableSetColumnEnabled(column_n, v); });
    }},
    {"TableGetHoveredColumn", [](lua_State* L) -> int {
        return lua_wrap<int>(L, [&]() { return ImGui::TableGetHoveredColumn(); });
    }},
    {"TableSetBgColor", [](lua_State* L) -> int {
        const auto target = lua_get<int>(L, 2);
        const auto color = lua_get<ImU32>(L, 3);
        const auto column_n = lua_get<int>(L, 4, -1);
        return lua_wrap<void>(L, [&]() { ImGui::TableSetBgColor(target, color, column_n); });
    }},

    {"Columns", [](lua_State* L) -> int {
        const auto count = lua_get<int>(L, 2, 1);
        const auto id = lua_get<const char*>(L, 3, nullptr);
        const auto borders = lua_get<bool>(L, 4, true);
        return lua_wrap<void>(L, [&]() { ImGui::Columns(count, id, borders); });
    }},
    {"NextColumn", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::NextColumn(); });
    }},
    {"GetColumnIndex", [](lua_State* L) -> int {
        return lua_wrap<int>(L, [&]() { return ImGui::GetColumnIndex(); });
    }},
    {"GetColumnWidth", [](lua_State* L) -> int {
        const auto column_index = lua_get<int>(L, 2, -1);
        return lua_wrap<float>(L, [&]() { return ImGui::GetColumnWidth(column_index); });
    }},
    {"SetColumnWidth", [](lua_State* L) -> int {
        const auto column_index = lua_get<int>(L, 2);
        const auto width = lua_get<float>(L, 3);
        return lua_wrap<void>(L, [&]() { ImGui::SetColumnWidth(column_index, width); });
    }},
    {"GetColumnOffset", [](lua_State* L) -> int {
        const auto column_index = lua_get<int>(L, 2, -1);
        return lua_wrap<float>(L, [&]() { return ImGui::GetColumnOffset(column_index); });
    }},
    {"SetColumnOffset", [](lua_State* L) -> int {
        const auto column_index = lua_get<int>(L, 2);
        const auto offset_x = lua_get<float>(L, 3);
        return lua_wrap<void>(L, [&]() { ImGui::SetColumnOffset(column_index, offset_x); });
    }},
    {"GetColumnsCount", [](lua_State* L) -> int {
        return lua_wrap<int>(L, [&]() { return ImGui::GetColumnsCount(); });
    }},

    {"TabItemButton", [](lua_State* L) -> int {
        const auto label = lua_get<const char*>(L, 2);
        const auto flags = lua_get<int>(L, 3, 0);
        return lua_wrap<bool>(L, [&]() { return ImGui::TabItemButton(label, flags); });
    }},
    {"SetTabItemClosed", [](lua_State* L) -> int {
        const auto tab_or_docked_window_label = lua_get<const char*>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::SetTabItemClosed(tab_or_docked_window_label); });
    }},

    {"BeginDisabled", [](lua_State* L) -> int {
        const auto disabled = lua_get<bool>(L, 2, true);
        return lua_wrap<void>(L, [&]() { ImGui::BeginDisabled(disabled); });
    }},
    {"EndDisabled", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::EndDisabled(); });
    }},

    {"PushClipRect", [](lua_State* L) -> int {
        const auto clip_rect_min = lua_get<ImVec2>(L, 2);
        const auto clip_rect_max = lua_get<ImVec2>(L, 3);
        const auto intersect_with_current_clip_rect = lua_get<bool>(L, 4, false);
        return lua_wrap<void>(L, [&]() { ImGui::PushClipRect(clip_rect_min, clip_rect_max, intersect_with_current_clip_rect); });
    }},
    {"PopClipRect", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::PopClipRect(); });
    }},

    {"SetItemDefaultFocus", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::SetItemDefaultFocus(); });
    }},
    {"SetKeyboardFocusHere", [](lua_State* L) -> int {
        const auto offset = lua_get<int>(L, 2, 0);
        return lua_wrap<void>(L, [&]() { ImGui::SetKeyboardFocusHere(offset); });
    }},

    {"SetNavCursorVisible", [](lua_State* L) -> int {
        const auto visible = lua_get<bool>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::SetNavCursorVisible(visible); });
    }},

    {"SetNextItemAllowOverlap", [](lua_State* L) -> int {
        return lua_wrap<void>(L, [&]() { ImGui::SetNextItemAllowOverlap(); });
    }},

    {"IsItemHovered", [](lua_State* L) -> int {
        const auto flags = lua_get<int>(L, 2, 0);
        return lua_wrap<bool>(L, [&]() { return ImGui::IsItemHovered(flags); });
    }},
    {"IsItemActive", [](lua_State* L) -> int {
        return lua_wrap<bool>(L, [&]() { return ImGui::IsItemActive(); });
    }},
    {"IsItemFocused", [](lua_State* L) -> int {
        return lua_wrap<bool>(L, [&]() { return ImGui::IsItemFocused(); });
    }},
    {"IsItemClicked", [](lua_State* L) -> int {
        const auto mouse_button = lua_get<int>(L, 2, 0);
        return lua_wrap<bool>(L, [&]() { return ImGui::IsItemClicked(mouse_button); });
    }},
    {"IsItemVisible", [](lua_State* L) -> int {
        return lua_wrap<bool>(L, [&]() { return ImGui::IsItemVisible(); });
    }},
    {"IsItemEdited", [](lua_State* L) -> int {
        return lua_wrap<bool>(L, [&]() { return ImGui::IsItemEdited(); });
    }},
    {"IsItemActivated", [](lua_State* L) -> int {
        return lua_wrap<bool>(L, [&]() { return ImGui::IsItemActivated(); });
    }},
    {"IsItemDeactivated", [](lua_State* L) -> int {
        return lua_wrap<bool>(L, [&]() { return ImGui::IsItemDeactivated(); });
    }},
    {"IsItemDeactivatedAfterEdit", [](lua_State* L) -> int {
        return lua_wrap<bool>(L, [&]() { return ImGui::IsItemDeactivatedAfterEdit(); });
    }},
    {"IsItemToggledOpen", [](lua_State* L) -> int {
        return lua_wrap<bool>(L, [&]() { return ImGui::IsItemToggledOpen(); });
    }},
    {"IsAnyItemHovered", [](lua_State* L) -> int {
        return lua_wrap<bool>(L, [&]() { return ImGui::IsAnyItemHovered(); });
    }},
    {"IsAnyItemActive", [](lua_State* L) -> int {
        return lua_wrap<bool>(L, [&]() { return ImGui::IsAnyItemActive(); });
    }},
    {"IsAnyItemFocused", [](lua_State* L) -> int {
        return lua_wrap<bool>(L, [&]() { return ImGui::IsAnyItemFocused(); });
    }},
    {"GetItemID", [](lua_State* L) -> int {
        return lua_wrap<ImGuiID>(L, [&]() { return ImGui::GetItemID(); });
    }},
    {"GetItemRectMin", [](lua_State* L) -> int {
        return lua_wrap<ImVec2>(L, [&]() { return ImGui::GetItemRectMin(); });
    }},
    {"GetItemRectMax", [](lua_State* L) -> int {
        return lua_wrap<ImVec2>(L, [&]() { return ImGui::GetItemRectMax(); });
    }},
    {"GetItemRectSize", [](lua_State* L) -> int {
        return lua_wrap<ImVec2>(L, [&]() { return ImGui::GetItemRectSize(); });
    }},

    {"IsRectVisible", [](lua_State* L) -> int {
        if (lua_gettop(L) == 2) {
            const auto size = lua_get<ImVec2>(L, 2);
            return lua_wrap<bool>(L, [&]() { return ImGui::IsRectVisible(size); });
        } else {
            const auto rect_min = lua_get<ImVec2>(L, 2);
            const auto rect_max = lua_get<ImVec2>(L, 3);
            return lua_wrap<bool>(L, [&]() { return ImGui::IsRectVisible(rect_min, rect_max); });
        }
    }},
    {"GetTime", [](lua_State* L) -> int {
        return lua_wrap<double>(L, [&]() { return ImGui::GetTime(); });
    }},
    {"GetFrameCount", [](lua_State* L) -> int {
        return lua_wrap<int>(L, [&]() { return ImGui::GetFrameCount(); });
    }},
    {"GetStyleColorName", [](lua_State* L) -> int {
        const auto idx = lua_get<int>(L, 2);
        return lua_wrap<const char*>(L, [&]() { return ImGui::GetStyleColorName(idx); });
    }},

    {"CalcTextSize", [](lua_State* L) -> int {
        const auto text = lua_get<const char*>(L, 2);
        const auto hide_text_after_double_hash = lua_get<bool>(L, 3, false);
        const auto wrap_width = lua_get<float>(L, 4, -1.0f);
        return lua_wrap<ImVec2>(L, [&]() { return ImGui::CalcTextSize(text, nullptr, hide_text_after_double_hash, wrap_width); });
    }},

    {"ColorConvertU32ToFloat4", [](lua_State* L) -> int {
        const auto in_val = lua_get<ImU32>(L, 2);
        return lua_wrap<ImVec4>(L, [&]() { return ImGui::ColorConvertU32ToFloat4(in_val); });
    }},


    {"IsKeyDown", [](lua_State* L) -> int {
        const auto key = static_cast<ImGuiKey>(lua_get<int>(L, 2));
        return lua_wrap<bool>(L, [&]() { return ImGui::IsKeyDown(key); });
    }},
    {"IsKeyPressed", [](lua_State* L) -> int {
        const auto key = static_cast<ImGuiKey>(lua_get<int>(L, 2));
        const auto repeat = lua_get<bool>(L, 3, true);
        return lua_wrap<bool>(L, [&]() { return ImGui::IsKeyPressed(key, repeat); });
    }},
    {"IsKeyReleased", [](lua_State* L) -> int {
        const auto key = static_cast<ImGuiKey>(lua_get<int>(L, 2));
        return lua_wrap<bool>(L, [&]() { return ImGui::IsKeyReleased(key); });
    }},
    {"IsKeyChordPressed", [](lua_State* L) -> int {
        const auto key_chord = lua_get<int>(L, 2);
        return lua_wrap<bool>(L, [&]() { return ImGui::IsKeyChordPressed(key_chord); });
    }},
    {"GetKeyPressedAmount", [](lua_State* L) -> int {
        const auto key = static_cast<ImGuiKey>(lua_get<int>(L, 2));
        const auto repeat_delay = lua_get<float>(L, 3);
        const auto rate = lua_get<float>(L, 4);
        return lua_wrap<int>(L, [&]() { return ImGui::GetKeyPressedAmount(key, repeat_delay, rate); });
    }},
    {"GetKeyName", [](lua_State* L) -> int {
        const auto key = static_cast<ImGuiKey>(lua_get<int>(L, 2));
        return lua_wrap<const char*>(L, [&]() { return ImGui::GetKeyName(key); });
    }},
    {"SetNextFrameWantCaptureKeyboard", [](lua_State* L) -> int {
        const auto want_capture_keyboard = lua_get<bool>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::SetNextFrameWantCaptureKeyboard(want_capture_keyboard); });
    }},

    {"IsMouseDown", [](lua_State* L) -> int {
        const auto button = lua_get<int>(L, 2);
        return lua_wrap<bool>(L, [&]() { return ImGui::IsMouseDown(button); });
    }},
    {"IsMouseClicked", [](lua_State* L) -> int {
        const auto button = lua_get<int>(L, 2);
        const auto repeat = lua_get<bool>(L, 3, false);
        return lua_wrap<bool>(L, [&]() { return ImGui::IsMouseClicked(button, repeat); });
    }},
    {"IsMouseReleased", [](lua_State* L) -> int {
        const auto button = lua_get<int>(L, 2);
        return lua_wrap<bool>(L, [&]() { return ImGui::IsMouseReleased(button); });
    }},
    {"IsMouseDoubleClicked", [](lua_State* L) -> int {
        const auto button = lua_get<int>(L, 2);
        return lua_wrap<bool>(L, [&]() { return ImGui::IsMouseDoubleClicked(button); });
    }},
    {"GetMouseClickedCount", [](lua_State* L) -> int {
        const auto button = lua_get<int>(L, 2);
        return lua_wrap<int>(L, [&]() { return ImGui::GetMouseClickedCount(button); });
    }},
    {"IsMouseHoveringRect", [](lua_State* L) -> int {
        const auto r_min = lua_get<ImVec2>(L, 2);
        const auto r_max = lua_get<ImVec2>(L, 3);
        const auto clip = lua_get<bool>(L, 4, true);
        return lua_wrap<bool>(L, [&]() { return ImGui::IsMouseHoveringRect(r_min, r_max, clip); });
    }},
    {"IsMousePosValid", [](lua_State* L) -> int {
        return lua_wrap<bool>(L, [&]() { return ImGui::IsMousePosValid(); });
    }},
    {"IsAnyMouseDown", [](lua_State* L) -> int {
        return lua_wrap<bool>(L, [&]() { return ImGui::IsAnyMouseDown(); });
    }},
    {"GetMousePos", [](lua_State* L) -> int {
        return lua_wrap<ImVec2>(L, [&]() { return ImGui::GetMousePos(); });
    }},
    {"GetMousePosOnOpeningCurrentPopup", [](lua_State* L) -> int {
        return lua_wrap<ImVec2>(L, [&]() { return ImGui::GetMousePosOnOpeningCurrentPopup(); });
    }},
    {"IsMouseDragging", [](lua_State* L) -> int {
        const auto button = lua_get<int>(L, 2);
        const auto lock_threshold = lua_get<float>(L, 3, -1.0f);
        return lua_wrap<bool>(L, [&]() { return ImGui::IsMouseDragging(button, lock_threshold); });
    }},
    {"GetMouseDragDelta", [](lua_State* L) -> int {
        const auto button = lua_get<int>(L, 2, 0);
        const auto lock_threshold = lua_get<float>(L, 3, -1.0f);
        return lua_wrap<ImVec2>(L, [&]() { return ImGui::GetMouseDragDelta(button, lock_threshold); });
    }},
    {"ResetMouseDragDelta", [](lua_State* L) -> int {
        const auto button = lua_get<int>(L, 2, 0);
        return lua_wrap<void>(L, [&]() { ImGui::ResetMouseDragDelta(button); });
    }},
    {"GetMouseCursor", [](lua_State* L) -> int {
        return lua_wrap<int>(L, [&]() { return ImGui::GetMouseCursor(); });
    }},
    {"SetMouseCursor", [](lua_State* L) -> int {
        const auto cursor_type = lua_get<int>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::SetMouseCursor(cursor_type); });
    }},
    {"SetNextFrameWantCaptureMouse", [](lua_State* L) -> int {
        const auto want_capture_mouse = lua_get<bool>(L, 2);
        return lua_wrap<void>(L, [&]() { ImGui::SetNextFrameWantCaptureMouse(want_capture_mouse); });
    }},






    {"BeginChild", [](lua_State* L) -> int {
        const auto name = lua_get<const char*>(L, 2);
        const auto size = lua_get<ImVec2>(L, 3, ImVec2(0, 0));
        const auto child_flags = lua_get<int>(L, 4, 0);
        const auto window_flags = lua_get<int>(L, 5, 0);

        return lua_wrap<bool>(L, [&]() { return ImGui::BeginChild(name, size, child_flags, window_flags); });
    }},
    {"EndChild",[](lua_State* L) -> int {
        ImGui::EndChild();
        return 0;
    }},

    {"IsWindowAppearing", [](lua_State* L) -> int {
        return lua_wrap<bool>(L, [&]() {
            return ImGui::IsWindowAppearing();
        });
    }},
    {"IsWindowCollapsed", [](lua_State* L) -> int {
        return lua_wrap<bool>(L, [&]() {
            return ImGui::IsWindowCollapsed();
        });
    }},
    {"IsWindowFocused", [](lua_State* L) -> int {
        const auto focused_flags = lua_get<int>(L, 2);
        return lua_wrap<bool>(L, [&]() {
            return ImGui::IsWindowFocused(focused_flags);
        });
    }},
    {"IsWindowHovered", [](lua_State* L) -> int {
        const auto hovered_flags = lua_get<int>(L, 2);
        return lua_wrap<bool>(L, [&]() {
            return ImGui::IsWindowHovered(hovered_flags);
        });
    }},
    {"IsWindowHovered", [](lua_State* L) -> int {
        const auto hovered_flags = lua_get<int>(L, 2);
        return lua_wrap<bool>(L, [&]() {
            return ImGui::IsWindowHovered(hovered_flags);
        });
    }},

    {"GetWindowPos", [](lua_State* L) -> int {
        return lua_wrap<ImVec2>(L, [&]() {
            return ImGui::GetWindowPos();
        });
    }},
    {"GetWindowSize", [](lua_State* L) -> int {
        return lua_wrap<ImVec2>(L, [&]() {
            return ImGui::GetWindowSize();
        });
    }},

    {"GetWindowWidth", [](lua_State* L) -> int {
        return lua_wrap<float>(L, [&]() {
            return ImGui::GetWindowWidth();
        });
    }},
    {"GetWindowHeight", [](lua_State* L) -> int {
        return lua_wrap<float>(L, [&]() {
            return ImGui::GetWindowHeight();
        });
    }},

    {"PushFont", lua_imgui_pushfont},
    {"PopFont", lua_imgui_popfont},
    {"SetClipboardText", [](lua_State* L) -> int {
        const auto clipboard_text = lua_get<const char*>(L, 2);
        return lua_wrap<void>(L, [&]() {
            ImGui::SetClipboardText(clipboard_text);
        });
    }},
    {"GetClipboardText", [](lua_State* L) -> int {
        return lua_wrap<const char*>(L, [&]() {
            return ImGui::GetClipboardText();
        });
    }},
    {nullptr, nullptr}
};

auto register_imgui(lua_State* L) -> void;

#endif