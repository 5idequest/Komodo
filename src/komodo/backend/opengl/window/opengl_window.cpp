#include "opengl_window.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "komodo/backend/opengl/window/opengl_window_title.hpp"

namespace Komodo {
  
OpenGlWindow::OpenGlWindow(const WindowCreateInfo& create_info) {
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

#ifdef KOMODO_PLATFORM_MACOS
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  CreateGlfwWindow(create_info, create_info.title);

  glfwMakeContextCurrent(glfw_window);
  gladLoadGL(glfwGetProcAddress);
  
  if (create_info.title.empty()) {
    glfwSetWindowTitle(glfw_window, OpenGl::GenerateDefaultWindowTitle().c_str());
  }
}

}
