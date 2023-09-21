#include "file_reader.hpp"

#include <fstream>
#include <sstream>

#include "komodo/debug/assert.hpp"

namespace Komodo {

std::string ReadTextFile(const std::string& path) {
  std::ifstream t(path);
  KM_ASSERT(t.is_open(), "Failed to open file");
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

std::vector<uint32_t> ReadSpvBinaryFile(const std::string& path) {
  std::ifstream file(path, std::ios::ate | std::ios::binary);
  
  KM_ASSERT(file.is_open(), "Failed to open file");
  
  size_t file_size = (size_t)file.tellg();
  std::vector<uint32_t> buffer(file_size / sizeof(uint32_t));
  
  file.seekg(0);
  file.read((char*)buffer.data(), file_size);
  file.close();
  
  return buffer;
}

}
