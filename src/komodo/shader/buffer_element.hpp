#pragma once

#include "komodo/shader/shader_data_type.hpp"

namespace Komodo {

struct BufferElement {
  BufferElement(ShaderDataType type);

  ShaderDataType type;
  int size;
  int offset;

  operator ShaderDataType() { return type; }
};

}
