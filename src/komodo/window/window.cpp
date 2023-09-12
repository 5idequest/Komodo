#include "window.hpp"

#ifdef KOMODO_BACKEND_GLFW
  #include "komodo/backend/glfw/window/glfw_window.hpp"
#endif

namespace Komodo {

void PollWindowEvents() {
#ifdef KOMODO_BACKEND_GLFW
  Glfw::PollWindowEvents();
#endif
}

}
