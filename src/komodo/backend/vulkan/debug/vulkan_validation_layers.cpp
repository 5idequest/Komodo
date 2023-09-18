#include "vulkan_validation_layers.hpp"

#include <cstdint>
#include <vector>

#include <vulkan/vulkan.h>

namespace Komodo {
namespace Vulkan {

const static std::vector<const char*> kValidationLayers = {
  "VK_LAYER_KHRONOS_validation"
};

bool AreAllRequiredValidationLayersSupported() {
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
      return false;
    }
}

return true;
}

}
}
