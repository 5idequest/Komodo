#include "file_reader.hpp"

#include <fstream>
#include <sstream>

#include "komodo/debug/assert.hpp"

namespace Komodo {

std::string ReadFile(const std::string& path) {
  std::ifstream t(path);
  KM_ASSERT(t.is_open(), "Failed to open file");
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

}
