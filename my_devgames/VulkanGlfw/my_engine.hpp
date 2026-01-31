namespace lve {

	struct SwapChainSupportDetails {
	  VkSurfaceCapabilitiesKHR capabilities;
	  std::vector<VkSurfaceFormatKHR> formats;
	  std::vector<VkPresentModeKHR> presentModes;
	};

	struct QueueFamilyIndices {
	  uint32_t graphicsFamily;
	  uint32_t presentFamily;
	  bool graphicsFamilyHasValue = false;
	  bool presentFamilyHasValue = false;
	  bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue;  }
	};
	

}
