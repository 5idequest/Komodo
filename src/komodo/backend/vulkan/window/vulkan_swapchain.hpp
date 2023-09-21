#pragma once

#include "komodo/backend/vulkan/instance/vulkan_instance_data.hpp"
#include "komodo/backend/vulkan/window/vulkan_window_data.hpp"

namespace Komodo {
namespace Vulkan {

void CreateWindowSwapchain(VulkanInstanceData* instance, VulkanWindowData* window);
void CreateWindowSwapchainImageViews(VulkanInstanceData* instance, VulkanWindowData* window);

}
}
