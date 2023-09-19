#pragma once

#include <memory>

#include "komodo/backend/vulkan/instance/vulkan_instance_data.hpp"
#include "komodo/backend/vulkan/window/vulkan_window.hpp"

namespace Komodo {

class VulkanInstance {
public:
  VulkanInstance();
  ~VulkanInstance();

private:
  VulkanInstanceData instance;

public:
  std::shared_ptr<VulkanWindow> CreateWindow(const WindowCreateInfo& window_info = { });
};

}
