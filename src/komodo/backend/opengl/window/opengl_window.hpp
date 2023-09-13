#pragma once

#include "komodo/backend/glfw/window/glfw_window.hpp"
#include "komodo/window/window_create_info.hpp"

namespace Komodo {

class OpenGlWindow : public GlfwWindow {
public:
  OpenGlWindow(const WindowCreateInfo& create_info = {});
};

}
