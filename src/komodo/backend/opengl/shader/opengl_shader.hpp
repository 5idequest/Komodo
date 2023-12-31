#pragma once

#include "komodo/shader/shader_create_info.hpp"

namespace Komodo {

class OpenGlShader {
public:
  OpenGlShader(const ShaderCreateInfo& shader_info);

private:
  unsigned int shader_program;

public:
  void Bind();
};

}
