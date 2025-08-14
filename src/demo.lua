--[[
    ImVec2, ImVec4 is also not a type in here, you can just make the function yourself by returning the given amount of arguments as a table
    so for example in ImVec2 there is x and y so we return: {x = x, y = y}

    local function ImVec2(x, y)
        return {x = x, y = y}
    end

    Everything that has a ImVec2 as a input option will need it, for example:
    - ImGui::BeginTable('Table', 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg, ImVec2.zero)
    - ImGui::Button("Table button 2", ImVec2.zero)
]]--

local WINDOW_WIDTH = 900
local WINDOW_HEIGHT = 700
local WINDOW_TITLE = "ImGui Lua Demo - UI Showcase"

renderer.CreateHWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT)
renderer.CreateDevice()
renderer.CreateImGui()

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

local Color3 = {
    new = function(r, g, b)
        return { r = r/255, g = g/255, b = b/255 }
    end,
}

local Color4 = {
    new = function(r, g, b, a)
        return { r = r/255, g = g/255, b = b/255, a = a or 1.0 }
    end,
}

local Demo = {}

local AppState = {
    checkbox1 = true,
    checkbox2 = false,
    checkbox3 = true,

    radioSelection = 0,

    backgroundColor = Color4.new(45, 45, 68, 1.0),
    accentColor = Color3.new(180, 142, 173),
    textColor = Color4.new(205, 214, 244, 1.0),

    progressValue = 0.7,
    sliderValue = 50,          

    singleLineText = "",
    multiLineText = "Welcome to ImGui Lua Demo!\n\nThis is a multi-line text area.\nYou can edit this content freely.\n\nFeatures:\n- Syntax highlighting ready\n- Tab support\n- Multi-line editing",

    treeData = {
        { name = "Documents", children = {"Resume.pdf", "Cover Letter.docx", "Portfolio.zip"} },
        { name = "Images", children = {"vacation.jpg", "profile.png", "screenshot.bmp"} },
        { name = "Projects", children = {"ImGui Demo", "Game Engine", "Web App"} },
        { name = "Music", children = {"playlist1.m3u", "song.mp3", "album/"} }
    }
}

function Demo::ApplyCatppuccinMocha()
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

    style.WindowRounding    = 6.0
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

function Demo::ShowBasicWidgets()
    ImGui::Text("Basic Widgets Showcase")
    ImGui::Separator()

    ImGui::Text("Buttons:")
    if ImGui::Button("Regular Button", ImVec2(120, 30)) then
    end

    ImGui::SameLine()
    if ImGui::SmallButton("Small") then
    end

    ImGui::SameLine()
    if ImGui::ArrowButton("left", ImGuiDir_Left) then
    end

    ImGui::Spacing()

    ImGui::Text("Checkboxes:")
    AppState.checkbox1 = ImGui::Checkbox("Enable Feature A", AppState.checkbox1)
    AppState.checkbox2 = ImGui::Checkbox("Enable Feature B", AppState.checkbox2)
    AppState.checkbox3 = ImGui::Checkbox("Enable Feature C", AppState.checkbox3)

    ImGui::Spacing()

    ImGui::Text("Radio Buttons:")
    if ImGui::RadioButton("Option 1", AppState.radioSelection == 0) then
        AppState.radioSelection = 0
    end
    ImGui::SameLine()
    if ImGui::RadioButton("Option 2", AppState.radioSelection == 1) then
        AppState.radioSelection = 1
    end
    ImGui::SameLine()
    if ImGui::RadioButton("Option 3", AppState.radioSelection == 2) then
        AppState.radioSelection = 2
    end

    ImGui::Spacing()

    ImGui::Text("Progress Bar:")
    ImGui::ProgressBar(AppState.progressValue, ImVec2(300, 25), string.format("%.1f%%", AppState.progressValue * 100))

    if ImGui::Button("Animate Progress", ImVec2.zero) then
        AppState.progressValue = math.min(AppState.progressValue + 0.1, 1.0)
    end
    ImGui::SameLine()
    if ImGui::Button("Reset", ImVec2.zero) then
        AppState.progressValue = 0.0
    end

    AppState.sliderValue = ImGui::Slider("Slider", AppState.sliderValue, 50.0, 200.0)
end

function Demo::ShowTextAndInputs()
    ImGui::Text("Text and Input Widgets")
    ImGui::Separator()

    ImGui::Text("Regular text")
    ImGui::TextDisabled("Disabled text")
    ImGui::TextColored(ImVec4(1.0, 0.5, 0.5, 1.0), "Colored text")
    ImGui::TextWrapped("This is a wrapped text that will automatically break into multiple lines when it becomes too long to fit in the current window width.")

    ImGui::Spacing()
    ImGui::Separator()
    ImGui::Spacing()

    ImGui::Text("Text Input:")
    local buffer, changed = ImGui::InputText("Single Line##input", "Example Input", 256)
    if changed then
        AppState.singleLineText = buffer
    end

    ImGui::Spacing()

    ImGui::Text("Multi-line Text Editor:")
    local multiBuffer, multiChanged = ImGui::InputTextMultiline("##multiline", AppState.multiLineText, 4096, ImVec2(WINDOW_WIDTH * 0.8, 200), ImGuiInputTextFlags_AllowTabInput)
    if multiChanged then
        AppState.multiLineText = multiBuffer
    end

    ImGui::Spacing()

    ImGui::Text("Link:")
    ImGui::SameLine()

    ImGui::TextLinkOpenURL("GitHub", "https://github.com")
end

local tables = {}
function Demo::ShowTablesAndTrees()
    ImGui::Text("Tables and Tree Structures")
    ImGui::Separator()

    ImGui::Text("Sample Table:")
    if ImGui::BeginTable("demo_table", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable, ImVec2.zero) then
        ImGui::TableNextRow()
        ImGui::TableSetColumnIndex(0)
        ImGui::Text("Name")
        ImGui::TableSetColumnIndex(1)
        ImGui::Text("Type")
        ImGui::TableSetColumnIndex(2)
        ImGui::Text("Action")


        for i = 1, 5 do
            if tables[i] ~= 200 then
                ImGui::TableNextRow()
                ImGui::TableSetColumnIndex(0)
                ImGui::Text("Item " .. i)

                ImGui::TableSetColumnIndex(1)
                ImGui::Text(i % 2 == 0 and "Even" or "Odd")

                ImGui::TableSetColumnIndex(2)
                if ImGui::Button("Print##" .. i, ImVec2.zero) then
                    print("Hello world")
                end
                ImGui::SameLine()
                if ImGui::Button("Delete##" .. i, ImVec2.zero) then
                    tables[i] = 200;
                end

                if ImGui::IsItemHovered() then
                    ImGui::SetTooltip("Delete item " .. i)
                end
            end
        end

        ImGui::EndTable()
    end

    ImGui::Spacing()
    ImGui::Separator()
    ImGui::Spacing()

    ImGui::Text("Tree Structure:")
    for _, folder in pairs(AppState.treeData) do
        if ImGui::TreeNode(folder.name .. "_node", folder.name) then
            for _, file in pairs(folder.children) do
                ImGui::Bullet()
                ImGui::TextColored(ImVec4(0.7, 0.8, 1.0, 1.0), file)
            end
            ImGui::TreePop()
        end
    end
end

function Demo::ShowColors()
    ImGui::Text("Color Editing")
    ImGui::Separator()

    ImGui::Text("Theme Colors:")

    -- these don't do anything this is just a example
    AppState.backgroundColor = ImGui::ColorEdit4("Background", AppState.backgroundColor)
    AppState.accentColor = ImGui::ColorEdit3("Accent Color", AppState.accentColor)
    AppState.textColor = ImGui::ColorEdit4("Text Color", AppState.textColor)

    ImGui::Spacing()
    ImGui::Separator()
    ImGui::Spacing()

    ImGui::Text("Color Pickers:")
    AppState.backgroundColor = ImGui::ColorPicker4("Background Picker", AppState.backgroundColor)

    ImGui::Spacing()

    if ImGui::Button("Reset to Default Colors", ImVec2.zero) then
        AppState.backgroundColor = Color4.new(45, 45, 68, 1.0)
        AppState.accentColor = Color3.new(180, 142, 173)
        AppState.textColor = Color4.new(205, 214, 244, 1.0)
    end
end

function Demo::ShowAbout()
    ImGui::Text("About This Demo")
    ImGui::Separator()

    ImGui::TextWrapped("This is a ImGui Lua demo showcasing various UI components and features available in the Lua binding.")

    ImGui::Spacing()

    ImGui::Text("Features Demonstrated:")
    ImGui::BulletText("Basic widgets (buttons, checkboxes, radio buttons)")
    ImGui::BulletText("Text display and input controls")
    ImGui::BulletText("Tables with sorting and resizing")
    ImGui::BulletText("Tree structures and hierarchical data")
    ImGui::BulletText("Color editing and theming")
    ImGui::BulletText("Tooltips and interactive elements")
    ImGui::BulletText("Progress bars and visual feedback")

    ImGui::Spacing()
    ImGui::Separator()
    ImGui::Spacing()

    ImGui::Text("Technical Information:")
    ImGui::Text("Window Size: " .. WINDOW_WIDTH .. " x " .. WINDOW_HEIGHT)
    ImGui::Text("Theme: Catppuccin Mocha")
    ImGui::Text("ImGui Version: Lua Binding")

    ImGui::Spacing()

    if ImGui::Button("Copy System Info", ImVec2.zero) then
        local info = "ImGui Lua Demo - System Information\n" ..
                    "Window: " .. WINDOW_WIDTH .. "x" .. WINDOW_HEIGHT .. "\n" ..
                    "Theme: Catppuccin Mocha\n" ..
                    "Features: All widgets functional"
        ImGui::SetClipboardText(info)
    end

    if ImGui::IsItemHovered() then
        ImGui::SetTooltip("Copies system information to clipboard")
    end
end

while ImGui::isRunning() do
    renderer.BeginRender()

    Demo::ApplyCatppuccinMocha()

    ImGui::SetNextWindowPos(0, 0)
    ImGui::SetNextWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT)

    if ImGui::Begin("ImGui Lua Demo") then
        if ImGui::BeginTabBar("MainTabs") then

            if ImGui::BeginTabItem("Widgets", true) then
                Demo::ShowBasicWidgets()
                ImGui::EndTabItem()
            end

            if ImGui::BeginTabItem("Text & Input", true) then
                Demo::ShowTextAndInputs()
                ImGui::EndTabItem()
            end

            if ImGui::BeginTabItem("Tables & Trees", true) then
                Demo::ShowTablesAndTrees()
                ImGui::EndTabItem()
            end

            if ImGui::BeginTabItem("Colors", true) then
                Demo::ShowColors()
                ImGui::EndTabItem()
            end

            if ImGui::BeginTabItem("About", true) then
                Demo::ShowAbout()
                ImGui::EndTabItem()
            end

            ImGui::EndTabBar()
        end
    end
    ImGui::End()

    renderer.EndRender()
end

renderer.DestroyImGui()
renderer.DestroyDevice()
renderer.DestroyHWindow()
