#pragma once

#include <vector>

#include <volk.h>

struct GLFWwindow;

namespace Komodo {

struct VulkanSwapchainSupportDetails {
  VulkanSwapchainSupportDetails(VkPhysicalDevice physical_device, VkSurfaceKHR surface);

  bool IsAdequate() const;

  VkSurfaceFormatKHR ChooseSurfaceFormat() const;
  VkPresentModeKHR ChooseSwapPresentMode() const;
  VkExtent2D ChooseSwapExtent(GLFWwindow* glfw_window) const;

  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> present_modes;
};

}
