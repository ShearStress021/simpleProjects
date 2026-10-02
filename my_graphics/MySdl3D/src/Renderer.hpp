#pragma once


#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan.h>
#include <string>


class Renderer {
	
	public:
		Renderer();
		~Renderer();


		bool init();
		bool run();
	
	private:
		bool initVulkan();
		void showError(const std::string_view message);

	private:

		


};


