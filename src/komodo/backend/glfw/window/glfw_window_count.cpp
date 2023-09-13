#include "glfw_window_count.hpp"

#include <GLFW/glfw3.h>

namespace Komodo {
namespace Glfw {

static int num_glfw_windows = 0;

void IncrementWindowCount() {
  if (++num_glfw_windows == 1) {
    glfwInit();
  }
}

void DecrementWindowCount() {
  if (--num_glfw_windows == 0) {
    glfwTerminate();
  }
}

}
}

