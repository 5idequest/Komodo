#include "vulkan_instance.hpp"

#include "komodo/debug/assert.hpp"
#include "komodo/backend/glfw/instance/glfw_instance_count.hpp"
#include "komodo/backend/vulkan/debug/vulkan_call.hpp"
#include "komodo/backend/vulkan/debug/vulkan_debug_messenger.hpp"
#include "komodo/backend/vulkan/debug/vulkan_validation_layers.hpp"
#include "komodo/backend/vulkan/instance/vulkan_device.hpp"
#include "komodo/backend/vulkan/instance/vulkan_instance_extensions.hpp"
#include "komodo/backend/vulkan/instance/vulkan_queue_family_indices.hpp"
#include "komodo/backend/vulkan/instance/vulkan_temp_surface.hpp"

namespace Komodo {

VulkanInstance::VulkanInstance() {
  Glfw::IncrementInstanceCount();

  volkInitialize();

  instance = new VulkanInstanceData();

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
#ifdef KOMODO_PLATFORM_MACOS
  instance_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif

#ifdef KOMODO_BUILD_DEBUG
  Vulkan::CheckRequiredValidationLayersSupported();
  Vulkan::EnableValidationLayers(instance_info);

  auto debug_messenger_info = Vulkan::CreateDebugMessengerCreateInfo();
  instance_info.pNext = &debug_messenger_info;
#endif

  VK_CALL(vkCreateInstance(&instance_info, instance->allocator, &instance->instance));
  volkLoadInstance(instance->instance);

#ifdef KOMODO_BUILD_DEBUG
  VK_CALL(vkCreateDebugUtilsMessengerEXT(instance->instance, &debug_messenger_info, instance->allocator, &instance->debug_messenger));
#endif // KOMODO_BUILD_DEBUG

  VulkanTempSurface temp_surface(instance);
  Vulkan::ChoosePhysicalDevice(instance, temp_surface);
  VulkanQueueFamilyIndices queue_families(instance->physical_device, temp_surface);
  Vulkan::CreateDevice(instance, queue_families);
  vkGetDeviceQueue(instance->device, queue_families.graphics_family.value(), 0, &instance->graphics_queue);
  vkGetDeviceQueue(instance->device, queue_families.present_family.value(), 0, &instance->present_queue);
}

VulkanInstance::~VulkanInstance() {
  vkDestroyDevice(instance->device, instance->allocator);
#ifdef KOMODO_BUILD_DEBUG
  vkDestroyDebugUtilsMessengerEXT(instance->instance, instance->debug_messenger, instance->allocator);
#endif // KOMODO_BUILD_DEBUG
  vkDestroyInstance(instance->instance, instance->allocator);

  delete instance;

  Glfw::DecrementInstanceCount();
}

void VulkanInstance::BeginFrame() {

}

void VulkanInstance::EndFrame() {

}

std::shared_ptr<VulkanWindow> VulkanInstance::CreateWindow(const WindowCreateInfo& window_info) {
  return std::make_shared<VulkanWindow>(instance, window_info);
}

std::shared_ptr<VulkanShader> VulkanInstance::CreateShader(const ShaderCreateInfo& shader_info) {
  return std::make_shared<VulkanShader>(shader_info);
}

}

