#include "vulkan_validation_layers.hpp"

#ifdef KOMODO_BUILD_DEBUG

#include <cstdint>
#include <vector>

#include <volk.h>

#include "komodo/debug/assert.hpp"

namespace Komodo {
namespace Vulkan {

const static std::vector<const char*> kValidationLayers = {
  "VK_LAYER_KHRONOS_validation"
};

bool CheckRequiredValidationLayersSupported() {
  uint32_t layer_count;
  vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

  std::vector<VkLayerProperties> available_layers(layer_count);
  vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());
  for (const char* layerName : kValidationLayers) {
    bool layer_found = false;

    for (const VkLayerProperties& layer_props : available_layers) {
      if (strcmp(layerName, layer_props.layerName) == 0) {
        layer_found = true;
        break;
      }
    }

    if (!layer_found) {
      KM_ASSERT(false, "One or more validation layers requested, but not present");
    }
  }

  return true;
}

void EnableValidationLayers(VkInstanceCreateInfo& instance_info) {
  instance_info.enabledLayerCount = kValidationLayers.size();
  instance_info.ppEnabledLayerNames = kValidationLayers.data();
}

}
}

#endif // KOMODO_BUILD_DEBUG
