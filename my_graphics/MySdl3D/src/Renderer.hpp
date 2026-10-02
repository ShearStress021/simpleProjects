#pragma once


#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <string>
#include <cstdint>
#include <vector>



class Renderer {
	
	public:
		Renderer();
		~Renderer();


		bool init();
		void run();
		void cleanUp();
	
	private:
		void showError(const std::string_view message);

		// vulkan methods
		// starter
		bool initVulkan();
		bool createInstance();
		bool createSurface();

		// devices
		VkPhysicalDevice findPhysicalDevice();

	private:
		SDL_Window* window{};
		uint16_t width{800};
		uint16_t height{600};
		bool running{true};

		// vulkan variables
		VkInstance instance{nullptr};
		VkSurfaceKHR surface{nullptr};
		VkPhysicalDevice physicalDevice{nullptr};

};


