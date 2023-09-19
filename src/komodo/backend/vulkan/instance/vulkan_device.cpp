#include "vulkan_device.hpp"

#include <cstdint>
#include <set>
#include <vector>

#include "komodo/backend/vulkan/debug/vulkan_call.hpp"
#include "komodo/debug/assert.hpp"

namespace Komodo {
namespace Vulkan {

const static std::vector<const char*> kDeviceExtensions = {
  VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

static bool DeviceSupportsAllRequiredExtensions(VkPhysicalDevice physical_device) {
  uint32_t extension_count;
  vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &extension_count, nullptr);
  std::vector<VkExtensionProperties> available_extensions(extension_count);
  vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &extension_count, available_extensions.data());
  
  std::set<std::string> required_extensions(kDeviceExtensions.begin(), kDeviceExtensions.end());

  for (const auto& extension : available_extensions) {
    required_extensions.erase(extension.extensionName);
  }
  
  return required_extensions.empty();
}

static int RateDeviceSuitability(VkPhysicalDevice physical_device, VkSurfaceKHR surface) {
  // Absolute requirements for GPU suitability:

  // GPU must support both graphics and present
  VulkanQueueFamilyIndices queue_families(physical_device, surface);
  if (!queue_families.IsComplete()) {
    return 0;
  }

  // GPU must support rendering to a swapchain
  if (!DeviceSupportsAllRequiredExtensions(physical_device)) {
    return 0;
  }

  VkPhysicalDeviceProperties device_properties;
  VkPhysicalDeviceFeatures device_features;
  vkGetPhysicalDeviceProperties(physical_device, &device_properties);
  vkGetPhysicalDeviceFeatures(physical_device, &device_features);

  int score = 0;

  // Discrete GPUs have a significant performance advantage
  if (device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
    score += 20000;
  }

  // Maximum possible size of textures affects graphics quality
  score += device_properties.limits.maxImageDimension2D;

  return score;
}

VkPhysicalDevice ChoosePhysicalDevice(VulkanInstanceData& instance, VkSurfaceKHR surface) {
  VkPhysicalDevice physical_device = VK_NULL_HANDLE;
  uint32_t device_count = 0;

  vkEnumeratePhysicalDevices(instance.instance, &device_count, nullptr);
  KM_ASSERT(device_count, "Failed to find a Vulkan-capable GPU");
  std::vector<VkPhysicalDevice> devices(device_count);
  vkEnumeratePhysicalDevices(instance.instance, &device_count, devices.data());

  int highest_score = 0;
  for (const auto& device : devices) {
    int device_score = RateDeviceSuitability(device, surface);
    if (device_score > highest_score) {
      physical_device = device;
      highest_score = device_score;
    }
  }

  KM_ASSERT(physical_device, "Failed to find a suitable GPU");
  return physical_device;
}

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
  device_info.enabledExtensionCount = static_cast<uint32_t>(kDeviceExtensions.size());
  device_info.ppEnabledExtensionNames = kDeviceExtensions.data();

  VkDevice device;
  VK_CALL(vkCreateDevice(instance.physical_device, &device_info, instance.allocator, &device));
  volkLoadDevice(device);
  return device;
}

}
}
