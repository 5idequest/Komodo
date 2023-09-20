#pragma once

#include "komodo/window/window.hpp"
#include "komodo/window/window_create_info.hpp"

struct GLFWwindow;

namespace Komodo {

class GlfwWindow {
public:
  GlfwWindow();
  ~GlfwWindow();

protected:
  void CreateGlfwWindow(const WindowCreateInfo& create_info, const std::string& title);
  
public:
  bool IsOpen() const;
  
protected:
  GLFWwindow* glfw_window;
};

namespace Glfw {

void PollWindowEvents();

}

}
