#pragma once

#include <cstdint>
#include <optional>

#include <volk.h>

namespace Komodo {

struct VulkanQueueFamilyIndices {
  VulkanQueueFamilyIndices(VkPhysicalDevice physical_device, VkSurfaceKHR surface);

  bool IsComplete() const;

  std::optional<uint32_t> graphics_family;
  std::optional<uint32_t> present_family;
};

}
