#include "opengl_window_title.hpp"

#include <GLFW/glfw3.h>

namespace Komodo {
namespace OpenGl {

std::string GenerateWindowTitle(const std::string& initial_title) {
  if (!initial_title.empty()) {
    return initial_title;
  }
  else {
#ifdef KOMODO_BUILD_DEBUG
    return "Komodo [OpenGl, Debug]";
#else
    return "Komodo [OpenGl]";
#endif
  }
}

}
}
