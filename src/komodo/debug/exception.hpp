#pragma once

#include <stdexcept>

#include "komodo/utils/concat.hpp"

namespace Komodo {

struct Exception : public std::runtime_error {
  Exception(const char* what) : std::runtime_error(what) {
  }
};

}
