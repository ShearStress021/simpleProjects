# CMake Builder Skill

## Project Context
- **Project**: SDL_Sample (C++20, executable target)
- **CMake**: Minimum 3.14, cross-platform
- **SDL2**: Fetched via FetchContent, built **statically** (no SDL DLL needed)
- **Source files**: `SDL_Sample.cpp`, `SDL_Sample.h` in `SDL_Sample/`

## Presets (Cross-Platform)

| Preset | Platform | Generator | Config |
|--------|----------|-----------|--------|
| `ninja-multi` | All | Ninja Multi-Config | Debug/Release |
| `win-x64-debug` | Windows | VS 18 2026 x64 | Debug |
| `win-x64-release` | Windows | VS 18 2026 x64 | Release |
| `win-x86-debug` | Windows | VS 18 2026 Win32 | Debug |
| `win-x86-release` | Windows | VS 18 2026 Win32 | Release |
| `linux-debug` | Linux | Ninja | Debug |
| `macos-debug` | macOS | Ninja | Debug |

Platform-conditional presets (`linux-debug`, `macos-debug`) only appear on matching systems.

## Visual Studio

### Config Files
- `launch.vs.json` — sets startup target to `SDL_Sample.exe`
- `CMakeSettings.json` — VS-specific fallback config
- `CMakePresets.json` — main config (read by VS 2022+)

### Startup Item Fix
1. Wait for CMake configure to finish (FetchContent downloads SDL ~1 min)
2. In Solution Explorer, right-click `SDL_Sample.exe` → Set as Startup Item
3. In startup dropdown, select `SDL_Sample.exe`
4. Hit F5

## Cross-Platform Commands

```bash
# Windows (VS)
cmake --preset win-x64-debug
cmake --build out/build/win-x64-debug --config Debug

# All platforms (Ninja Multi-Config)
cmake --preset ninja-multi
cmake --build out/build/ninja-multi --config Debug

# Linux / macOS
cmake --preset linux-debug
cmake --build out/build/linux-debug
```

## Conventions
- Modern CMake (3.14+): targets, properties, generator expressions
- Explicit source lists — no `file(GLOB)`
- Static SDL2 linking — no runtime DLL dependencies
- Root `CMakeLists.txt` for project + `add_subdirectory`
- Subdirectory `SDL_Sample/` for the executable target
