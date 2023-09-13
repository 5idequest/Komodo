#include "vulkan_window.hpp"

#include <GLFW/glfw3.h>

#include "vulkan_window_title.hpp"

namespace Komodo {

VulkanWindow::VulkanWindow(const WindowCreateInfo& create_info) {
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  CreateGlfwWindow(create_info, Vulkan::GenerateWindowTitle(create_info.title));
}

}
