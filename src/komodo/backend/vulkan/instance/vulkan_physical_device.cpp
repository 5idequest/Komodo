#include "vulkan_physical_device.hpp"

#include <cstdint>
#include <vector>

#include <volk.h>

#include "komodo/backend/vulkan/instance/vulkan_queue_family_indices.hpp"
#include "komodo/debug/assert.hpp"

namespace Komodo {
namespace Vulkan {

static int RateDeviceSuitability(VkPhysicalDevice physical_device) {
  VulkanQueueFamilyIndices queue_families(physical_device);

  if (!queue_families.IsComplete()) {
    return 0;
  }

  VkPhysicalDeviceProperties device_properties;
  VkPhysicalDeviceFeatures device_features;
  vkGetPhysicalDeviceProperties(physical_device, &device_properties);
  vkGetPhysicalDeviceFeatures(physical_device, &device_features);

  int score = 1;

  // Discrete GPUs have a significant performance advantage
  if (device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
    score += 1000;
  }

  // Maximum possible size of textures affects graphics quality
  score += device_properties.limits.maxImageDimension2D;

  return score;
}

VkPhysicalDevice ChoosePhysicalDevice(VulkanInstanceData& instance) {
  VkPhysicalDevice physical_device = VK_NULL_HANDLE;
  uint32_t device_count = 0;

  vkEnumeratePhysicalDevices(instance.instance, &device_count, nullptr);
  KM_ASSERT(device_count, "Failed to find a Vulkan-capable GPU");
  std::vector<VkPhysicalDevice> devices(device_count);
  vkEnumeratePhysicalDevices(instance.instance, &device_count, devices.data());

  int highest_score = 0;
  for (const auto& device : devices) {
    int device_score = RateDeviceSuitability(device);
    if (device_score > highest_score) {
      physical_device = device;
      highest_score = device_score;
    }
  }

  KM_ASSERT(physical_device, "Failed to find a suitable GPU");
  return physical_device;
}

}
}