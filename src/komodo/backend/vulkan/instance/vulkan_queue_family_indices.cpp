#include "vulkan_queue_family_indices.hpp"

#include <vector>

namespace Komodo {

VulkanQueueFamilyIndices::VulkanQueueFamilyIndices(VkPhysicalDevice physical_device) {
  uint32_t queue_family_count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, nullptr);
  std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, queue_families.data());

  for (int i = 0; i < queue_family_count; ++i) {
    if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      graphics_family = i;
    }

    if (IsComplete()) {
      break;
    }
  }
}

bool VulkanQueueFamilyIndices::IsComplete() const {
  return graphics_family.has_value();
}

}
