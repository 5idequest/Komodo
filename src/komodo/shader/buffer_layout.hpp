#pragma once

#include <vector>

#include "komodo/shader/buffer_element.hpp"

namespace Komodo {

class BufferLayout {
public:
  BufferLayout() = default;
  BufferLayout(const std::vector<BufferElement>& buffer_elements);
  BufferLayout(const std::initializer_list<BufferElement>& buffer_elements);

  inline size_t GetSize() const                                   { return size;                    }
  inline size_t GetNumElements() const                            { return buffer_elements.size();  }
  inline const std::vector<BufferElement>& GetElements() const    { return buffer_elements;         }

  inline std::vector<BufferElement>::iterator begin()             { return buffer_elements.begin(); }
  inline std::vector<BufferElement>::iterator end()               { return buffer_elements.end();   }
  inline std::vector<BufferElement>::const_iterator begin() const { return buffer_elements.begin(); }
  inline std::vector<BufferElement>::const_iterator end() const   { return buffer_elements.end();   }
  inline BufferElement operator [](int i) const                   { return buffer_elements[i];      }

private:
  void CalculateOffsetsAndSize();

private:
  std::vector<BufferElement> buffer_elements;
  size_t size = 0;
};

}
