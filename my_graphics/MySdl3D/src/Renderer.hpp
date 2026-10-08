#pragma once


#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <shaderc/shaderc.hpp>

#include <string>
#include <cstdint>
#include <vector>
#include <fstream>
#include <sstream>
#include <array>



struct VmaAllocator_T;
typedef struct VmaAllocator_T* VmaAllocator;
struct VmaAllocation_T;
typedef struct VmaAllocation_T* VmaAllocation;

struct FrameResources {
	VkCommandPool commandPool{VK_NULL_HANDLE};
	VkCommandBuffer commandbuffer{VK_NULL_HANDLE};
	VkSemaphore imageAcquiredSemaphore{VK_NULL_HANDLE};

};
class Renderer {
	
	public:
		Renderer();
		~Renderer();


		bool init();
		void run();
		void cleanUp();
	
	private:
		void showError(const std::string_view message) const;

		// vulkan methods
		// starter
		bool initVulkan();
		bool createInstance();
		bool createSurface();

		// devices
		VkPhysicalDevice findPhysicalDevice();
		bool findGraphicQueue();
		bool createDevice(VkPhysicalDevice physicalDevice);
		// allocator
		bool initializeVMA();

		//swapchain
		bool createSwapchain(uint32_t width, uint32_t height);
		void destroySwapchain();

		// Reading shader files
		VkShaderModule createShaderModule(const std::string &filename) const;
		bool createShader();

		//pipeline
		VkPipeline createGraphicsPipeline();

		//synchrozation and frame
		bool createSyncResources();
		bool createCommandBuffers();


		void display();

		static std::vector<char> readTextFile(const std::string &filename) {

			std::ifstream file(filename, std::ios::ate | std::ios::binary);

			if(!file.is_open()){
				throw std::runtime_error("failed to open file");
			}
			size_t fileSize = (size_t)file.tellg();
			std::vector<char> buffer(fileSize);
			file.seekg(0);
			file.read(buffer.data(), fileSize);
			file.close();
			return buffer;
		}

	private:
		SDL_Window* window{};
		uint16_t width{800};
		uint16_t height{600};
		bool running{true};
		constexpr static uint32_t MaxFramesInFlight{2};
		constexpr static VkFormat swapchainFormat{VK_FORMAT_B8G8R8A8_SRGB};
		constexpr static VkFormat depthFormat{ VK_FORMAT_D32_SFLOAT  };
		uint64_t frameIdx{};
		uint64_t nextSignalValue{MaxFramesInFlight + 1};

		// vulkan variables
		VkInstance instance{VK_NULL_HANDLE};
		VkSurfaceKHR surface{VK_NULL_HANDLE};
		VkPhysicalDevice physicalDevice{VK_NULL_HANDLE};
		VkDevice device{VK_NULL_HANDLE};

		//queue -s
		uint32_t gfxQueueFamIdx{UINT32_MAX};
		VkQueue gfxQueue{VK_NULL_HANDLE};

		// Allocator
		VmaAllocator vmaAllocator{VK_NULL_HANDLE};

		//swapchain
		VkSwapchainKHR swapchain{VK_NULL_HANDLE};
		std::vector<VkImage> swapchainImages{};
		std::vector<VkImageView> swapchainImageViews{};
		std::vector<VkSemaphore> renderCompleteSemaphores{};
		bool requireSwapchainRecreate{false};
		uint32_t swapchainWidth{};
		uint32_t swapchainHeight{};


		// Image
		VkImage dImage{VK_NULL_HANDLE};
		VkImageView  dImageView{VK_NULL_HANDLE};
		VmaAllocation dImageAllocation{VK_NULL_HANDLE};

		//Shader module
		VkShaderModule vertShader{VK_NULL_HANDLE};
		VkShaderModule fragShader{VK_NULL_HANDLE};




		// Graphics pipeline
		VkPipelineLayout pipelineLayout{VK_NULL_HANDLE};
		VkPipeline pipeline{VK_NULL_HANDLE};

		// frame and synchrozation
		VkSemaphore timelineSemaphore{VK_NULL_HANDLE};
		std::array<FrameResources, MaxFramesInFlight> frameResources;





};


