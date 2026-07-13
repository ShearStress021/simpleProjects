cmake_minimum_required(VERSION 3.24) # FetchContent with integrated find_package() is available in 3.24+
project(ArmagaddonClash)


# Generate compile_commands.json
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Dependencies
include(FetchContent)

set(RAYLIB_VERSION 5.5)
FetchContent_Declare(
	raylib
	GIT_REPOSITORY https://github.com/raysan5/raylib.git
	GIT_TAG 5.5
	GIT_SHALLOW TRUE
	)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

#set(RAYGUI_VERSION 3.2)
#FetchContent_Declare(
#	raygui
#	URL https://github.com/raysan5/raygui/archive/refs/tags/${RAYGUI_VERSION}.tar.gz
#	FIND_PACKAGE_ARGS ${RAYGUI_VERSION} EXACT

#	)
#set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
#FetchContent_MakeAvailable(raygui)

# 1. Create a "dummy" target for raygui
#add_library(raygui INTERFACE)

# 2. Tell CMake where the raygui.h file is located
#target_include_directories(raygui INTERFACE ${raygui_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
#file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/main.cpp)
add_executable(res ${SOURCES})
#add_executable(res main.cpp)

target_link_libraries(res raylib)
#target_link_libraries(res raygui)
