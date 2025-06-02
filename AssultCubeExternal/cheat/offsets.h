#pragma once
#include <windows.h>

// Structure for player offsets
struct PlayerOffsets {
    DWORD base = 0x0017E0A8;

    DWORD posX = 0x0028;
    DWORD posY = 0x002C;
    DWORD posZ = 0x0030;
    DWORD viewHorizontal = 0x0038;
    DWORD viewVertical = 0x0038;
    DWORD groundCheck = 0x005D;

    DWORD health = 0x00EC;
    DWORD arReserveAmmo = 0x011C;
    DWORD arClipAmmo = 0x0140;
    DWORD grenade = 0x0144;
    DWORD pistolReserveAmmo = 0x0108;
    DWORD pistolClipAmmo = 0x012C;
    DWORD playerName = 0x0205;
};

// Structure for instruction addresses
struct GameInstructions {
    DWORD arAmmoDecrement = 0xC73EF;
    DWORD jumpCheck = 0xC140E;
    DWORD grenadeDecrement = 0xC7E5D;
    DWORD healthDecrement = 0x1C223; // For world not just self (meaning bots dont lose health either)
    DWORD recoilIncrement = 0xC2EC3;
};

// Global instances
inline PlayerOffsets offsets;
inline GameInstructions instructions;
