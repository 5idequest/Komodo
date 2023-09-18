#pragma once

#include <stdexcept>

namespace Komodo {

struct Exception : public std::runtime_error {
  Exception(const char* what) : std::runtime_error(what) {
  }
};

}
