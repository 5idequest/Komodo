#pragma once

#ifdef KOMODO_BUILD_DEBUG

#include <vulkan/vulkan.h>

namespace Komodo {

struct VulkanInstanceData;

class VulkanDebugMessenger {
public:
  VulkanDebugMessenger(VulkanInstanceData& instance);
  ~VulkanDebugMessenger();

private:
  VkDebugUtilsMessengerEXT debug_messenger;
  VulkanInstanceData& instance;
};

}

#endif // KOMODO_BUILD_DEBUG
