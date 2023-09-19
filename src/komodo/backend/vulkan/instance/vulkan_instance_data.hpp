#pragma once

#include <volk.h>

#include "komodo/backend/vulkan/debug/vulkan_debug_messenger.hpp"

namespace Komodo {

struct VulkanInstanceData {
  VkInstance instance;
  VkAllocationCallbacks* allocator = nullptr;
  VkPhysicalDevice physical_device;
  VkDevice device;
  VkQueue graphics_queue;
  VkQueue present_queue;

#ifdef KOMODO_BUILD_DEBUG
  VkDebugUtilsMessengerEXT debug_messenger;
#endif
};

}
