#pragma once

#include <vector>

#include <volk.h>

#include "komodo/backend/vulkan/instance/vulkan_instance_data.hpp"

struct GLFWwindow;

namespace Komodo {

struct VulkanWindowData {
  GLFWwindow* glfw_window;
  VkSurfaceKHR surface;

  VkSwapchainKHR swapchain;
  std::vector<VkImage> swapchain_images;
  VkFormat swapchain_image_format;
  VkExtent2D swapchain_extent;
  std::vector<VkImageView> swapchain_image_views;
};

}
