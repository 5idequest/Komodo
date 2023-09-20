#pragma once

#ifdef KOMODO_BACKEND_OPENGL

  #include "komodo/backend/opengl/instance/opengl_instance.hpp"
  #include "komodo/backend/opengl/window/opengl_window.hpp"

#endif // KOMODO_BACKEND_OPENGL

#ifdef KOMODO_BACKEND_VULKAN

  #include "komodo/backend/vulkan/instance/vulkan_instance.hpp"
  #include "komodo/backend/vulkan/window/vulkan_window.hpp"

#endif // KOMODO_BACKEND_VULKAN
