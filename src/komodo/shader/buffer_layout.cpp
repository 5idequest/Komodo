#include "buffer_layout.hpp"

namespace Komodo {

BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& buffer_elements) : buffer_elements(buffer_elements) {
  CalculateOffsetsAndSize();
}

BufferLayout::BufferLayout(const std::vector<BufferElement>& buffer_elements) : buffer_elements(buffer_elements) {
  CalculateOffsetsAndSize();
}

void BufferLayout::CalculateOffsetsAndSize() {
  int offset = 0;
  for (auto& element : buffer_elements) {
    element.offset = offset;
    offset += element.size;
    size += element.size;
  }
}

}