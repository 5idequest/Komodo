#pragma once

#include <vector>

#include <volk.h>

namespace Komodo {

struct VulkanSwapchainSupportDetails {
  VulkanSwapchainSupportDetails(VkPhysicalDevice physical_device, VkSurfaceKHR surface);

  bool IsAdequate() const;

  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> present_modes;
};

}
