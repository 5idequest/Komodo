#include "vulkan_shader.hpp"

#include "komodo/shader/shader.hpp"

namespace Komodo {

VulkanShader::VulkanShader(const ShaderCreateInfo& shader_info) {
  auto spv = LoadShaderModules(shader_info);
}

}
