#include "glfw_instance.hpp"

#include <GLFW/glfw3.h>

namespace Komodo {
namespace Glfw {

static int num_glfw_windows = 0;

void IncrementContextCount() {
  if (++num_glfw_windows == 1) {
    glfwInit();
  }
}

void DecrementContextCount() {
  if (--num_glfw_windows == 0) {
    glfwTerminate();
  }
}

}
}

