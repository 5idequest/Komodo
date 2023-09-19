#include "opengl_instance.hpp"

#include "komodo/backend/glfw/instance/glfw_instance_count.hpp"

namespace Komodo {

OpenGlInstance::OpenGlInstance() {
  Glfw::IncrementInstanceCount();
}

OpenGlInstance::~OpenGlInstance() {
  Glfw::DecrementInstanceCount();
}

std::shared_ptr<OpenGlWindow> OpenGlInstance::CreateWindow(const WindowCreateInfo& window_info) {
  return std::make_shared<OpenGlWindow>(window_info);
}

}
