#pragma once

#include "komodo/window/window.hpp"
#include "komodo/window/window_create_info.hpp"

struct GLFWwindow;

namespace Komodo {

class GlfwWindow : public Window {
public:
  GlfwWindow();
  ~GlfwWindow();

protected:
  void CreateGlfwWindow(const WindowCreateInfo& create_info, const std::string& title);
  
public:
  virtual bool IsOpen() const override;
  
protected:
  GLFWwindow* glfw_window;
};

namespace Glfw {

void PollWindowEvents();

}

}
