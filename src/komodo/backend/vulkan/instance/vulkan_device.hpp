#pragma once

#include <volk.h>

#include "komodo/backend/vulkan/instance/vulkan_instance_data.hpp"
#include "komodo/backend/vulkan/instance/vulkan_queue_family_indices.hpp"

namespace Komodo {
namespace Vulkan {

VkPhysicalDevice ChoosePhysicalDevice(VulkanInstanceData& instance, VkSurfaceKHR surface);
VkDevice CreateDevice(VulkanInstanceData& instance, const VulkanQueueFamilyIndices& queue_families);

}
}
