cmake_minimum_required(VERSION 3.21)
project(VulkanSDL)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



include(FetchContent)
set(FETCHCONTENT_QUIET OFF)


# Vulkan SDK
find_package(Vulkan REQUIRED)

#SDL3 fof windowing
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL3_DISABLE_INSTALL ON CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
	SDL3
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG        release-3.2.0
	GIT_SHALLOW    TRUE
	)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
FetchContent_MakeAvailable(SDL3)

# GLM for the Math
FetchContent_Declare(
	glm
	GIT_REPOSITORY https://github.com/g-truc/glm.git
	GIT_TAG        1.0.1
	GIT_SHALLOW    TRUE
	)
FetchContent_MakeAvailable(glm)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(res ${SOURCES})

#add_executable(res src/main.cpp)
target_link_libraries(res PRIVATE
	SDL3::SDL3
	Vulkan::Vulkan
	glm::glm
	)












