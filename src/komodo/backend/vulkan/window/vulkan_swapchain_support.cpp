#include "vulkan_swapchain_support.hpp"

#include <algorithm>

#include <GLFW/glfw3.h>

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

VkSurfaceFormatKHR VulkanSwapchainSupportDetails::ChooseSurfaceFormat() const {
  for (const auto& format : formats) {
    if (format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
      return format;
    }
  }

  return formats[0];
}

VkPresentModeKHR VulkanSwapchainSupportDetails::ChooseSwapPresentMode() const {
  for (const auto& present_mode : present_modes) {
    if (present_mode == VK_PRESENT_MODE_MAILBOX_KHR) {
      return present_mode;
    }
  }
  
  return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanSwapchainSupportDetails::ChooseSwapExtent(GLFWwindow* glfw_window) const {
  if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
    return capabilities.currentExtent;
  } else {
    int width, height;
    glfwGetFramebufferSize(glfw_window, &width, &height);
    
    VkExtent2D actual_extent = { width, height };
    
    actual_extent.width = std::clamp(actual_extent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
    actual_extent.height = std::clamp(actual_extent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
    
    return actual_extent;
  }
}

}
