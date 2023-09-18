#include "vulkan_instance.hpp"

#include "komodo/debug/assert.hpp"
#include "komodo/backend/vulkan/debug/vulkan_call.hpp"
#include "komodo/backend/vulkan/debug/vulkan_validation_layers.hpp"
#include "komodo/backend/vulkan/instance/vulkan_instance_extensions.hpp"

namespace Komodo {

VulkanInstance::VulkanInstance() {
  VkApplicationInfo app_info { };
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.pEngineName = "Komodo";
  app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo instance_info { };
  instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instance_info.pApplicationInfo = &app_info;
  Vulkan::EnableInstanceExtensions(instance_info);

#ifdef KOMODO_BUILD_DEBUG
  Vulkan::CheckRequiredValidationLayersSupported();
  Vulkan::EnableValidationLayers(instance_info);
#endif

  VK_CALL(vkCreateInstance(&instance_info, allocator, &instance));
}

VulkanInstance::~VulkanInstance() {
  vkDestroyInstance(instance, allocator);
}

}

