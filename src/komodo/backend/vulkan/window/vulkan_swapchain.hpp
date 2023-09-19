#pragma once

#include <volk.h>

#include "komodo/backend/vulkan/window/vulkan_window_data.hpp"

namespace Komodo {
namespace Vulkan {

VkSwapchainKHR CreateSwapchain(VulkanInstanceData& instance, VulkanWindowData& window);

}
}
