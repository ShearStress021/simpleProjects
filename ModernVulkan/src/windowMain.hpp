#pragma once
#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan.hpp>

#include <SDL3/SDL.h>
#include <iostream>
#include <cstdint>



class MainWindow {
	
	public:
		bool init();
		void run();
		
	private:
		SDL_Window * window = nullptr;
		std::uint16_t width{1280};
		std::uint16_t height{720};
	
		// vulkan
		VkInstance instanceVK{VK_NULL_HANDLE};



	private:

		//class subroutines private
		void Error(const char* msg) const;

		bool initVulkan();
		bool createVulkanInstance();

		

};
