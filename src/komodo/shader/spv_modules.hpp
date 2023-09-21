#pragma once

#include <cstdint>
#include <memory>
#include <vector>

namespace Komodo {

struct SpvModules {
  std::shared_ptr<std::vector<uint32_t>> vert;
  std::shared_ptr<std::vector<uint32_t>> frag;
};

}
