# CMake Builder Skill

## Project Context
- **Project**: SDL_Sample (C++20, executable target)
- **CMake**: Minimum 3.10, uses modern practices
- **Presets**: VS-style presets with Windows (x64/x86 Debug/Release), Linux, macOS
- **Build dir**: `${sourceDir}/out/build/${presetName}`
- **Generator**: Ninja (Windows with `cl.exe`)
- **Subprojects**: `SDL_Sample/` contains the only target
- **Source files**: `SDL_Sample.cpp`, `SDL_Sample.h`

## Conventions
- Use **modern CMake** (3.10+): targets, properties, generator expressions
- List sources explicitly in `add_executable` / `target_sources` — no `file(GLOB)`
- Use `set_property(TARGET ... CXX_STANDARD 20)` for C++ standard
- Keep root `CMakeLists.txt` for project config and `add_subdirectory` only
- Add new targets in the `SDL_Sample/` subdirectory

## Workflow
1. Scan source files and headers
2. Update `SDL_Sample/CMakeLists.txt` via `target_sources` or `add_executable`
3. Run `cmake --preset x64-debug && cmake --build --preset x64-debug`
4. Fix any compiler/linker errors

## Common Commands
- `cmake --list-presets` — list available presets
- `cmake --preset x64-debug` — configure
- `cmake --build out/build/x64-debug` — build
- `cmake --build out/build/x64-debug --target SDL_Sample` — single target
- `ctest --test-dir out/build/x64-debug` — run tests

## Adding New Files
```cmake
add_executable(SDL_Sample
  "SDL_Sample.cpp"
  "SDL_Sample.h"
  "new_file.cpp"
)
# OR
target_sources(SDL_Sample PRIVATE
  "new_file.cpp"
  "new_file.h"
)
```

## Adding Dependencies (SDL, etc.)
```cmake
find_package(SDL2 REQUIRED)
target_link_libraries(SDL_Sample PRIVATE SDL2::SDL2)
target_include_directories(SDL_Sample PRIVATE ${SDL2_INCLUDE_DIRS})
```
