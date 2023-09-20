#include "vulkan_window.hpp"

#include <GLFW/glfw3.h>

#include "komodo/backend/vulkan/window/vulkan_swapchain.hpp"
#include "komodo/backend/vulkan/window/vulkan_window_title.hpp"

namespace Komodo {

VulkanWindow::VulkanWindow(VulkanInstanceData& instance, const WindowCreateInfo& create_info) : instance(instance) {
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  CreateGlfwWindow(create_info, Vulkan::GenerateWindowTitle(create_info.title));
  glfwCreateWindowSurface(instance.instance, glfw_window, instance.allocator, &window.surface);

  Vulkan::CreateWindowSwapchain(instance, window);
}

VulkanWindow::~VulkanWindow() {
  vkDestroySwapchainKHR(instance.device, window.swapchain, instance.allocator);
  vkDestroySurfaceKHR(instance.instance, window.surface, instance.allocator);
}

}
