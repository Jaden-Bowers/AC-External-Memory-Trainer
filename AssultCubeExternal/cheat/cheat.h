#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include <thread>

namespace cheat {
    extern bool isAttached;
    extern HANDLE hProcess;
    extern uintptr_t moduleBase;
    extern uintptr_t playerBase;
    extern bool GodMode;
    extern bool InfGrenade;
    extern bool InfArAmmo;
    extern bool InfJump;
    extern bool NoRecoil;


    void AttachToGame();
    void ToggleGodMode();
    void ToggleInfGrenade();
    void ToggleInfArAmmo();
    void ToggleInfJump();
    void ToggleNoRecoil();
}
