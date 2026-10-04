#include "renderer.hpp"

Renderer::Renderer(){

}
Renderer::~Renderer(){
	cleanUp();
}
void Renderer::showError(const std::string_view message){
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message.data(),window);
}


void Renderer::cleanUp(){


	if(surface){
		vkDestroySurfaceKHR(instance,surface,nullptr);
	}

	if(instance){
		vkDestroyInstance(instance, nullptr);
	}

	if(window){
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
}


bool Renderer::init(){
	if(!SDL_InitSubSystem(SDL_INIT_VIDEO)){
		showError("SDL init Failed!!!");
		return false;
	}
	window = SDL_CreateWindow("vulkan + SDL3",width, height,SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);

	if(!window){
		showError("Window not created!!!");
		return false;
	}
	if(!initVulkan()){
		showError("Vulkan initialization failed!!!");
		return false;
	}

	return true;

}

void Renderer::run(){

	while(running){
		SDL_Event e{};
		while (SDL_PollEvent(&e)){

			if (e.type == SDL_EVENT_QUIT) running = false;

		}

	}

}

bool Renderer::initVulkan(){
	if(!createInstance() && !createSurface() ){
		return false;
	}

	if(physicalDevice = findPhysicalDevice(); !physicalDevice) return false;
	return true;
}

bool Renderer::createInstance(){
	VkApplicationInfo appInfo{
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = "vulkan sdl",
		.apiVersion = VK_API_VERSION_1_4,
	};

	uint32_t extCount  = 0;
	const char *const *extensions = SDL_Vulkan_GetInstanceExtensions(&extCount);
	std::vector<const char*> requestLayers {
		"VK_LAYER_KHRONOS_validation"
	};
	VkInstanceCreateInfo createInfo{
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &appInfo,
		.enabledLayerCount = static_cast<uint32_t>(requestLayers.size()),
		.ppEnabledLayerNames = requestLayers.data(),
		.enabledExtensionCount = extCount,
		.ppEnabledExtensionNames  = extensions

	};

	if(vkCreateInstance(&createInfo,nullptr,&instance) != VK_SUCCESS){
		showError("vulkan Instance not created!!!");
		return false;
	}

	return true;
}

bool Renderer::createSurface(){
	if(!SDL_Vulkan_CreateSurface(window,instance,nullptr,&surface)){
		showError("vulkan surface not created!!!");
		return false;

	} 
	return true;
}

VkPhysicalDevice Renderer::findPhysicalDevice(){
	uint32_t physicalDeviceCount {};
	vkEnumeratePhysicalDevices(instance,&physicalDeviceCount,nullptr);
	std::vector<VkPhysicalDevice> devices(physicalDeviceCount);

	vkEnumeratePhysicalDevices(instance,&physicalDeviceCount,devices.data());

	VkPhysicalDevice physicalDevice{nullptr};

	if(physicalDeviceCount){
		physicalDevice = devices[0];
		
		for(auto &phyDev: devices){
			VkPhysicalDeviceProperties properties{};
			vkGetPhysicalDeviceProperties(physicalDevice,&properties);

			if(properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU){
				physicalDevice = phyDev;
				break;
			}
				
		}

	}

	uint32_t formatCount {};
	vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice,surface,&formatCount,nullptr);
	std::vector<VkSurfaceFormatKHR> surfaceFormats(formatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice,surface,&formatCount,surfaceFormats.data());

	bool formatSupported{false};
	for(const VkSurfaceFormatKHR &surFormat: surfaceFormats){
		if(surFormat.format == swapchainFormat) {
			formatSupported = true;
			break;
		}
	}

	if(!formatSupported){
		showError("Requested swapchain!!!");
		return nullptr;

	}



	return physicalDevice;
}


