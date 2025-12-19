cmake_minimum_required(VERSION 3.10)
project(GettingThere VERSION 1.0 LANGUAGES CXX)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Find the Raylib package
# This works because you installed it to /usr/local
find_package(raylib 5.0 REQUIRED)

# 2. Define your executable and its source files
# Add any new .cpp files here as you create them
add_executable(res 
    main.cpp 
)

# 3. Link libraries
# This automatically handles include paths and linking
target_link_libraries(res PRIVATE raylib)

# 4. Optional: Add standard Linux system libraries if needed
# Raylib usually handles these via find_package, but if you get 
# "undefined reference to GL", uncomment the line below:
# target_link_libraries(res PRIVATE GL m pthread dl rt X11)
