#include "glfw_instance_count.hpp"

#include <GLFW/glfw3.h>

namespace Komodo {
namespace Glfw {

static int num_glfw_instances = 0;

void IncrementInstanceCount() {
  if (++num_glfw_instances == 1) {
    glfwInit();
  }
}

void DecrementInstanceCount() {
  if (--num_glfw_instances == 0) {
    glfwTerminate();
  }
}

}
}

