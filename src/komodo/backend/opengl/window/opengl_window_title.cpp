#include "opengl_window_title.hpp"

#include <string>

#include <glad/gl.h>

namespace Komodo {
namespace OpenGl {

std::string GenerateDefaultWindowTitle() {
  std::string version = (char*)glGetString(GL_VERSION);

#ifdef KOMODO_BUILD_DEBUG
  return std::string("Komodo [OpenGl ") + version + std::string(", Debug]");
#else
  return std::string("Komodo [OpenGl ") + version + std::string("]");
#endif
}

}
}
