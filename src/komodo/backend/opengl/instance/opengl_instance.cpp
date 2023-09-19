#include "opengl_instance.hpp"

#include "komodo/backend/glfw/instance/glfw_instance_count.hpp"

namespace Komodo {

OpenGlInstance::OpenGlInstance() {
  Glfw::IncrementInstanceCount();
}

OpenGlInstance::~OpenGlInstance() {
  Glfw::DecrementInstanceCount();
}

}
