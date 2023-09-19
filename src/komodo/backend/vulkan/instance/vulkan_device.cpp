#include "vulkan_device.hpp"

#include "komodo/backend/vulkan/debug/vulkan_call.hpp"
#include "komodo/backend/vulkan/instance/vulkan_queue_family_indices.hpp"

namespace Komodo {
namespace Vulkan {

VkDevice CreateDevice(VulkanInstanceData& instance) {
  VkDeviceQueueCreateInfo queue_create_info { };
  queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  VulkanQueueFamilyIndices queue_families(instance.physical_device);
  queue_create_info.queueFamilyIndex = queue_families.graphics_family.value();
  queue_create_info.queueCount = 1;
  float queue_priority = 1.0f;
  queue_create_info.pQueuePriorities = &queue_priority;

  VkPhysicalDeviceFeatures device_features { };

  VkDeviceCreateInfo device_info { };
  device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  device_info.pQueueCreateInfos = &queue_create_info;
  device_info.queueCreateInfoCount = 1;
  device_info.pEnabledFeatures = &device_features;

  VkDevice device;
  VK_CALL(vkCreateDevice(instance.physical_device, &device_info, instance.allocator, &device));
  return device;
}

}
}