#pragma once

#include "komodo/window/window.hpp"

struct GLFWwindow;

namespace Komodo {

class GlfwWindow : public Window {
public:
  GlfwWindow();
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
