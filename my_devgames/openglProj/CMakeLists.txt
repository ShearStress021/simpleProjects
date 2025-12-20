cmake_minimum_required(VERSION 3.10)
project(ThreeD LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(OpenGL REQUIRED)
#find_package(glfw3 REQUIRED)
#find_package(Threads REQUIRED)

add_executable(res main.cpp glad/glad.c)

# Link everything explicitly to avoid "Undefined Reference"
target_link_libraries(res PRIVATE 
    OpenGL::GL 
    #   glfw
    #    Threads::Threads
    #${CMAKE_DL_LIBS}
)
