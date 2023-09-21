#pragma once

#include <volk.h>
#include <GLFW/glfw3.h>

#include "komodo/backend/vulkan/instance/vulkan_instance_data.hpp"

namespace Komodo {

class VulkanTempSurface {
public:
  VulkanTempSurface(VulkanInstanceData* instance);
  ~VulkanTempSurface();

private:
  VkSurfaceKHR surface;
  GLFWwindow* window;
  VulkanInstanceData* instance;

public:
  operator VkSurfaceKHR() const;
};

}
