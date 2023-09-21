#pragma once

#include <memory>

#include "komodo/backend/opengl/window/opengl_window.hpp"
#include "komodo/backend/opengl/shader/opengl_shader.hpp"

namespace Komodo {

class OpenGlInstance {
public:
  OpenGlInstance();
  ~OpenGlInstance();

private:
  bool is_opengl_loaded = false;

public:
  std::shared_ptr<OpenGlWindow> CreateWindow(const WindowCreateInfo& window_info = { });
  std::shared_ptr<OpenGlShader> CreateShader(const ShaderCreateInfo& shader_info = { });
};

}
