#include "process.h"
#include <TlHelp32.h>


// Get Process ID from the proc name
DWORD process::GetProcessID(const std::string& processName) {
    DWORD procID = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 procEntry;
    procEntry.dwSize = sizeof(procEntry);

    if (Process32First(hSnap, &procEntry)) {
        do {
            if (!_stricmp(procEntry.szExeFile, processName.c_str())) {
                procID = procEntry.th32ProcessID;
                break;
            }
        } while (Process32Next(hSnap, &procEntry));
    }
    CloseHandle(hSnap);
    return procID;
}

// Get Module Base Addr from proc ID
uintptr_t process::GetModuleBaseAddress(DWORD procID, const std::string& modName) {
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, procID);
    MODULEENTRY32 modEntry;
    modEntry.dwSize = sizeof(modEntry);

    if (Module32First(hSnap, &modEntry)) {
        do {
            if (!_stricmp(modEntry.szModule, modName.c_str())) {
                modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                break;
            }
        } while (Module32Next(hSnap, &modEntry));
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}
