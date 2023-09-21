#include "vulkan_temp_surface.hpp"

#include "komodo/backend/vulkan/debug/vulkan_call.hpp"

namespace Komodo {

VulkanTempSurface::VulkanTempSurface(VulkanInstanceData* instance) : instance(instance) {
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  window = glfwCreateWindow(1, 1, "", nullptr, nullptr);
  glfwCreateWindowSurface(instance->instance, window, instance->allocator, &surface);
}

VulkanTempSurface::~VulkanTempSurface() {
  vkDestroySurfaceKHR(instance->instance, surface, instance->allocator);
  glfwDestroyWindow(window);
}

VulkanTempSurface::operator VkSurfaceKHR() const {
  return surface;
}

}