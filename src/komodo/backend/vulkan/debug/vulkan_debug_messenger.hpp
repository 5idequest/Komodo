#pragma once

#ifdef KOMODO_BUILD_DEBUG

#include <volk.h>

namespace Komodo {
namespace Vulkan {

VkDebugUtilsMessengerCreateInfoEXT CreateDebugMessengerCreateInfo();

}
}

#endif // KOMODO_BUILD_DEBUG
