#include "vulkan_window_title.hpp"

#include <cstdint>
#include <string>

#include <volk.h>

namespace Komodo {
namespace Vulkan {

std::string GenerateDefaultWindowTitle() {
  uint32_t instance_version = VK_API_VERSION_1_0;
  vkEnumerateInstanceVersion(&instance_version);
  uint32_t major = VK_VERSION_MAJOR(instance_version);
  uint32_t minor = VK_VERSION_MINOR(instance_version);
  uint32_t patch = VK_VERSION_PATCH(instance_version);
  std::string version = std::to_string(major) + std::string(".") + std::to_string(minor) + std::string(".") + std::to_string(patch);

#ifdef KOMODO_BUILD_DEBUG
  return std::string("Komodo [Vulkan ") + version + std::string(", Debug]");
#else
  return std::string("Komodo [Vulkan ") + version + std::string("]");
#endif
}

}
}
