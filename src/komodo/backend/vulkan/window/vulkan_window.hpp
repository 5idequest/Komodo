#pragma once

#include "komodo/backend/glfw/window/glfw_window.hpp"
#include "komodo/backend/vulkan/instance/vulkan_instance_data.hpp"
#include "komodo/backend/vulkan/window/vulkan_window_data.hpp"

namespace Komodo {

class VulkanWindow : public GlfwWindow {
public:
  VulkanWindow(VulkanInstanceData& instance, const WindowCreateInfo& create_info);
  ~VulkanWindow();

private:
  VulkanWindowData window;
  VulkanInstanceData& instance;
};

}
