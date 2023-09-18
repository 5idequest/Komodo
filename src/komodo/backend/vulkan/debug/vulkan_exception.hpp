#pragma once

#include "komodo/debug/exception.hpp"

namespace Komodo {

struct VulkanException : public Exception {
  VulkanException(const char* what) : Exception(what) {
  }
};

}
