#include "vulkan_window_title.hpp"

namespace Komodo {
namespace Vulkan {

std::string GenerateWindowTitle(const std::string& initial_title) {
  if (!initial_title.empty()) {
    return initial_title;
  }
  else {
#ifdef KOMODO_BUILD_DEBUG
    return "Komodo [Vulkan, Debug]";
#else
    return "Komodo [Vulkan]";
#endif
  }
}

}
}
