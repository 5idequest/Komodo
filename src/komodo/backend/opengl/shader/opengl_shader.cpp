#include "opengl_shader.hpp"

#include "komodo/shader/shader.hpp"

namespace Komodo {

OpenGlShader::OpenGlShader(const ShaderCreateInfo& shader_info) {
  auto spv = LoadShaderModules(shader_info);
}

}
