#include "vulkan_swapchain_support.hpp"

namespace Komodo {

VulkanSwapchainSupportDetails::VulkanSwapchainSupportDetails(VkPhysicalDevice physical_device, VkSurfaceKHR surface) {
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device, surface, &capabilities);

  uint32_t format_count;
  vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, surface, &format_count, nullptr);
  if (format_count > 0) {
    formats.resize(format_count);
    vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, surface, &format_count, formats.data());
  }

  uint32_t present_mode_count;
  vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, surface, &present_mode_count, nullptr);
  if (present_mode_count != 0) {
    present_modes.resize(present_mode_count);
    vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, surface, &present_mode_count, present_modes.data());
  }
}

bool VulkanSwapchainSupportDetails::IsAdequate() const {
  return !formats.empty() && !present_modes.empty();
}

}
