#pragma once

#include <memory>

#include "komodo/backend/opengl/window/opengl_window.hpp"
#include "komodo/instance/instance.hpp"

namespace Komodo {

class OpenGlInstance : public Instance {
public:
  OpenGlInstance();
  ~OpenGlInstance();

public:
  std::shared_ptr<OpenGlWindow> CreateWindow(const WindowCreateInfo& window_info = { });
};

}
