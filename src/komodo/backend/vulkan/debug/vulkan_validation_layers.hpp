#pragma once

#ifdef KOMODO_BUILD_DEBUG

#include <volk.h>

namespace Komodo {
namespace Vulkan {

bool CheckRequiredValidationLayersSupported();

void EnableValidationLayers(VkInstanceCreateInfo& instance_info);

}
}

#endif
