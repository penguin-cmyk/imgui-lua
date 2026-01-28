local screen = {
    WIDTH = 1280,
    HEIGHT = 720
}
local success = renderer::Init("ImGui Feature Showcase", screen.WIDTH, screen.HEIGHT);

if (not success) then
    return
end

local ImVec2 = setmetatable({
    zero = { x = 0, y = 0 }
}, {
    __call = function(self, x, y)
        return { x = x or 0, y = y or 0 }
    end,
})

local ImVec4 = setmetatable({
    zero = { x = 0, y = 0, z = 0, w = 0 }
}, {
    __call = function(self, x, y, z, w)
        return { x = x or 0, y = y or 0, z = z or 0, w = w or 0 }
    end,
})

local ImColor = setmetatable({
    zero = { r = 0, g = 0, b = 0, a = 0 }
}, {
    __call = function(self, r, g, b, a)
        return { r = r/255, g = g/255, b = b/255, a = a or 1.0 }
    end,
})

function ApplyCatppuccinMocha()
    local style = ImGui::GetStyle()
    local colors = style.Colors

    colors[ImGuiCol_WindowBg]           = ImVec4(0.10, 0.10, 0.15, 1.00)
    colors[ImGuiCol_ChildBg]            = ImVec4(0.10, 0.10, 0.15, 1.00)
    colors[ImGuiCol_PopupBg]            = ImVec4(0.10, 0.10, 0.15, 1.00)
    colors[ImGuiCol_MenuBarBg]          = ImVec4(0.12, 0.12, 0.18, 1.00)

    colors[ImGuiCol_TitleBg]            = ImVec4(0.10, 0.10, 0.15, 1.00)
    colors[ImGuiCol_TitleBgActive]      = ImVec4(0.18, 0.18, 0.27, 1.00)
    colors[ImGuiCol_TitleBgCollapsed]   = ImVec4(0.10, 0.10, 0.15, 1.00)

    colors[ImGuiCol_Border]             = ImVec4(0.31, 0.31, 0.42, 1.00)
    colors[ImGuiCol_BorderShadow]       = ImVec4(0.00, 0.00, 0.00, 0.00)

    colors[ImGuiCol_Text]               = ImVec4(0.80, 0.84, 0.96, 1.00)
    colors[ImGuiCol_TextDisabled]       = ImVec4(0.51, 0.53, 0.64, 1.00)

    colors[ImGuiCol_FrameBg]            = ImVec4(0.18, 0.18, 0.27, 1.00)
    colors[ImGuiCol_FrameBgHovered]     = ImVec4(0.27, 0.28, 0.39, 1.00)
    colors[ImGuiCol_FrameBgActive]      = ImVec4(0.36, 0.36, 0.48, 1.00)

    colors[ImGuiCol_Tab]                = ImVec4(0.18, 0.18, 0.27, 1.00)
    colors[ImGuiCol_TabHovered]         = ImVec4(0.70, 0.65, 0.97, 1.00)
    colors[ImGuiCol_TabActive]          = ImVec4(0.27, 0.28, 0.39, 1.00)
    colors[ImGuiCol_TabUnfocused]       = ImVec4(0.18, 0.18, 0.27, 1.00)
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.27, 0.28, 0.39, 1.00)

    colors[ImGuiCol_Button]             = ImVec4(0.36, 0.36, 0.48, 1.00)
    colors[ImGuiCol_ButtonHovered]      = ImVec4(0.70, 0.65, 0.97, 1.00)
    colors[ImGuiCol_ButtonActive]       = ImVec4(0.80, 0.65, 0.72, 1.00)

    colors[ImGuiCol_Header]             = ImVec4(0.36, 0.36, 0.48, 1.00)
    colors[ImGuiCol_HeaderHovered]      = ImVec4(0.70, 0.65, 0.97, 1.00)
    colors[ImGuiCol_HeaderActive]       = ImVec4(0.80, 0.65, 0.72, 1.00)

    colors[ImGuiCol_CheckMark]          = ImVec4(0.80, 0.84, 0.96, 1.00)
    colors[ImGuiCol_SliderGrab]         = ImVec4(0.70, 0.65, 0.97, 1.00)
    colors[ImGuiCol_SliderGrabActive]   = ImVec4(0.80, 0.65, 0.72, 1.00)

    colors[ImGuiCol_ScrollbarBg]        = ImVec4(0.18, 0.18, 0.27, 1.00)
    colors[ImGuiCol_ScrollbarGrab]      = ImVec4(0.36, 0.36, 0.48, 1.00)
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.70, 0.65, 0.97, 1.00)
    colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.80, 0.65, 0.72, 1.00)

    colors[ImGuiCol_Separator]          = ImVec4(0.31, 0.31, 0.42, 1.00)
    colors[ImGuiCol_SeparatorHovered]   = ImVec4(0.70, 0.65, 0.97, 1.00)
    colors[ImGuiCol_SeparatorActive]    = ImVec4(0.80, 0.65, 0.72, 1.00)

    colors[ImGuiCol_ResizeGrip]         = ImVec4(0.36, 0.36, 0.48, 0.20)
    colors[ImGuiCol_ResizeGripHovered]  = ImVec4(0.70, 0.65, 0.97, 0.60)
    colors[ImGuiCol_ResizeGripActive]   = ImVec4(0.80, 0.65, 0.72, 0.80)

    style.WindowRounding    = 0.0
    style.ChildRounding     = 6.0
    style.FrameRounding     = 4.0
    style.PopupRounding     = 4.0
    style.ScrollbarRounding = 4.0
    style.GrabRounding      = 4.0
    style.TabRounding       = 4.0

    style.WindowPadding     = ImVec2(12.0, 12.0)
    style.FramePadding      = ImVec2(6.0, 4.0)
    style.ItemSpacing       = ImVec2(8.0, 6.0)
    style.ItemInnerSpacing  = ImVec2(6.0, 4.0)
    style.IndentSpacing     = 22.0

    style.ScrollbarSize     = 14.0
    style.FrameBorderSize   = 1.0
    style.WindowBorderSize  = 1.0
    style.TabBorderSize     = 1.0
end

local state = {
    checkbox = false,
    radio_selected = 0,

    text_input = "",
    multiline_input = "",
    text_with_hint = "",

    float_value = 0.0,
    int_value = 0,
    double_value = 0.0,

    slider_float = 0.5,
    slider_int = 50,
    slider_angle = 0.0,

    drag_float = 0.0,
    drag_int = 0,

    color3 = ImVec4(1.0, 0.0, 0.0, 1.0),
    color4 = ImVec4(0.0, 1.0, 0.0, 1.0),

    tree_open = false,

    combo_current = 0,
    combo_items = {"Item 1", "Item 2", "Item 3", "Item 4"},

    listbox_current = 0,

    progress = 0.0,

    widgets_enabled = true,

    table_data = {
        {name = "Alice", age = 25, score = 95.5},
        {name = "Bob", age = 30, score = 87.3},
        {name = "Charlie", age = 22, score = 92.1},
        {name = "Diana", age = 28, score = 88.9},
    }
}

local io = ImGui::GetIO()

ApplyCatppuccinMocha()

local fonts = io::Fonts();
local mono = fonts::AddFont("JetBrainsMono-Regular.ttf", 14.0)
fonts::AddFontDefault()
fonts::Build()

local open_about = false


while (renderer::ShouldClose() == false) do
    renderer::BeginFrame()

    ImGui::SetNextWindowSize(screen.WIDTH, screen.HEIGHT)
    ImGui::SetNextWindowPos(0, 0)

    ImGui::PushFont(mono)


    ImGui::Begin("ImGui Feature Showcase",  ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_MenuBar)



    if ImGui::BeginMenuBar() then
        if ImGui::BeginMenu("File") then
            if ImGui::MenuItem("New", "Ctrl+N") then
                print("New clicked")
            end
            if ImGui::MenuItem("Open", "Ctrl+O") then
                print("Open clicked")
            end
            ImGui::Separator()
            if ImGui::MenuItem("Exit", "Alt+F4") then
                print("Exit clicked")
            end
            ImGui::EndMenu()
        end

        if ImGui::BeginMenu("Edit") then
            ImGui::MenuItem("Undo", "Ctrl+Z", false, false) -- disabled
            ImGui::MenuItem("Redo", "Ctrl+Y")
            ImGui::EndMenu()
        end


        if ImGui::BeginMenu("Help") then
            if ImGui::MenuItem("About") then
                open_about = true
                print("About clicked")
            end

            ImGui::EndMenu()
        end


        if open_about then
            ImGui::OpenPopup("AboutPopup")
            open_about = false
        end

        if ImGui::BeginPopup("AboutPopup") then
            ImGui::Text("ImGui Lua Bindings")
            ImGui::Separator()
            ImGui::Text("Version 1.0")
            ImGui::Text("A comprehensive showcase of ImGui features")
            if ImGui::Button("Close") then
                ImGui::CloseCurrentPopup()
            end
            ImGui::EndPopup()
        end

        ImGui::EndMenuBar()
    end



    if ImGui::BeginTabBar("MainTabs") then

        if ImGui::BeginTabItem("Basic Widgets", true) then
            ImGui::SeparatorText("Text Display")

            ImGui::Text("Regular text")
            ImGui::TextColored(ImVec4(1.0, 0.5, 0.0, 1.0), "Colored text")
            ImGui::TextDisabled("Disabled text")
            ImGui::TextWrapped("This is a long text that will wrap around when it reaches the edge of the window. Very useful for displaying paragraphs.")
            ImGui::Bullet()
            ImGui::SameLine()
            ImGui::Text("Bulleted text")
            ImGui::BulletText("Bullet with text combined")
            ImGui::LabelText("Label", "Value")

            ImGui::SeparatorText("Buttons")

            if ImGui::Button("Regular Button", ImVec2(200, 40)) then
                print("Button clicked!")
            end

            ImGui::SameLine()
            if ImGui::SmallButton("Small") then
                print("Small button clicked!")
            end

            if ImGui::ArrowButton("LeftArrow", ImGuiDir_Left) then
                print("Left arrow clicked!")
            end

            ImGui::SameLine()
            if ImGui::ArrowButton("RightArrow", ImGuiDir_Right) then
                print("Right arrow clicked!")
            end

            if ImGui::InvisibleButton("InvisibleBtn", ImVec2(100, 30)) then
                print("Invisible button clicked!")
            end
            if ImGui::IsItemHovered() then
                ImGui::SetTooltip("This is an invisible button")
            end

            ImGui::SeparatorText("Checkboxes & Radio Buttons")

            local new_val, changed = ImGui::Checkbox("Checkbox", state.checkbox)
            if changed then
                state.checkbox = new_val
                print("Checkbox::", state.checkbox)
            end

            if ImGui::RadioButton("Radio 1", state.radio_selected == 0) then
                state.radio_selected = 0
            end
            ImGui::SameLine()
            if ImGui::RadioButton("Radio 2", state.radio_selected == 1) then
                state.radio_selected = 1
            end
            ImGui::SameLine()
            if ImGui::RadioButton("Radio 3", state.radio_selected == 2) then
                state.radio_selected = 2
            end

            ImGui::SeparatorText("Progress Bar")

            ImGui::ProgressBar(state.progress, ImVec2(-1, 0), string.format("%.0f%%", state.progress * 100))
            state.progress = state.progress + 0.001
            if state.progress > 1.0 then
                state.progress = 0.0
            end

            ImGui::SeparatorText("Links")

            if ImGui::TextLink("Click me!") then
                print("Link clicked!")
            end

            ImGui::EndTabItem()
        end

        if ImGui::BeginTabItem("Input Widgets", true) then
            ImGui::SeparatorText("Text Input")

            local text, changed = ImGui::InputText("Text Input", state.text_input, 256)
            if changed then
                state.text_input = text
            end

            local hint_text, hint_changed = ImGui::InputTextWithHint("With Hint", "Enter text here...", state.text_with_hint, 256)
            if hint_changed then
                state.text_with_hint = hint_text
            end

            local multi, multi_changed = ImGui::InputTextMultiline("Multiline", state.multiline_input, 1024, ImVec2(-1, 100))
            if multi_changed then
                state.multiline_input = multi
            end

            ImGui::SeparatorText("Numeric Input")

            local float_val, float_changed = ImGui::InputFloat("Float Input", state.float_value, 0.1, 1.0)
            if float_changed then
                state.float_value = float_val
            end

            local int_val, int_changed = ImGui::InputInt("Int Input", state.int_value, 1, 10)
            if int_changed then
                state.int_value = int_val
            end

            local double_val, double_changed = ImGui::InputDouble("Double Input", state.double_value, 0.01, 1.0)
            if double_changed then
                state.double_value = double_val
            end

            ImGui::EndTabItem()
        end

        if ImGui::BeginTabItem("Sliders & Drags", true) then
            ImGui::SeparatorText("Sliders")

            local slider_f, slider_f_changed = ImGui::SliderFloat("Float Slider", state.slider_float, 0.0, 1.0)
            if slider_f_changed then
                state.slider_float = slider_f
            end

            local slider_i, slider_i_changed = ImGui::SliderInt("Int Slider", state.slider_int, 0, 100)
            if slider_i_changed then
                state.slider_int = slider_i
            end

            local slider_a, slider_a_changed = ImGui::SliderAngle("Angle Slider", state.slider_angle)
            if slider_a_changed then
                state.slider_angle = slider_a
            end

            ImGui::Text("Vertical Sliders::")
            local vslider1, vs1_changed = ImGui::VSliderFloat("##v1", ImVec2(40, 160), state.slider_float, 0.0, 1.0)
            if vs1_changed then
                state.slider_float = vslider1
            end

            ImGui::SameLine()
            local vslider2, vs2_changed = ImGui::VSliderInt("##v2", ImVec2(40, 160), state.slider_int, 0, 100)
            if vs2_changed then
                state.slider_int = vslider2
            end

            ImGui::SeparatorText("Drag Widgets")

            local drag_f, drag_f_changed = ImGui::DragFloat("Drag Float", state.drag_float, 0.1, -100.0, 100.0)
            if drag_f_changed then
                state.drag_float = drag_f
            end

            local drag_i, drag_i_changed = ImGui::DragInt("Drag Int", state.drag_int, 1, -100, 100)
            if drag_i_changed then
                state.drag_int = drag_i
            end

            ImGui::EndTabItem()
        end

        if ImGui::BeginTabItem("Color Pickers", true) then
            ImGui::SeparatorText("Color Edit")

            local col3, col3_changed = ImGui::ColorEdit3("Color RGB", state.color3)
            if col3_changed then
                state.color3 = col3
            end

            local col4, col4_changed = ImGui::ColorEdit4("Color RGBA", state.color4)
            if col4_changed then
                state.color4 = col4
            end

            ImGui::SeparatorText("Color Picker")

            local picker3, picker3_changed = ImGui::ColorPicker3("Pick RGB", state.color3)
            if picker3_changed then
                state.color3 = picker3
            end

            ImGui::SameLine()

            local picker4, picker4_changed = ImGui::ColorPicker4("Pick RGBA", state.color4)
            if picker4_changed then
                state.color4 = picker4
            end

            ImGui::SeparatorText("Color Button")

            if ImGui::ColorButton("ColorBtn", state.color4, 0, ImVec2(50, 50)) then
                print("Color button clicked!")
            end

            ImGui::EndTabItem()
        end

        if ImGui::BeginTabItem("Trees & Lists", true) then
            ImGui::SeparatorText("Tree Nodes")

            if ImGui::TreeNode("Parent Node") then
                ImGui::Text("Content under parent")

                if ImGui::TreeNode("Child Node 1") then
                    ImGui::Text("Content under child 1")
                    ImGui::TreePop()
                end

                if ImGui::TreeNode("Child Node 2") then
                    ImGui::Text("Content under child 2")
                    ImGui::TreePop()
                end

                ImGui::TreePop()
            end

            if ImGui::CollapsingHeader("Collapsing Header") then
                ImGui::Text("This content collapses!")
                ImGui::Bullet()
                ImGui::Text("Item 1")
                ImGui::Bullet()
                ImGui::Text("Item 2")
            end

            ImGui::SeparatorText("Selectables")

            if ImGui::Selectable("Selectable 1", false) then
                print("Selectable 1 clicked")
            end
            if ImGui::Selectable("Selectable 2", false) then
                print("Selectable 2 clicked")
            end
            if ImGui::Selectable("Selectable 3 (Disabled)", false, ImGuiSelectableFlags_Disabled) then
                print("Selectable 3 clicked")
            end

            ImGui::SeparatorText("List Box")

            if ImGui::BeginListBox("##listbox", ImVec2(-1, 100)) then
                for i = 0, 9 do
                    if ImGui::Selectable("Item " .. i, state.listbox_current == i) then
                        state.listbox_current = i
                        print("Selected item::", i)
                    end
                end
                ImGui::EndListBox()
            end

            ImGui::SeparatorText("Combo Box")

            if ImGui::BeginCombo("Combo", state.combo_items[state.combo_current + 1]) then
                for i = 0, #state.combo_items - 1 do
                    local is_selected = state.combo_current == i
                    if ImGui::Selectable(state.combo_items[i + 1], is_selected) then
                        state.combo_current = i
                    end
                    if is_selected then
                        ImGui::SetItemDefaultFocus()
                    end
                end
                ImGui::EndCombo()
            end

            ImGui::EndTabItem()
        end

        if ImGui::BeginTabItem("Tables", true) then
            ImGui::SeparatorText("Simple Table")

            if ImGui::BeginTable("SimpleTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg) then
                ImGui::TableSetupColumn("Name")
                ImGui::TableSetupColumn("Age")
                ImGui::TableSetupColumn("Score")
                ImGui::TableHeadersRow()

                for i, row in ipairs(state.table_data) do
                    ImGui::TableNextRow()

                    ImGui::TableNextColumn()
                    ImGui::Text(row.name)

                    ImGui::TableNextColumn()
                    ImGui::Text(tostring(row.age))

                    ImGui::TableNextColumn()
                    ImGui::Text(string.format("%.1f", row.score))
                end

                ImGui::EndTable()
            end

            ImGui::SeparatorText("Advanced Table")

            if ImGui::BeginTable("AdvancedTable", 3,
                ImGuiTableFlags_Resizable | ImGuiTableFlags_Sortable | ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY,
                ImVec2(0, 200)) then

                ImGui::TableSetupScrollFreeze(0, 1)
                ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_DefaultSort)
                ImGui::TableSetupColumn("Age", ImGuiTableColumnFlags_None)
                ImGui::TableSetupColumn("Score", ImGuiTableColumnFlags_None)
                ImGui::TableHeadersRow()

                for i, row in ipairs(state.table_data) do
                    ImGui::TableNextRow()

                    ImGui::TableNextColumn()
                    ImGui::Text(row.name)

                    ImGui::TableNextColumn()
                    ImGui::Text(tostring(row.age))

                    ImGui::TableNextColumn()
                    ImGui::Text(string.format("%.1f", row.score))
                end

                ImGui::EndTable()
            end

            ImGui::SeparatorText("Legacy Columns")

            ImGui::Columns(3, "LegacyColumns", true)
            ImGui::Text("Column 1")
            ImGui::NextColumn()
            ImGui::Text("Column 2")
            ImGui::NextColumn()
            ImGui::Text("Column 3")
            ImGui::NextColumn()
            ImGui::Separator()
            ImGui::Text("Row 2, Col 1")
            ImGui::NextColumn()
            ImGui::Text("Row 2, Col 2")
            ImGui::NextColumn()
            ImGui::Text("Row 2, Col 3")
            ImGui::Columns(1)

            ImGui::EndTabItem()
        end

        if ImGui::BeginTabItem("Layouts", true) then
            ImGui::SeparatorText("Groups")

            ImGui::BeginGroup()
            ImGui::Text("Group 1")
            ImGui::Button("Button 1")
            ImGui::Button("Button 2")
            ImGui::EndGroup()

            ImGui::SameLine()

            ImGui::BeginGroup()
            ImGui::Text("Group 2")
            ImGui::Button("Button 3")
            ImGui::Button("Button 4")
            ImGui::EndGroup()

            ImGui::SeparatorText("Child Windows")

            if ImGui::BeginChild("ChildLeft", ImVec2(300, 200)) then
                ImGui::Text("Left Child Window")
                for i = 0, 20 do
                    ImGui::Text("Scrollable item " .. i)
                end
                ImGui::EndChild()
            end

            ImGui::SameLine()

            if ImGui::BeginChild("ChildRight", ImVec2(300, 200)) then
                ImGui::Text("Right Child Window")
                ImGui::Button("Button in child")
                ImGui::Checkbox("Checkbox in child", false)
                ImGui::EndChild()
            end

            ImGui::SeparatorText("Spacing & Alignment")

            ImGui::Text("Normal spacing")
            ImGui::Spacing()
            ImGui::Spacing()
            ImGui::Text("After spacing")

            ImGui::Indent(20)
            ImGui::Text("Indented text")
            ImGui::Unindent(20)

            ImGui::Text("Normal text")
            ImGui::AlignTextToFramePadding()
            ImGui::Text("Aligned to frame padding")

            ImGui::EndTabItem()
        end

        if ImGui::BeginTabItem("Popups", true) then
            ImGui::SeparatorText("Context Menus")

            ImGui::Text("Right-click me!")
            if ImGui::BeginPopupContextItem("ItemContext") then
                if ImGui::MenuItem("Action 1") then
                    print("Action 1")
                end
                if ImGui::MenuItem("Action 2") then
                    print("Action 2")
                end
                ImGui::EndPopup()
            end

            ImGui::Text("Right-click in window!")
            if ImGui::BeginPopupContextWindow("WindowContext") then
                if ImGui::MenuItem("Window Action 1") then
                    print("Window Action 1")
                end
                if ImGui::MenuItem("Window Action 2") then
                    print("Window Action 2")
                end
                ImGui::EndPopup()
            end

            ImGui::SeparatorText("Regular Popups")

            if ImGui::Button("Open Popup") then
                ImGui::OpenPopup("RegularPopup")
            end

            if ImGui::BeginPopup("RegularPopup") then
                ImGui::Text("This is a regular popup!")
                ImGui::Separator()
                if ImGui::Button("Close") then
                    ImGui::CloseCurrentPopup()
                end
                ImGui::EndPopup()
            end

            ImGui::SeparatorText("Tooltips")

            ImGui::Button("Hover me!")
            if ImGui::IsItemHovered() then
                ImGui::SetTooltip("This is a simple tooltip")
            end

            ImGui::SameLine()

            ImGui::Button("Hover me too!")
            if ImGui::BeginItemTooltip() then
                ImGui::Text("Advanced tooltip")
                ImGui::Separator()
                ImGui::Text("With multiple lines")
                ImGui::BulletText("And bullets!")
                ImGui::EndTooltip()
            end

            ImGui::EndTabItem()
        end

        if ImGui::BeginTabItem("Utilities", true) then
            ImGui::SeparatorText("Disabled Widgets")

            local new_val, changed = ImGui::Checkbox("Enable widgets", state.widgets_enabled)
            if changed then
                state.widgets_enabled = new_val
            end

            ImGui::BeginDisabled(not state.widgets_enabled)
            ImGui::Button("Disabled Button")
            ImGui::Checkbox("Disabled Checkbox", false)
            ImGui::SliderFloat("Disabled Slider", 0.5, 0.0, 1.0)
            ImGui::EndDisabled()

            ImGui::SeparatorText("Item Queries")

            ImGui::Button("Query Me!")
            if ImGui::IsItemHovered() then
                ImGui::Text("Hovered:: true")
            else
                ImGui::Text("Hovered:: false")
            end

            if ImGui::IsItemActive() then
                ImGui::SameLine()
                ImGui::Text("Active:: true")
            end

            if ImGui::IsItemClicked() then
                print("Item was clicked!")
            end

            local item_min = ImGui::GetItemRectMin()
            local item_max = ImGui::GetItemRectMax()
            local item_size = ImGui::GetItemRectSize()
            ImGui::Text(string.format("Item Rect:: (%.1f,%.1f) to (%.1f,%.1f)", item_min.x, item_min.y, item_max.x, item_max.y))
            ImGui::Text(string.format("Item Size:: %.1f x %.1f", item_size.x, item_size.y))

            ImGui::SeparatorText("Input Queries")

            local mouse_pos = ImGui::GetMousePos()
            ImGui::Text(string.format("Mouse Position:: (%.1f, %.1f)", mouse_pos.x, mouse_pos.y))

            if ImGui::IsMouseDown(0) then
                ImGui::Text("Left Mouse:: DOWN")
            else
                ImGui::Text("Left Mouse:: UP")
            end

            if ImGui::IsMouseClicked(0) then
                print("Left mouse clicked!")
            end

            if ImGui::IsMouseDragging(0) then
                local drag_delta = ImGui::GetMouseDragDelta(0)
                ImGui::Text(string.format("Dragging:: (%.1f, %.1f)", drag_delta.x, drag_delta.y))
            end

            ImGui::SeparatorText("Keyboard Queries")

            if ImGui::IsKeyPressed(ImGuiKey_Space) then
                print("Space pressed!")
            end

            if ImGui::IsKeyDown(ImGuiKey_LeftCtrl) then
                ImGui::Text("Ctrl is held down")
            end

            ImGui::SeparatorText("Misc Utilities")

            local text_size = ImGui::CalcTextSize("Calculate me!")
            ImGui::Text(string.format("Text size:: %.1f x %.1f", text_size.x, text_size.y))

            ImGui::Text(string.format("Frame count:: %d", ImGui::GetFrameCount()))
            ImGui::Text(string.format("Time:: %.2f seconds", ImGui::GetTime()))

            local line_height = ImGui::GetTextLineHeight()
            local frame_height = ImGui::GetFrameHeight()
            ImGui::Text(string.format("Line height:: %.1f", line_height))
            ImGui::Text(string.format("Frame height:: %.1f", frame_height))

            ImGui::EndTabItem()
        end

        ImGui::EndTabBar()
    end
    ImGui::PopFont()
    ImGui::End()

    renderer::EndFrame()
end

renderer::Shutdown()