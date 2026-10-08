#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>
#include "renderer.hpp"
#include <iostream>

Renderer::Renderer(){

}
Renderer::~Renderer(){
	cleanUp();
}
void Renderer::showError(const std::string_view message) const{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message.data(),window);
}


void Renderer::cleanUp(){

	vkDeviceWaitIdle(device);

	if(timelineSemaphore) vkDestroySemaphore(device,timelineSemaphore,nullptr);


	for(auto &res: frameResources){
		vkDestroySemaphore(device, res.imageAcquiredSemaphore,nullptr);
		vkDestroyCommandPool(device,res.commandPool, nullptr);
	}


	if(pipelineLayout) vkDestroyPipelineLayout(device,pipelineLayout,nullptr);
	if(pipeline) vkDestroyPipeline(device,pipeline,nullptr);


	if(vertShader) vkDestroyShaderModule(device, vertShader,nullptr);
	if(fragShader) vkDestroyShaderModule(device, fragShader,nullptr);

	destroySwapchain();

	if(vmaAllocator){
		vmaDestroyAllocator(vmaAllocator);
	}
	if(surface){
		vkDestroySurfaceKHR(instance,surface,nullptr);

	}

	if(device){
		vkDestroyDevice(device, nullptr);
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

		display();
	}

}

bool Renderer::initVulkan(){
	if(!createInstance() ){
		showError("Vulkan instance wasn't created");
		return false;
	}
	if(!createSurface()){
		showError("Vulkan Surface failed to create");
		return false;
	}

	if(physicalDevice = findPhysicalDevice(); !physicalDevice) {
		showError("Physical Device wasn't found!!!");
		return false;

	}

	if(!findGraphicQueue()){
		showError("Invalid Compatible Graphical Queue");
		return false;
	}
	if(!createDevice(physicalDevice)){
		showError("Device wasn't created!!");
		return false;
	}
	if(!initializeVMA()){
		showError("VMA was not allocated!!!");
		return false;
	}
	if(!createShader()){
		showError("Failded to created shader modules");
		return false;
	}
	if(createSwapchain(width, height)){
		showError("swapchain failed to be created!!!");
		return false;
	}

	if(pipeline = createGraphicsPipeline(); !pipeline) {
		showError("Unable to create vulkan pipeline");
		return false;
	}

	if(!createSyncResources()){
		showError("Failed to create sync resourcess");
		return false;
	}
	if(!createCommandBuffers()){
		showError("Failed to create command buffer!!!");
		return false;
	}

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

bool Renderer::findGraphicQueue(){

	uint32_t queueCount{};
	vkGetPhysicalDeviceQueueFamilyProperties2(physicalDevice,&queueCount,nullptr);
	std::vector<VkQueueFamilyProperties2> queueProps(queueCount, {VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2});
	vkGetPhysicalDeviceQueueFamilyProperties2(physicalDevice,&queueCount,queueProps.data());

	for(size_t i{}; i < queueProps.size(); ++i){
		VkBool32 supportPresent{false};
		vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &supportPresent);
		const auto &props = queueProps[i];

		if(props.queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT && supportPresent){
			gfxQueueFamIdx = i;
			return true;
		}
	}

	return false;
}

bool Renderer::createDevice(VkPhysicalDevice physicalDevice){
	float queuePriority{1.f};
	std::vector<uint32_t> queueFamily{gfxQueueFamIdx};

	VkDeviceQueueCreateInfo deviceQueueInfo {
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		.queueFamilyIndex = gfxQueueFamIdx,
		.queueCount = 1,
		.pQueuePriorities = &queuePriority
	};

	VkPhysicalDeviceVulkan14Features supportedFeatures14{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES, .pNext = nullptr  };
	VkPhysicalDeviceVulkan13Features supportedFeatures13{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES, .pNext = &supportedFeatures14  };
	VkPhysicalDeviceVulkan12Features supportedFeatures12{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES, .pNext = &supportedFeatures13  };
	VkPhysicalDeviceFeatures2 supportedFeatures{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2, .pNext = &supportedFeatures12  };
	vkGetPhysicalDeviceFeatures2(physicalDevice, &supportedFeatures);

	// check if what we need is supported
	if (!supportedFeatures13.dynamicRendering || !supportedFeatures13.synchronization2 ||
			!supportedFeatures12.timelineSemaphore)
	{
		showError("Physical device doesn't meet the feature requirements");
		return false;
	}
	VkPhysicalDeviceVulkan14Features features14
	{
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES,
			.pNext = nullptr,

	};
	VkPhysicalDeviceVulkan13Features features13
	{
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES,
			.pNext = &features14,
			.synchronization2 = VK_TRUE,
			.dynamicRendering = VK_TRUE,

	};
	VkPhysicalDeviceVulkan12Features features12
	{
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
			.pNext = &features13,
			.timelineSemaphore = VK_TRUE

	};
	VkPhysicalDeviceFeatures2 features{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2, .pNext = &features12  };
	const std::vector<const char *> deviceExtensions{ VK_KHR_SWAPCHAIN_EXTENSION_NAME  };
	VkDeviceCreateInfo devCreateInfo
	{
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
			.pNext = &features,
			.queueCreateInfoCount = 1,
			.pQueueCreateInfos = &deviceQueueInfo,
			.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size()),
			.ppEnabledExtensionNames = deviceExtensions.data(),
			.pEnabledFeatures = nullptr // features struct chain is set in pNext
										// 	
	};

	if (vkCreateDevice(physicalDevice, &devCreateInfo, nullptr, &device) != VK_SUCCESS)
	{
		showError("Couldn't create the logical GPU device");
		return false;

	}

	vkGetDeviceQueue(device, gfxQueueFamIdx, 0, &gfxQueue);
	if (!gfxQueue)
	{
		showError("Couldn't get the graphics queue");
		return false;

	}



	return true;
}

bool Renderer::initializeVMA(){
	VmaVulkanFunctions vmaFuncInfo{};
	VmaAllocatorCreateInfo vmaAllocInfo{
		.flags = VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT,
		.physicalDevice = physicalDevice,
		.device = device,
		.pVulkanFunctions = &vmaFuncInfo,
		.instance = instance,
		.vulkanApiVersion = VK_API_VERSION_1_4
	};

	if(vmaCreateAllocator(&vmaAllocInfo, &vmaAllocator) != VK_SUCCESS){
		showError("Unable to create Vulkan memory Allocator");
		return false;

	}
	return true;
}

bool Renderer::createSwapchain(uint32_t width, uint32_t height){
	swapchainWidth = width;
	swapchainHeight = height;

	VkSurfaceCapabilitiesKHR surfaceCaps{};

	if(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice,surface,&surfaceCaps) != VK_SUCCESS){
		showError("Couldn't get the surface capabilities");
		return false;
	}

	VkSwapchainCreateInfoKHR swapchainCreateInfo {
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.surface = surface,
		.minImageCount = surfaceCaps.minImageCount,
		.imageFormat = swapchainFormat,
		.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
		.imageExtent{.width = swapchainWidth, .height = swapchainHeight},
		.imageArrayLayers = 1,
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		.presentMode = VK_PRESENT_MODE_FIFO_KHR
	};

	if(vkCreateSwapchainKHR(device, &swapchainCreateInfo, nullptr, &swapchain) != VK_SUCCESS){
 		showError("Failed to create swapchain!!");
		return false;
	}
	uint32_t imageCount {};
	vkGetSwapchainImagesKHR(device,swapchain,&imageCount,nullptr);
	swapchainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(device,swapchain,&imageCount,swapchainImages.data());
	swapchainImageViews.resize(imageCount);

	for(size_t i{}; i < swapchainImages.size(); i++){

		VkImageViewCreateInfo imageViewInfo {
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			.image = swapchainImages[i],
			.viewType = VK_IMAGE_VIEW_TYPE_2D,
			.format = swapchainFormat,
			.subresourceRange {
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
				.levelCount = 1,
				.layerCount = 1
			}
		};

		if(vkCreateImageView(device, &imageViewInfo, nullptr, &swapchainImageViews[i]) != VK_SUCCESS){
			showError("Error in creating swapchain image view");
			return false;
		}
	}

	renderCompleteSemaphores.resize(swapchainImages.size());
	for(VkSemaphore &semaphore: renderCompleteSemaphores){
		VkSemaphoreCreateInfo semaphoreInfo {.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};
		if(vkCreateSemaphore(device,&semaphoreInfo,nullptr,&semaphore) != VK_SUCCESS){
			showError("Error creating the render complete semaphore!!!");
			return false;
		}

	}

	VkImageCreateInfo depthCreateInfo {
		.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
		.imageType = VK_IMAGE_TYPE_2D,
		.format = depthFormat,
		.extent{.width = swapchainWidth, .height = swapchainHeight, .depth = 1},
		.mipLevels = 1,
		.arrayLayers = 1,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.tiling = VK_IMAGE_TILING_OPTIMAL,
		.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
		.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
	};

	VmaAllocationCreateInfo allocInfo {
		.flags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT,
		.usage = VMA_MEMORY_USAGE_AUTO
	};

	if(vmaCreateImage(vmaAllocator, &depthCreateInfo, &allocInfo, &dImage, &dImageAllocation, nullptr) != VK_SUCCESS){
		showError("Error allocating depth image!!!");
		return false;
	}

	VkImageViewCreateInfo deptImgViewInfo {
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.image = dImage,
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.format = depthFormat,
		.subresourceRange{.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT, .levelCount = 1, .layerCount =1},
	};
	
	if(vkCreateImageView(device,&deptImgViewInfo,nullptr, &dImageView) != VK_SUCCESS){
 		showError("Error in creating Depth");
		return false;
	}
	return true;
}

void Renderer::destroySwapchain(){
	for(VkImageView swapchainImageView: swapchainImageViews){
		vkDestroyImageView(device,swapchainImageView,nullptr);
	}
	swapchainImageViews.clear();

	for(VkSemaphore &semaphore: renderCompleteSemaphores){
		vkDestroySemaphore(device,semaphore,nullptr);
	}
	renderCompleteSemaphores.clear();

	if(swapchain){
		vkDestroySwapchainKHR(device,swapchain,nullptr);
		swapchain = nullptr;
	}
	if(dImageView){
		vkDestroyImageView(device,dImageView,nullptr);
		vmaDestroyImage(vmaAllocator,dImage,dImageAllocation);
		dImageView = nullptr;
	}


}

VkShaderModule Renderer::createShaderModule(const std::string &filename) const {
	const std::string shaderPath {"shaders/" + filename};
	const auto source = readTextFile(shaderPath);
	if(source.empty()){
		showError("shader File doesn't exist: " +shaderPath);
		return nullptr;
	}
	VkShaderModuleCreateInfo moduleCreateInfo {
		.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.codeSize = source.size() ,
		.pCode = reinterpret_cast<const uint32_t*>(source.data())
	};
	VkShaderModule shaderModule{nullptr};
	if(vkCreateShaderModule(device,&moduleCreateInfo,nullptr,&shaderModule) != VK_SUCCESS){
		showError("Error create Shader module");
		return nullptr;
	}
	return shaderModule;
}
bool Renderer::createShader(){
	if(vertShader = createShaderModule("shader.vert.spv"); !vertShader) return false;
	if(fragShader = createShaderModule("shader.frag.spv"); !fragShader) return false;
	return true;
}

VkPipeline Renderer::createGraphicsPipeline(){
	VkPipelineLayoutCreateInfo createPipelineInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
		.setLayoutCount = 0,
		.pushConstantRangeCount = 0,
	};

	if(vkCreatePipelineLayout(device, &createPipelineInfo, nullptr, &pipelineLayout) != VK_SUCCESS){
		showError("Unable to create the pipeline Layout!!!!!");
		return nullptr;
	}

	const char* entryPoint{"main"};

	std::vector<VkPipelineShaderStageCreateInfo> shaderStages {
		{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			.stage = VK_SHADER_STAGE_VERTEX_BIT,
			.module = vertShader,
			.pName = entryPoint

		},
		{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			.stage = VK_SHADER_STAGE_FRAGMENT_BIT,
			.module = fragShader,
			.pName = entryPoint

		}

	};

	VkPipelineVertexInputStateCreateInfo vertInputInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO
	};

	VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
		.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST

	};

	VkPipelineDepthStencilStateCreateInfo depthStencilInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
		.depthTestEnable = VK_TRUE,
		.depthWriteEnable = VK_TRUE,
		.depthCompareOp = VK_COMPARE_OP_LESS,
		.stencilTestEnable = VK_FALSE
	};

	VkPipelineViewportStateCreateInfo viewPortInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
		.viewportCount = 1,
		.pViewports = nullptr,
		.scissorCount = 1,
		.pScissors = nullptr

	};

	VkPipelineRasterizationStateCreateInfo rasterCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
		.polygonMode = VK_POLYGON_MODE_FILL,
		.cullMode = VK_CULL_MODE_BACK_BIT,
		.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE,
		.lineWidth = 1.0f
	};

	VkPipelineMultisampleStateCreateInfo multiSampleCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
		.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT
	};

	VkPipelineColorBlendAttachmentState attachState {
		.blendEnable = VK_FALSE,
		.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT |
			VK_COLOR_COMPONENT_A_BIT
	};

	VkPipelineColorBlendStateCreateInfo blendCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
		.attachmentCount = 1,
		.pAttachments = &attachState
	};

	std::vector<VkDynamicState> dynamicState {
		VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR
	};

	VkPipelineDynamicStateCreateInfo dynamicCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
		.dynamicStateCount = static_cast<uint32_t>(dynamicState.size()),
		.pDynamicStates = dynamicState.data()

	};

	VkPipelineRenderingCreateInfo renderCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO,
		.colorAttachmentCount = 1,
		.pColorAttachmentFormats = &swapchainFormat,
		.depthAttachmentFormat = depthFormat
	};
	VkGraphicsPipelineCreateInfo pipelineCreateInfo {
		.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
		.pNext = &renderCreateInfo,
		.stageCount = static_cast<uint32_t>(shaderStages.size()),
		.pStages = shaderStages.data(),
		.pVertexInputState = &vertInputInfo,
		.pInputAssemblyState = &inputAssemblyInfo,
		.pViewportState = &viewPortInfo,
		.pRasterizationState = &rasterCreateInfo,
		.pMultisampleState = &multiSampleCreateInfo,
		.pDepthStencilState = &depthStencilInfo,
		.pColorBlendState = &blendCreateInfo,
		.pDynamicState = &dynamicCreateInfo,
		.layout = pipelineLayout,
		.renderPass = VK_NULL_HANDLE
	};

	if(vkCreateGraphicsPipelines(device, nullptr, 1, &pipelineCreateInfo,nullptr, &pipeline) != VK_SUCCESS){
		showError("Error creating the pipeline!!!");
		return nullptr;

	}
	return pipeline;
}

bool Renderer::createSyncResources(){
	VkSemaphoreTypeCreateInfo semaphoreTypeInfo {
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
		.semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
		.initialValue = MaxFramesInFlight
	};

	VkSemaphoreCreateInfo semaphoreCreateInfo {
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		.pNext = &semaphoreTypeInfo
	};
	if (vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &timelineSemaphore) != VK_SUCCESS){
		showError("Unable to create the timeline Semaphore!!");
		return false;
	}
	for(FrameResources &res : frameResources){
		VkSemaphoreCreateInfo semaphoreInfo {.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};
		if(vkCreateSemaphore(device,&semaphoreInfo,nullptr,&res.imageAcquiredSemaphore) != VK_SUCCESS){
			showError("Error creating the per-frame image-acquire semaphore!!!");
			return false;
		}

	}

	return true;
}

bool Renderer::createCommandBuffers(){
	for(FrameResources &res: frameResources){
		VkCommandPoolCreateInfo createPoolInfo {
			.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
			.queueFamilyIndex = gfxQueueFamIdx,
		};
		if(vkCreateCommandPool(device,&createPoolInfo,nullptr,&res.commandPool) != VK_SUCCESS){
			showError("Unable to create command buffer pool!!!");
			return false;
		}

		VkCommandBufferAllocateInfo cmdAllocInfo {
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
			.commandPool = res.commandPool,
			.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
			.commandBufferCount = 1
		};

		if(vkAllocateCommandBuffers(device,&cmdAllocInfo,&res.commandbuffer) != VK_SUCCESS){
			showError("failed to allocate Command Buffer!!!");
			return false;
		}
	}

	return true;
}
void Renderer::display(){
	if(requireSwapchainRecreate){
		vkDeviceWaitIdle(device);
		destroySwapchain();
		createSwapchain(width, height);
		requireSwapchainRecreate = false;
	}

	const uint32_t frameresIdx = frameIdx++ % MaxFramesInFlight;
	const uint64_t signalVal { nextSignalValue };
	const uint64_t waitVal {signalVal - MaxFramesInFlight};

	VkSemaphoreWaitInfo waitInfo {
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
		.semaphoreCount = 1,
		.pSemaphores = &timelineSemaphore,
		.pValues = &waitVal
	};
	vkWaitSemaphores(device,&waitInfo,UINT64_MAX);
	FrameResources &res = frameResources[frameresIdx];
	vkResetCommandPool(device,res.commandPool,0);

	VkSemaphore imageAcquireSemaphore = frameResources[frameresIdx].imageAcquiredSemaphore;
	uint32_t imageIdx{};
	VkResult acquireResult = vkAcquireNextImageKHR(device,swapchain,UINT64_MAX,
			imageAcquireSemaphore,VK_NULL_HANDLE,&imageIdx);
	
	if(acquireResult == VK_SUBOPTIMAL_KHR) requireSwapchainRecreate = true;
	else if(acquireResult == VK_ERROR_OUT_OF_DATE_KHR) {
		requireSwapchainRecreate = true;
		return ;
	}

	VkCommandBufferBeginInfo commandBufBegin {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
	};

	vkBeginCommandBuffer(res.commandbuffer,&commandBufBegin);

	std::vector<VkImageMemoryBarrier2> layoutBarriers {
		{
			.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
			.srcStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
			.srcAccessMask = 0,
			.dstStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
			.dstAccessMask = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT,
			.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
			.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
			.image = swapchainImages[imageIdx],
			.subresourceRange {
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
				.baseMipLevel = 0,
				.levelCount = 1,
				.baseArrayLayer = 0,
				.layerCount = 1

			}
		},
		{
			.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
			.srcStageMask = VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT,
			.srcAccessMask = 0,
			.dstStageMask = VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT | 
				VK_PIPELINE_STAGE_2_LATE_FRAGMENT_TESTS_BIT,
			.dstAccessMask = VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
			.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
			.newLayout = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
			.image = dImage,
			.subresourceRange {
				.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT,
				.baseMipLevel = 0,
				.levelCount = 1,
				.baseArrayLayer = 0,
				.layerCount = 1

			}
			


		}
		

	};
	VkDependencyInfo dependencyInfo {
		.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
		.imageMemoryBarrierCount = static_cast<uint32_t>(layoutBarriers.size()),
		.pImageMemoryBarriers = layoutBarriers.data(),
	};

	vkCmdPipelineBarrier2(res.commandbuffer,&dependencyInfo);
	
	VkRenderingAttachmentInfo colorAttachInfo {
		.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
		.imageView = swapchainImageViews[imageIdx],
		.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
		.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
		.clearValue{.color{0.01f, 0.01f, 0.01f,1}},
	};

	VkRenderingAttachmentInfo depthAttachInfo {
		.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
		.imageView = dImageView,
		.imageLayout = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
		.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
		.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
		.clearValue{.depthStencil{1.0f, 0}}

	};
	VkRenderingInfo renderingInfo {
		.sType = VK_STRUCTURE_TYPE_RENDERING_INFO,
		.renderArea {
			.offset {.x = 0, .y = 0},
			.extent {.width = swapchainWidth, .height = swapchainHeight}
			},
		.layerCount = 1,
		.colorAttachmentCount = 1,
		.pColorAttachments = &colorAttachInfo,
		.pDepthAttachment = &depthAttachInfo,
	};

	vkCmdBeginRendering(res.commandbuffer, &renderingInfo);
	{
		VkViewport viewport {
			.x = 0, .y =0,
			.width = static_cast<float>(swapchainWidth),
			.height = static_cast<float>(swapchainHeight)
		};
		vkCmdSetViewport(res.commandbuffer, 0, 1,&viewport);

		VkRect2D scissor {
			.offset {.x = 0, .y=0},
			.extent{.width = swapchainWidth, .height = swapchainWidth}
		};
		vkCmdSetScissor(res.commandbuffer, 0,1,&scissor);
		vkCmdBindPipeline(res.commandbuffer,VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
		vkCmdDraw(res.commandbuffer,3,1,0,0);
		
	};
	vkCmdEndRendering(res.commandbuffer);
	
	VkImageMemoryBarrier2 presentLayoutBarrier {
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
		.srcStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
		.srcAccessMask = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT,
		.dstStageMask = VK_PIPELINE_STAGE_NONE,
		.dstAccessMask = 0,
		.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
		.subresourceRange {
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1
		}

	};

	VkDependencyInfo presentDepInfo {
		.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
		.imageMemoryBarrierCount = 1,
		.pImageMemoryBarriers = &presentLayoutBarrier
	};
	vkCmdPipelineBarrier2(res.commandbuffer,&presentDepInfo);
	vkEndCommandBuffer(res.commandbuffer);

	VkSemaphoreSubmitInfo imageAcquireWaitInfo {
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
		.semaphore = imageAcquireSemaphore,
		.stageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
	};

	std::vector<VkSemaphoreSubmitInfo> semaphoreSignals {
		{
			.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
			.semaphore = renderCompleteSemaphores[imageIdx],
			.stageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT
		},
		{
			.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
			.semaphore = timelineSemaphore,
			.value = signalVal,
			.stageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT
		}
	};
	VkCommandBufferSubmitInfo cmdSubmitInfo{
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO,
		.commandBuffer = res.commandbuffer
	};

	VkSubmitInfo2 submitInfo {
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.waitSemaphoreInfoCount = 1,
		.pWaitSemaphoreInfos = &imageAcquireWaitInfo,
		.commandBufferInfoCount = 1,
		.pCommandBufferInfos = &cmdSubmitInfo,
		.signalSemaphoreInfoCount = static_cast<uint32_t>(semaphoreSignals.size()),
		.pSignalSemaphoreInfos = semaphoreSignals.data(),
	};
	vkQueueSubmit2(gfxQueue,1,&submitInfo,VK_NULL_HANDLE);
	
	VkPresentInfoKHR presentInfo {
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &renderCompleteSemaphores[imageIdx],
		.swapchainCount = 1,
		.pSwapchains = &swapchain,
		.pImageIndices = &imageIdx,
		.pResults = nullptr
	};
	vkQueuePresentKHR(gfxQueue,&presentInfo);
}





