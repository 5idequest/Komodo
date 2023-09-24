#include "vulkan_shader.hpp"

#include <volk.h>

#include "komodo/shader/shader.hpp"
#include "komodo/backend/vulkan/debug/vulkan_call.hpp"
#include "komodo/backend/vulkan/instance/vulkan_instance_data.hpp"

namespace Komodo {

static VkShaderModule CreateShaderModule(VulkanInstanceData* instance, const std::vector<uint32_t>& spv) {
  VkShaderModuleCreateInfo shader_info { };
  shader_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  shader_info.codeSize = spv.size() * sizeof(uint32_t);
  shader_info.pCode = spv.data();
  VkShaderModule shader_module;
  VK_CALL(vkCreateShaderModule(instance->device, &shader_info, instance->allocator, &shader_module));
  return shader_module;
}

static VkPipelineShaderStageCreateInfo CreateShaderStageCreateInfo(VkShaderModule module, VkShaderStageFlagBits stage) {
  VkPipelineShaderStageCreateInfo shader_stage_info { };
  shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  shader_stage_info.stage = stage;
  shader_stage_info.module = module;
  shader_stage_info.pName = "main";
  return shader_stage_info;
}

VulkanShader::VulkanShader(VulkanInstanceData* instance, const ShaderCreateInfo& shader_info) {
  auto spv = LoadShaderModules(shader_info);
  
  std::vector<VkShaderModule> shader_modules;
  std::vector<VkPipelineShaderStageCreateInfo> shader_stages;
  if (spv->vert) {
    VkShaderModule module = CreateShaderModule(instance, *spv->vert);
    shader_modules.push_back(module);
    shader_stages.push_back(std::move(CreateShaderStageCreateInfo(module, VK_SHADER_STAGE_VERTEX_BIT)));
  }
  if (spv->frag) {
    VkShaderModule module = CreateShaderModule(instance, *spv->frag);
    shader_modules.push_back(module);
    shader_stages.push_back(std::move(CreateShaderStageCreateInfo(module, VK_SHADER_STAGE_FRAGMENT_BIT)));
  }
  
  for (auto shader_module : shader_modules) {
    vkDestroyShaderModule(instance->device, shader_module, instance->allocator);
  }
}

void VulkanShader::Bind() {

}

}
