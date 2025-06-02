#pragma once
#include <d3d9.h>
#include <vector>
#include <string>
#include <windows.h>

namespace gui {
    // Window size
    constexpr int WIDTH = 500;
    constexpr int HEIGHT = 300;

    inline bool exit = true;

    // WinAPI window
    inline HWND window = nullptr;
    inline WNDCLASSEXA windowClass = {};

    // Window movement
    inline POINTS position = {};

    // DirectX state variables
    inline PDIRECT3D9 d3d = nullptr;
    inline LPDIRECT3DDEVICE9 device = nullptr;
    inline D3DPRESENT_PARAMETERS presentParameters = {};

    // Window functions
    void CreateHWindow(const char* windowName, const char* className) noexcept;
    void DestroyHWindow() noexcept;

    // Device functions
    bool CreateDevice() noexcept;
    void ResetDevice() noexcept;
    void DestroyDevice() noexcept;

    // ImGui functions
    void CreateImGui() noexcept;
    void DestroyImGui() noexcept;

    void BeginRender() noexcept;
    void EndRender() noexcept;
    void Render() noexcept;

    // Logging system
    extern std::vector<std::string> logMessages;
    void AddLog(const std::string& message);
}
