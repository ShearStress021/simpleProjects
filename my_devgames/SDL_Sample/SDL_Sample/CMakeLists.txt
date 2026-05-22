add_executable (SDL_Sample "SDL_Sample.cpp" "SDL_Sample.h")

set_property(TARGET SDL_Sample PROPERTY CXX_STANDARD 20)

target_link_libraries(SDL_Sample PRIVATE SDL3::SDL3)
