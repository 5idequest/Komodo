#pragma once

#include "komodo/backend/glfw/window/glfw_window.hpp"

namespace Komodo {

class VulkanWindow : public GlfwWindow {
public:
  VulkanWindow(const WindowCreateInfo& create_info = {});
};

}
