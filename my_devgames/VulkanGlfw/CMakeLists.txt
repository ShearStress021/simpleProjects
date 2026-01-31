cmake_minimum_required(VERSION 3.10)
project(Vulkan LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)
find_package(Threads REQUIRED)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(res ${SOURCES})


target_link_libraries(res PRIVATE
    glfw
    Vulkan::Vulkan
	#    Threads::Threads
    ${CMAKE_DL_LIBS}
)
