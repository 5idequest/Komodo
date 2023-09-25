#pragma once

#include <memory>

#include "komodo/shader/buffer_layout.hpp"
#include "komodo/shader/spv_modules.hpp"

namespace Komodo {

struct ShaderReflectionDetails {
  ShaderReflectionDetails(std::shared_ptr<SpvModules> spv);

  BufferLayout vertex_input_layout;
};

}
