#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace Komodo {

std::string ReadTextFile(const std::string& path);
std::vector<uint32_t> ReadSpvBinaryFile(const std::string& path);

}
