cmake_minimum_required(VERSION 3.24) # FetchContent with integrated find_package() is available in 3.24+
project(vulkansdl)


# Generate compile_commands.json
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Dependencies
include(FetchContent)

find_package(Vulkan REQUIRED)

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL3_DISABLE_INSTALL ON CACHE BOOL "" FORCE)
FetchContent_Declare(
	SDL3	
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG        release-3.2.0  
	GIT_SHALLOW TRUE

	)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(SDL3)
FetchContent_Declare(
	VulkanMemoryAllocator	
	GIT_REPOSITORY https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator 
	GIT_TAG       v3.3.0 
	GIT_SHALLOW TRUE

	)
FetchContent_MakeAvailable(VulkanMemoryAllocator)

#

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(res ${SOURCES})
#add_executable(res main.cpp)

target_link_libraries(res PRIVATE Vulkan::Vulkan SDL3::SDL3-static GPUOpen::VulkanMemoryAllocator)


#------ shader (compling with glslc)
find_program(GLSLC glslc HINTS $ENV{VULKAN_SDK}/Bin REQUIRED)

file(GLOB SHADER_SOURCES CONFIGURE_DEPENDS
	${CMAKE_SOURCE_DIR}/shaders/*.vert
	${CMAKE_SOURCE_DIR}/shaders/*.frag
	)

set(SPV_FILES "")
foreach(SHADER ${SHADER_SOURCES})
	get_filename_component(SHADER_NAME ${SHADER} NAME)
	set(SPV ${CMAKE_SOURCE_DIR}/shaders/${SHADER_NAME}.spv)
	add_custom_command(
		OUTPUT ${SPV}
		COMMAND ${GLSLC} ${SHADER} -o ${SPV}
		DEPENDS ${SHADER}
		COMMENT "Compiling ${SHADER_NAME}"
		)
	list(APPEND SPV_FILES ${SPV})
endforeach()

add_custom_target(shaders DEPENDS ${SPV_FILES})
add_dependencies(res shaders)









