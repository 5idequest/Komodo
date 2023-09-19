#pragma once

#include "komodo/backend/vulkan/instance/vulkan_instance_data.hpp"

namespace Komodo {

class VulkanInstance {
public:
  VulkanInstance();
  ~VulkanInstance();

private:
  VulkanInstanceData instance;
};

}
