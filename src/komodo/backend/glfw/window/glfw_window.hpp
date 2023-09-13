#pragma once

#include "komodo/window/window.hpp"
#include "komodo/window/window_create_info.hpp"

struct GLFWwindow;

namespace Komodo {

class GlfwWindow : public Window {
public:
  GlfwWindow(const WindowCreateInfo& create_info);
  ~GlfwWindow();
  
public:
  virtual bool IsOpen() const override;
  
private:
  GLFWwindow* glfw_window;
};

namespace Glfw {

void PollWindowEvents();

}

}
