# AC-External-Memory-Trainer
An external memory trainer cheat for Assault Cube 1.3.0.2, built in C++ with a DirectX9 ImGui GUI. This project demonstrates external memory manipulation to toggle in-game features in real-time using a custom interface.

## Features

- God Mode  
- Infinite Grenades  
- Infinite Assault Rifle Ammo  
- Infinite Jump  
- No Recoil  
- ImGui-based GUI overlay using DirectX9

## How It Works

- Attaches to `ac_client.exe` using Windows API functions
- Reads and writes to game memory externally (no DLL injection)
- GUI is built with ImGui using DirectX9 and Win32 backends
- Game hacks implemented by patching memory values or instructions
- Offsets and instruction addresses are defined for key game features

## Usage

1. Open `AssultCubeExternal.sln` in Visual Studio
2. Build the project in Release mode
3. Run the trainer as administrator
4. Start AssaultCube
5. Use the GUI to attach to the game and toggle features

