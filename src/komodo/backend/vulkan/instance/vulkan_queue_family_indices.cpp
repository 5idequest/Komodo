#include "vulkan_queue_family_indices.hpp"

#include <vector>

namespace Komodo {

VulkanQueueFamilyIndices::VulkanQueueFamilyIndices(VkPhysicalDevice physical_device, VkSurfaceKHR surface) {
  uint32_t queue_family_count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, nullptr);
  std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, queue_families.data());

  for (int i = 0; i < queue_family_count; ++i) {
    VkBool32 graphics_support = queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT;
    VkBool32 present_support = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, i, surface, &present_support);
  
    if (graphics_support) {
      graphics_family = i;
    }
    if (present_support) {
      present_family = i;
    }
    if (graphics_support && present_support) {
      return;
    }
  }


}

bool VulkanQueueFamilyIndices::IsComplete() const {
  return graphics_family.has_value() && present_family.has_value();
}

}
