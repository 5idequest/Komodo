#pragma once

#include <memory>

#include "komodo/backend/vulkan/window/vulkan_window.hpp"
#include "komodo/backend/vulkan/shader/vulkan_shader.hpp"

namespace Komodo {

struct VulkanInstanceData;

class VulkanInstance {
public:
  VulkanInstance();
  ~VulkanInstance();

private:
  VulkanInstanceData* instance;

public:
  std::shared_ptr<VulkanWindow> CreateWindow(const WindowCreateInfo& window_info = { });
  std::shared_ptr<VulkanShader> CreateShader(const ShaderCreateInfo& shader_info = { });
};

}
