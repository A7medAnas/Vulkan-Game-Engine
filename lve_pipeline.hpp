#pragma once

#include "lve_device.hpp"

#include <string>
#include <vector>

namespace lve {

    struct PipelineConfigInfo {};

    class LvePipeline {

    public:
        LvePipeline(
            LveDevice& device,
            const std::string& vertFilePath,
            const std::string& fragFilePath,
            const PipelineConfigInfo& configinfo);

        ~LvePipeline() {}

        LvePipeline(const LvePipeline&) = delete;
        LvePipeline& operator =(const LvePipeline&) = delete;

        static PipelineConfigInfo defaultPipelineConfigInfo(u_int32_t width, u_int32_t height);

    private:
        static std::vector<char> readFile(const std::string& filepath);

        void createGraphicsPipeline(
            const std::string& vertFilePath,
            const std::string& fragFilePath,
            const PipelineConfigInfo& configinfo);
    
        void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

        LveDevice& lveDevice;
        VkPipeline graphicsPipeline;
        VkShaderModule vertShaderModule;
        VkShaderModule fragShaderModule;
    };
}