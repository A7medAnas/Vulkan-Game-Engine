#include "lve_pipeline.hpp"

#include <fstream>
#include <iostream>

namespace lve {

    LvePipeline::LvePipeline(
            LveDevice& device,
            const std::string& vertFilePath,
            const std::string& fragFilePath,
            const PipelineConfigInfo& configinfo):
            lveDevice{device} {
        createGraphicsPipeline(vertFilePath, fragFilePath, configinfo);
    }

    std::vector<char> LvePipeline::readFile(const std::string& filepath) {

        std::ifstream file{filepath, std::ios::ate | std::ios::binary};

        if (!file.is_open()) {
            throw std::runtime_error("failed to open file: " + filepath);
        }

        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();
        return buffer;
    }

    void LvePipeline::createGraphicsPipeline(
        const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configinfo) {
        auto vertCode = readFile(vertFilePath);
        auto fragCode = readFile(fragFilePath);

        std::cout << "Vertex Shader Code Size: " << vertCode.size() << '\n';
        std::cout << "Fragment Shader Code Size: " << fragCode.size() << '\n';
    }

    void LvePipeline::createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule) {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const u_int32_t*>(code.data());

        if(vkCreateShaderModule(lveDevice.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS) {
            throw std::runtime_error("failed to create shader module") ;
        }
    }

    PipelineConfigInfo LvePipeline::defaultPipelineConfigInfo(u_int32_t width, u_int32_t height) {
        PipelineConfigInfo configInfo{};

        return configInfo;
    }

}