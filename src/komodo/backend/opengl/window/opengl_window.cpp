#include "opengl_window.hpp"

#include <GLFW/glfw3.h>

#include "komodo/backend/opengl/window/opengl_window_title.hpp"

namespace Komodo {
  
OpenGlWindow::OpenGlWindow(const WindowCreateInfo& create_info) {
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

#ifdef KOMODO_PLATFORM_MACOS
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  CreateGlfwWindow(create_info, OpenGl::GenerateWindowTitle(create_info.title));

  glfwMakeContextCurrent(glfw_window);
}

}
