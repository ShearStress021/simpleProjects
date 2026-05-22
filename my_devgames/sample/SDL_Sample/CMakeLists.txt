add_executable (SDL_Sample "SDL_Sample.cpp" "SDL_Sample.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SDL_Sample PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(SDL_Sample PRIVATE SDL2::SDL2 SDL2::SDL2main)
