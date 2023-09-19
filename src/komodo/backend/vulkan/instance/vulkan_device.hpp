#pragma once

#include <volk.h>

#include "komodo/backend/vulkan/instance/vulkan_instance_data.hpp"

namespace Komodo {
namespace Vulkan {

VkDevice CreateDevice(VulkanInstanceData& instance);

}
}
