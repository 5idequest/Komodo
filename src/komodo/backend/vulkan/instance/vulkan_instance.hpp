#pragma once

#include <vulkan/vulkan.h>

namespace Komodo {

class VulkanInstance {
public:
  VulkanInstance();
  ~VulkanInstance();

private:
  VkInstance instance;
  VkAllocationCallbacks* allocator = nullptr;
};

}
