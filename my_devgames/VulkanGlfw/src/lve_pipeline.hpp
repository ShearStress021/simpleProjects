#pragma once
#include <string>
#include <vector>
#include "lve_device.hpp"


namespace lve {

	struct PipelineConfigInfo 
	{

	};

	class LvePipeLine {
		public:
			LvePipeLine(LveDevice& device, const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configInfo); 
			~LvePipeLine() {};
			LvePipeLine(const LvePipeLine& ) = delete;
			void operator=(const LvePipeLine&) = delete;
			static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);


		private:
			static std::vector<char> readFile(const std::string& filepath);
			void createGraphicPipeline(const std::string&  vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configInfo);
			void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

			LveDevice& lveDevice;
			VkPipeline graphicsPipeline;
			VkShaderModule vertShaderModule;
			VkShaderModule fragShaderModule;

	};

}
