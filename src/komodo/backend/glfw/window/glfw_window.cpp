#include "glfw_window.hpp"

#include <GLFW/glfw3.h>

#include "komodo/backend/glfw/window/glfw_window_count.hpp"
#include "komodo/backend/glfw/window/glfw_window_position.hpp"

namespace Komodo {

GlfwWindow::GlfwWindow() : glfw_window(nullptr) {
  Glfw::IncrementWindowCount();
}

void GlfwWindow::CreateGlfwWindow(const WindowCreateInfo& create_info, const std::string& title) {
  glfw_window = glfwCreateWindow(create_info.width, create_info.height, title.c_str(), nullptr, nullptr);
  
  Glfw::PositionWindow(glfw_window, create_info.position);
}

GlfwWindow::~GlfwWindow() {
  glfwDestroyWindow(glfw_window);
  
  Glfw::DecrementWindowCount();
}

bool GlfwWindow::IsOpen() const {
  return !glfwWindowShouldClose(glfw_window);
}

namespace Glfw {

void PollWindowEvents() {
  glfwPollEvents();
}

}

}
