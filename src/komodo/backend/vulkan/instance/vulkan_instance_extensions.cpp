#include "vulkan_instance_extensions.hpp"

#include <cstdint>
#include <vector>

#include <GLFW/glfw3.h>

namespace Komodo {
namespace Vulkan {

static std::vector<const char*> extensions;

void EnableInstanceExtensions(VkInstanceCreateInfo& instance_info) {
  if (extensions.empty()) {
    uint32_t glfw_extension_count = 0;
    const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
    for (int i = 0; i < glfw_extension_count; ++i) {
      extensions.push_back(glfw_extensions[i]);
    }

#ifdef KOMODO_BUILD_DEBUG
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif
    
#ifdef KOMODO_PLATFORM_MACOS
    extensions.push_back("VK_KHR_portability_enumeration");
    extensions.push_back("VK_KHR_get_physical_device_properties2");
#endif
  }

  instance_info.enabledExtensionCount = extensions.size();
  instance_info.ppEnabledExtensionNames = extensions.data();
}

}
}
