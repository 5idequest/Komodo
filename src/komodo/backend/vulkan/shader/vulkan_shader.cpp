#include "vulkan_shader.hpp"

#include <volk.h>

#include "komodo/shader/shader.hpp"
#include "komodo/backend/vulkan/debug/vulkan_call.hpp"
#include "komodo/backend/vulkan/instance/vulkan_instance_data.hpp"

namespace Komodo {

static VkShaderModule CreateShaderModule(VulkanInstanceData* instance, const std::vector<uint32_t>& spv) {
  VkShaderModuleCreateInfo shader_info { };
  shader_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  shader_info.codeSize = spv.size();
  shader_info.pCode = spv.data();
  VkShaderModule shader_module;
  VK_CALL(vkCreateShaderModule(instance->device, &shader_info, instance->allocator, &shader_module));
  return shader_module;
}

VulkanShader::VulkanShader(VulkanInstanceData* instance, const ShaderCreateInfo& shader_info) {
  auto spv = LoadShaderModules(shader_info);
  
  std::vector<VkShaderModule> shader_modules;
  
  if (spv->vert) {
    shader_modules.push_back(CreateShaderModule(instance, *spv->vert));
  }
}

void VulkanShader::Bind() {

}

}
