#include "buffer_element.hpp"

namespace Komodo {

BufferElement::BufferElement(ShaderDataType type) : type(type), size(ShaderDataTypeSize(type)), offset(0) {
}

}
