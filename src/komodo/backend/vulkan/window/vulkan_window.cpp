#include "vulkan_window.hpp"

#include <GLFW/glfw3.h>

#include "vulkan_window_title.hpp"

namespace Komodo {

VulkanWindow::VulkanWindow(VulkanInstanceData& instance, const WindowCreateInfo& create_info) : instance(instance) {
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  CreateGlfwWindow(create_info, Vulkan::GenerateWindowTitle(create_info.title));

  glfwCreateWindowSurface(instance.instance, glfw_window, instance.allocator, &window.surface);
}

VulkanWindow::~VulkanWindow() {
  vkDestroySurfaceKHR(instance.instance, window.surface, instance.allocator);
}

}
