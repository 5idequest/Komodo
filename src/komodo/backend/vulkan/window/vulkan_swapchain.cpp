#include "vulkan_swapchain.hpp"

#include "komodo/backend/vulkan/debug/vulkan_call.hpp"
#include "komodo/backend/vulkan/instance/vulkan_queue_family_indices.hpp"
#include "komodo/backend/vulkan/window/vulkan_swapchain_support.hpp"

namespace Komodo {
namespace Vulkan {

void CreateWindowSwapchain(VulkanInstanceData& instance, VulkanWindowData& window) {
  VulkanSwapchainSupportDetails swapchain_support(instance.physical_device, window.surface);

  VkSurfaceFormatKHR surface_format = swapchain_support.ChooseSurfaceFormat();
  VkPresentModeKHR present_mode = swapchain_support.ChooseSwapPresentMode();
  VkExtent2D extent = swapchain_support.ChooseSwapExtent(window.glfw_window);

  uint32_t image_count = swapchain_support.capabilities.minImageCount + 1;
  if (swapchain_support.capabilities.maxImageCount > 0 && image_count > swapchain_support.capabilities.maxImageCount) {
    image_count = swapchain_support.capabilities.maxImageCount;
  }

  VkSwapchainCreateInfoKHR swapchain_info { };
  swapchain_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  swapchain_info.surface = window.surface;
  swapchain_info.minImageCount = image_count;
  swapchain_info.imageFormat = surface_format.format;
  swapchain_info.imageColorSpace = surface_format.colorSpace;
  swapchain_info.imageExtent = extent;
  swapchain_info.imageArrayLayers = 1;
  swapchain_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

  VulkanQueueFamilyIndices indices(instance.physical_device, window.surface);
  uint32_t queue_family_indices[] = { indices.graphics_family.value(), indices.present_family.value() };

  if (indices.graphics_family != indices.present_family) {
    swapchain_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    swapchain_info.queueFamilyIndexCount = 2;
    swapchain_info.pQueueFamilyIndices = queue_family_indices;
  } else {
    swapchain_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
  }

  swapchain_info.preTransform = swapchain_support.capabilities.currentTransform;
  swapchain_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  swapchain_info.presentMode = present_mode;
  swapchain_info.clipped = VK_TRUE;
  swapchain_info.oldSwapchain = VK_NULL_HANDLE;

  VK_CALL(vkCreateSwapchainKHR(instance.device, &swapchain_info, instance.allocator, &window.swapchain));

  vkGetSwapchainImagesKHR(instance.device, window.swapchain, &image_count, nullptr);
  window.swapchain_images.resize(image_count);
  vkGetSwapchainImagesKHR(instance.device, window.swapchain, &image_count, window.swapchain_images.data());
}

}
}
