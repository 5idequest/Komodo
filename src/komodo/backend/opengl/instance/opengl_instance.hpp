#pragma once

#include <memory>

#include "komodo/backend/opengl/window/opengl_window.hpp"

namespace Komodo {

class OpenGlInstance {
public:
  OpenGlInstance();
  ~OpenGlInstance();

public:
  std::shared_ptr<OpenGlWindow> CreateWindow(const WindowCreateInfo& window_info = { });
};

}
