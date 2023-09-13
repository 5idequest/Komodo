#pragma once

#include "komodo/instance/instance.hpp"

#ifdef KOMODO_BACKEND_OPENGL

  #include "komodo/backend/opengl/window/opengl_window.hpp"

#endif // KOMODO_BACKEND_OPENGL

#ifdef KOMODO_BACKEND_VULKAN

  #include "komodo/backend/vulkan/window/vulkan_window.hpp"

#endif // KOMODO_BACKEND_VULKAN
