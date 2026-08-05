cmake_minimum_required(VERSION 3.10)
project(doom VERSION 1.0.0)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#include_directories(${PROJECT_SOURCE_DIR}/include)
#file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*/*.cpp)

# Dependencies
include(FetchContent)

# set(RAYLIB_VERSION 5.5)
FetchContent_Declare(
    freeglut 
    GIT_REPOSITORY https://github.com/freeglut/freeglut.git
    GIT_TAG v3.6.0
)

FetchContent_MakeAvailable(freeglut)

#set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

find_package(OpenGL REQUIRED)

#file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(doom main.c) 
#find_package(GLUT REQUIRED)
target_link_libraries(doom PRIVATE 
    OpenGL::GL
    freeglut::freeglut
)
