#pragma once

#include <volk.h>

#include "komodo/backend/vulkan/debug/vulkan_debug_messenger.hpp"

namespace Komodo {

struct VulkanInstanceData {
  VkInstance instance;
  VkAllocationCallbacks* allocator = nullptr;

#ifdef KOMODO_BUILD_DEBUG
  VulkanDebugMessenger* debug_messenger;
#endif
};

}
