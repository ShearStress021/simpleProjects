cmake_minimum_required(VERSION 3.10)

project(hello VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find raylib
find_package(raylib REQUIRED)

# Create executable and list ALL .cpp files
add_executable(res
    main.cpp
    character.cpp
    prop.cpp
    enemy.cpp
    baseCharacter.cpp
)

# Link libraries
target_link_libraries(
    res PRIVATE raylib
)
