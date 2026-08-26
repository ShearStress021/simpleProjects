cmake_minimum_required(VERSION 3.14)
project(MyDoomEngine)

include(FetchContent)

FetchContent_Declare(
    freeglut
    GIT_REPOSITORY https://github.com/FreeGLUTProject/freeglut.git
    GIT_TAG        v3.4.0
)

set(FREEGLUT_BUILD_DEMOS OFF CACHE BOOL "" FORCE)
set(FREEGLUT_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5 CACHE STRING "")

FetchContent_MakeAvailable(freeglut)

find_package(OpenGL REQUIRED)
find_package(GLU REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${freeglut_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} OpenGL::GL OpenGL::GLU freeglut_static)
