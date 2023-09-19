#pragma once

#include <cstdint>
#include <optional>

#include <volk.h>

namespace Komodo {

struct VulkanQueueFamilyIndices {
  VulkanQueueFamilyIndices(VkPhysicalDevice device);

  bool IsComplete() const;

  std::optional<uint32_t> graphics_family;
};

}
