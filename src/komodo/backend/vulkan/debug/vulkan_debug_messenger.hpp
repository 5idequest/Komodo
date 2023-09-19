#pragma once

#ifdef KOMODO_BUILD_DEBUG

#include <volk.h>

namespace Komodo {
namespace Vulkan {

VkDebugUtilsMessengerCreateInfoEXT CreateDebugMessengerCreateInfo();

}

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
