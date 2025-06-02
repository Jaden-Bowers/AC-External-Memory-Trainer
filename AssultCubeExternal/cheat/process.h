#pragma once
#include <windows.h>
#include <string>

namespace process {
    DWORD GetProcessID(const std::string& processName);
    uintptr_t GetModuleBaseAddress(DWORD procID, const std::string& modName);
}
