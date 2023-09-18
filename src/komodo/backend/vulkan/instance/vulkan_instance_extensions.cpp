#include "vulkan_instance_extensions.hpp"

#include <cstdint>

#include <GLFW/glfw3.h>

namespace Komodo {
namespace Vulkan {

void EnableInstanceExtensions(VkInstanceCreateInfo& instance_info) {    
  uint32_t glfw_extension_count = 0;
  const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
  instance_info.enabledExtensionCount = glfw_extension_count;
  instance_info.ppEnabledExtensionNames = glfw_extensions;
  instance_info.enabledLayerCount = 0;
}

}
}
