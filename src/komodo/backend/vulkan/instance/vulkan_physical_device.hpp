#pragma once

#include "komodo/backend/vulkan/instance/vulkan_instance_data.hpp"

namespace Komodo {
namespace Vulkan {

VkPhysicalDevice ChoosePhysicalDevice(VulkanInstanceData& instance);

}
}
