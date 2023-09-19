#pragma once

#include <volk.h>

namespace Komodo {

struct VulkanWindowData {
  VkSurfaceKHR surface;
  VkSwapchainKHR swapchain;
};

}
