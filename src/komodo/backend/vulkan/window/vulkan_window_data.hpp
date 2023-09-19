#pragma once

#include <volk.h>

#include "komodo/backend/vulkan/instance/vulkan_instance_data.hpp"

struct GLFWwindow;

namespace Komodo {

struct VulkanWindowData {
  VkSurfaceKHR surface;
  VkSwapchainKHR swapchain;
  GLFWwindow* glfw_window;
};

}
