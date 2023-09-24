#pragma once

#include "komodo/shader/buffer_layout.hpp"
#include "komodo/shader/spv_modules.hpp"

namespace Komodo {

struct ShaderReflectionDetails {
  ShaderReflectionDetails(const SpvModules& spv);

  BufferLayout vertex_input_layout;
};

}
