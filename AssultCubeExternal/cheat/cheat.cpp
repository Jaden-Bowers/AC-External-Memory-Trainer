#include "cheat.h"
#include "offsets.h"
#include "process.h"
#include "../gui/gui.h"

bool cheat::isAttached = false;
HANDLE cheat::hProcess = nullptr;
uintptr_t cheat::moduleBase = 0;
uintptr_t cheat::playerBase = 0;
bool cheat::GodMode = false;
bool cheat::InfGrenade = false;
bool cheat::InfArAmmo = false;
bool cheat::InfJump = false;
bool cheat::NoRecoil = false;

// Handle reading game memory
void cheat::AttachToGame() {
    DWORD procID = process::GetProcessID("ac_client.exe");
    if (!procID) {
        gui::AddLog("[ERROR] Process not found!");
        return;
    }

    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
    if (!hProcess) {
        gui::AddLog("[ERROR] Failed to get process handle!");
        return;
    }

    moduleBase = process::GetModuleBaseAddress(procID, "ac_client.exe");
    uintptr_t playerBasePtr = moduleBase + offsets.base;
    ReadProcessMemory(hProcess, (LPCVOID)playerBasePtr, &playerBase, sizeof(DWORD), nullptr);

    gui::AddLog("[SUCCESS] Attached to game.");
    isAttached = true;
}

// Toggle God Mode
void cheat::ToggleGodMode() {
    if (!isAttached) {
        gui::AddLog("[ERROR] Attach to Game First!");
        return;
    }

    static std::thread godModeThread;

    if (GodMode) {
        godModeThread = std::thread([]() {
            while (GodMode && isAttached && hProcess) {
                uintptr_t healthAddress = playerBase + offsets.health;
                int newHealth = 999;
                WriteProcessMemory(hProcess, (LPVOID)healthAddress, &newHealth, sizeof(newHealth), nullptr);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            });
        godModeThread.detach();
        gui::AddLog("[INFO] God Mode enabled.");
    }
    else {
        uintptr_t healthAddress = playerBase + offsets.health;
        int normalHealth = 100;
        WriteProcessMemory(hProcess, (LPVOID)healthAddress, &normalHealth, sizeof(normalHealth), nullptr);

        gui::AddLog("[INFO] God Mode disabled.");
    }
}

// Toggle Infinite Grenades
void cheat::ToggleInfGrenade() {
    if (!isAttached) {
        gui::AddLog("[ERROR] Attach to Game First!");
        return;
    }

    if (InfGrenade) {
        uintptr_t grenadeAddress = playerBase + offsets.grenade;
        int value = 3;
        WriteProcessMemory(hProcess, (LPVOID)grenadeAddress, &value, sizeof(value), nullptr);
        uintptr_t gernadeDecrementAddress = moduleBase + instructions.grenadeDecrement;
        BYTE nopBytes[2] = { 0x90, 0x90 };
        WriteProcessMemory(hProcess, (LPVOID)gernadeDecrementAddress, nopBytes, sizeof(nopBytes), nullptr);
        gui::AddLog("[INFO] Infinite Grenades enabled.");
    }
    else {
        uintptr_t gernadeDecrementAddress = moduleBase + instructions.grenadeDecrement;
        BYTE ogBytes[2] = { 0xFF, 0x08 };
        WriteProcessMemory(hProcess, (LPVOID)gernadeDecrementAddress, ogBytes, sizeof(ogBytes), nullptr);
        gui::AddLog("[INFO] Infinite Grenades disabled.");
    }
}

// NOP AR Ammo Decrement
void cheat::ToggleInfArAmmo() {
    if (!isAttached) {
        gui::AddLog("[ERROR] Attach to Game First!");
        return;
    }

    if (InfArAmmo) {
        uintptr_t ammoAddress = playerBase + offsets.arClipAmmo;
        int value = 20;
        WriteProcessMemory(hProcess, (LPVOID)ammoAddress, &value, sizeof(value), nullptr);
        uintptr_t ammoDecrementAddress = moduleBase + instructions.arAmmoDecrement;
        BYTE nopBytes[2] = { 0x90, 0x90 };
        WriteProcessMemory(hProcess, (LPVOID)ammoDecrementAddress, nopBytes, sizeof(nopBytes), nullptr);
        gui::AddLog("[INFO] Infinite AR Ammo  enabled.");
    }
    else {
        uintptr_t ammoDecrementAddress = moduleBase + instructions.arAmmoDecrement;
        BYTE ogBytes[2] = { 0xFF, 0x08 };
        WriteProcessMemory(hProcess, (LPVOID)ammoDecrementAddress, ogBytes, sizeof(ogBytes), nullptr);
        gui::AddLog("[INFO] Infinite AR Ammo  disabled.");
    }
}

// Toggle Infinite Jump
void cheat::ToggleInfJump() {
    if (!isAttached) {
        gui::AddLog("[ERROR] Attach to Game First!");
        return;
    }

    if (InfJump) {
        uintptr_t jumpAddress = moduleBase + instructions.jumpCheck;
        BYTE nopBytes[3] = { 0x90, 0x90, 0x90};
        WriteProcessMemory(hProcess, (LPVOID)jumpAddress, nopBytes, sizeof(nopBytes), nullptr);
        gui::AddLog("[INFO] Infinite Jump  enabled.");
    }
    else {
        uintptr_t jumpAddress = moduleBase + instructions.jumpCheck;
        BYTE ogBytes[3] = { 0x88, 0x45, 0x5D };
        WriteProcessMemory(hProcess, (LPVOID)jumpAddress, ogBytes, sizeof(ogBytes), nullptr);
        gui::AddLog("[INFO] Infinite Jump  disabled.");
    }
}

// Toggle No Recoil Jump
void cheat::ToggleNoRecoil() {
    if (!isAttached) {
        gui::AddLog("[ERROR] Attach to Game First!");
        return;
    }

    if (NoRecoil) {
        uintptr_t recoilAddress = moduleBase + instructions.recoilIncrement;
        BYTE nopBytes[4] = { 0x90, 0x90, 0x90, 0x90 };
        WriteProcessMemory(hProcess, (LPVOID)recoilAddress, nopBytes, sizeof(nopBytes), nullptr);
        gui::AddLog("[INFO] No Recoil enabled.");
    }
    else {
        uintptr_t recoilAddress = moduleBase + instructions.recoilIncrement;
        BYTE ogBytes[4] = { 0xF3, 0xF11, 0x56, 0x38 };
        WriteProcessMemory(hProcess, (LPVOID)recoilAddress, ogBytes, sizeof(ogBytes), nullptr);
        gui::AddLog("[INFO] No Recoil  disabled.");
    }
}

