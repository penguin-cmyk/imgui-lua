#pragma once
#include <d3d9.h>



#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"



namespace gui
{
    // constant window size
    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 600;

    // when this changes, exit threads
    // and close menu :)
    inline bool isRunning = true;

    // winapi window vars
    inline HWND window = nullptr;
    inline WNDCLASSEX windowClass = { };

    // points for window movement
    inline POINTS position = { };

    // direct x state vars
    inline PDIRECT3D9 d3d = nullptr;
    inline LPDIRECT3DDEVICE9 device = nullptr;
    inline D3DPRESENT_PARAMETERS presentParameters = { };

    // handle window creation & destruction
    void CreateHWindow(const char* windowName, float WIDTH, float HEIGHT) noexcept;
    void DestroyHWindow() noexcept;

    // handle device creation & destruction
    bool CreateDevice() noexcept;
    void ResetDevice() noexcept;
    void DestroyDevice() noexcept;

    // handle ImGui creation & destruction
    void CreateImGui() noexcept;
    void DestroyImGui() noexcept;

    void BeginRender() noexcept;
    void EndRender() noexcept;
    void Render() noexcept;
}
