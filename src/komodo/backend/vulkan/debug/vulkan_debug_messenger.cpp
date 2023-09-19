#include "vulkan_debug_messenger.hpp"

#ifdef KOMODO_BUILD_DEBUG

#include <cstdio>

#include "komodo/backend/vulkan/debug/vulkan_call.hpp"
#include "komodo/backend/vulkan/instance/vulkan_instance_data.hpp"

namespace Komodo {

static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

  fprintf(stderr, "%s\n", pCallbackData->pMessage);

  return VK_FALSE;
}

namespace Vulkan {

VkDebugUtilsMessengerCreateInfoEXT CreateDebugMessengerCreateInfo() {
  VkDebugUtilsMessengerCreateInfoEXT debug_messenger_info { };
  debug_messenger_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  debug_messenger_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
    | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
    | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  debug_messenger_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
    | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
    | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  debug_messenger_info.pfnUserCallback = DebugCallback;
  return debug_messenger_info;
}

}

VulkanDebugMessenger::VulkanDebugMessenger(VulkanInstanceData& instance) : instance(instance) {
  auto debug_messenger_info = Vulkan::CreateDebugMessengerCreateInfo();
  VK_CALL(vkCreateDebugUtilsMessengerEXT(instance.instance, &debug_messenger_info, instance.allocator, &debug_messenger));
}

VulkanDebugMessenger::~VulkanDebugMessenger() {
  vkDestroyDebugUtilsMessengerEXT(instance.instance, debug_messenger, instance.allocator);
}

}

#endif // KOMODO_BUILD_DEBUG
