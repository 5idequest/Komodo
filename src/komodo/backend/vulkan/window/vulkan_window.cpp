#include "vulkan_window.hpp"

#include <volk.h>
#include <GLFW/glfw3.h>

#include "komodo/backend/vulkan/instance/vulkan_instance_data.hpp"
#include "komodo/backend/vulkan/window/vulkan_swapchain.hpp"
#include "komodo/backend/vulkan/window/vulkan_window_data.hpp"
#include "komodo/backend/vulkan/window/vulkan_window_title.hpp"

namespace Komodo {

VulkanWindow::VulkanWindow(VulkanInstanceData* instance, const WindowCreateInfo& create_info) : instance(instance) {
  window = new VulkanWindowData();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  CreateGlfwWindow(create_info, Vulkan::GenerateWindowTitle(create_info.title));
  glfwCreateWindowSurface(instance->instance, glfw_window, instance->allocator, &window->surface);

  Vulkan::CreateWindowSwapchain(instance, window);
  Vulkan::CreateWindowSwapchainImageViews(instance, window);
}

VulkanWindow::~VulkanWindow() {
  for (auto image_view : window->swapchain_image_views) {
    vkDestroyImageView(instance->device, image_view, instance->allocator);
  }
  vkDestroySwapchainKHR(instance->device, window->swapchain, instance->allocator);
  vkDestroySurfaceKHR(instance->instance, window->surface, instance->allocator);

  delete window;
}

}
