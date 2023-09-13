#pragma once

#include "komodo/window/window_create_info.hpp"

struct GLFWwindow;

namespace Komodo {
namespace Glfw {

void PositionWindow(GLFWwindow* glfw_window, const WindowPositionInfo& position);

}
}
