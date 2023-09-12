#include "glfw_window.hpp"

#include <GLFW/glfw3.h>

#include "komodo/backend/glfw/instance/glfw_instance.hpp"

namespace Komodo {

GlfwWindow::GlfwWindow() {
  Glfw::IncrementContextCount();
  
  glfw_window = glfwCreateWindow(1280, 720, "GLfw Window", nullptr, nullptr);
}

GlfwWindow::~GlfwWindow() {
  glfwDestroyWindow(glfw_window);
  
  Glfw::DecrementContextCount();
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
