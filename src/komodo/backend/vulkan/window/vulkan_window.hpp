#pragma once

#include "komodo/backend/glfw/window/glfw_window.hpp"

namespace Komodo {

struct VulkanInstanceData;
struct VulkanWindowData;

class VulkanWindow : public GlfwWindow {
public:
  VulkanWindow(VulkanInstanceData* instance, const WindowCreateInfo& create_info);
  ~VulkanWindow();

private:
  VulkanWindowData* window;
  VulkanInstanceData* instance;
};

}
