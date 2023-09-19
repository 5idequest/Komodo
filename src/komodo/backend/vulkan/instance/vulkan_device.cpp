#include "vulkan_device.hpp"

#include <set>
#include <vector>

#include "komodo/backend/vulkan/debug/vulkan_call.hpp"

namespace Komodo {
namespace Vulkan {

VkDevice CreateDevice(VulkanInstanceData& instance, const VulkanQueueFamilyIndices& queue_families) {
  std::set<uint32_t> unique_queue_families = {
    queue_families.graphics_family.value(),
    queue_families.present_family.value()
  };

  std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
  float queue_priority = 1.0f;

  for (uint32_t queue_family : unique_queue_families) {
    VkDeviceQueueCreateInfo queue_create_info { };
    queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_info.queueFamilyIndex = queue_family;
    queue_create_info.queueCount = 1;
    queue_create_info.pQueuePriorities = &queue_priority;
    queue_create_infos.push_back(queue_create_info);
  }

  VkPhysicalDeviceFeatures device_features { };

  VkDeviceCreateInfo device_info { };
  device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  device_info.pQueueCreateInfos = queue_create_infos.data();
  device_info.queueCreateInfoCount = queue_create_infos.size();
  device_info.pEnabledFeatures = &device_features;

  VkDevice device;
  VK_CALL(vkCreateDevice(instance.physical_device, &device_info, instance.allocator, &device));
  volkLoadDevice(device);
  return device;
}

}
}
