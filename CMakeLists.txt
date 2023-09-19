cmake_minimum_required(VERSION 3.27)
project(Komodo)

# Find platform - macOS, Windows or Linux
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  set(KOMODO_PLATFORM_WINDOWS TRUE)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
  set(KOMODO_PLATFORM_MACOS TRUE)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  set(KOMODO_PLATFORM_LINUX TRUE)
endif()

# Find all supported backends for the current platform
if(KOMODO_PLATFORM_WINDOWS OR KOMODO_PLATFORM_MACOS OR KOMODO_PLATFORM_LINUX)
  set(KOMODO_BACKEND_OPENGL TRUE)
endif()

find_package(Vulkan)
if(Vulkan_FOUND)
  set(KOMODO_BACKEND_VULKAN TRUE)
endif()

if(KOMODO_BACKEND_OPENGL OR KOMODO_BACKEND_VULKAN)
  set(KOMODO_BACKEND_GLFW TRUE)
endif()

# List source files
set(KOMODO_SRC_FILES
  src/komodo/komodo.hpp
)
source_group("src" FILES ${KOMODO_SRC_FILES})

set(KOMODO_SRC_DEBUG_FILES
  src/komodo/debug/assert.hpp
  src/komodo/debug/exception.hpp
)
source_group("src/komodo/debug" FILES ${KOMODO_SRC_DEBUG_FILES})

set(KOMODO_SRC_INSTANCE_FILES
  src/komodo/instance/instance.hpp src/komodo/instance/instance.cpp
)
source_group("src/komodo/instance" FILES ${KOMODO_SRC_INSTANCE_FILES})

set(KOMODO_SRC_WINDOW_FILES
  src/komodo/window/window.hpp src/komodo/window/window.cpp
  src/komodo/window/window_create_info.hpp
)
source_group("src/komodo/window" FILES ${KOMODO_SRC_WINDOW_FILES})

set(KOMODO_SRC_UTILS_FILES
  src/komodo/utils/concat.hpp
)
source_group("src/komodo/utils" FILES ${KOMODO_SRC_UTILS_FILES})

if(KOMODO_BACKEND_GLFW)
  set(KOMODO_SRC_GLFW_INSTANCE_FILES
    src/komodo/backend/glfw/instance/glfw_instance_count.hpp src/komodo/backend/glfw/instance/glfw_instance_count.cpp
  )
  source_group("src/backend/glfw/instance" FILES ${KOMODO_SRC_GLFW_INSTANCE_FILES})

  set(KOMODO_SRC_GLFW_WINDOW_FILES
    src/komodo/backend/glfw/window/glfw_window.hpp src/komodo/backend/glfw/window/glfw_window.cpp
    src/komodo/backend/glfw/window/glfw_window_position.hpp src/komodo/backend/glfw/window/glfw_window_position.cpp
  )
  source_group("src/backend/glfw/window" FILES ${KOMODO_SRC_GLFW_WINDOW_FILES})
endif()

if(KOMODO_BACKEND_OPENGL)
  set(KOMODO_SRC_OPENGL_INSTANCE_FILES
    src/komodo/backend/opengl/instance/opengl_instance.hpp src/komodo/backend/opengl/instance/opengl_instance.cpp
  )
  source_group("src/backend/opengl/instance" FILES ${KOMODO_SRC_OPENGL_INSTANCE_FILES})

  set(KOMODO_SRC_OPENGL_WINDOW_FILES
    src/komodo/backend/opengl/window/opengl_window.hpp src/komodo/backend/opengl/window/opengl_window.cpp
    src/komodo/backend/opengl/window/opengl_window_title.hpp src/komodo/backend/opengl/window/opengl_window_title.cpp
  )
  source_group("src/backend/opengl/window" FILES ${KOMODO_SRC_OPENGL_WINDOW_FILES})
endif()

if(KOMODO_BACKEND_VULKAN)
  set(KOMODO_SRC_VULKAN_DEBUG_FILES
    src/komodo/backend/vulkan/debug/vulkan_call.hpp
    src/komodo/backend/vulkan/debug/vulkan_exception.hpp
    src/komodo/backend/vulkan/debug/vulkan_debug_messenger.hpp src/komodo/backend/vulkan/debug/vulkan_debug_messenger.cpp
    src/komodo/backend/vulkan/debug/vulkan_validation_layers.hpp src/komodo/backend/vulkan/debug/vulkan_validation_layers.cpp
  )
  source_group("src/backend/vulkan/debug" FILES ${KOMODO_SRC_VULKAN_DEBUG_FILES})

  set(KOMODO_SRC_VULKAN_INSTANCE_FILES
    src/komodo/backend/vulkan/instance/vulkan_instance.hpp src/komodo/backend/vulkan/instance/vulkan_instance.cpp
    src/komodo/backend/vulkan/instance/vulkan_instance_data.hpp
    src/komodo/backend/vulkan/instance/vulkan_instance_extensions.hpp src/komodo/backend/vulkan/instance/vulkan_instance_extensions.cpp
  )
  source_group("src/backend/vulkan/instance" FILES ${KOMODO_SRC_VULKAN_INSTANCE_FILES})

  set(KOMODO_SRC_VULKAN_WINDOW_FILES
    src/komodo/backend/vulkan/window/vulkan_window.hpp src/komodo/backend/vulkan/window/vulkan_window.cpp
    src/komodo/backend/vulkan/window/vulkan_window_title.hpp src/komodo/backend/vulkan/window/vulkan_window_title.cpp
  )
  source_group("src/backend/vulkan/window" FILES ${KOMODO_SRC_VULKAN_WINDOW_FILES})
endif()

add_library(${PROJECT_NAME}
  ${KOMODO_SRC_FILES}

  ${KOMODO_SRC_DEBUG_FILES}
  ${KOMODO_SRC_INSTANCE_FILES}
  ${KOMODO_SRC_WINDOW_FILES}
  ${KOMODO_SRC_UTILS_FILES}
  
  ${KOMODO_SRC_GLFW_INSTANCE_FILES}
  ${KOMODO_SRC_GLFW_WINDOW_FILES}
  
  ${KOMODO_SRC_OPENGL_INSTANCE_FILES}
  ${KOMODO_SRC_OPENGL_WINDOW_FILES}
  
  ${KOMODO_SRC_VULKAN_DEBUG_FILES}
  ${KOMODO_SRC_VULKAN_INSTANCE_FILES}
  ${KOMODO_SRC_VULKAN_WINDOW_FILES}
)

# Target C++17
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Set public include directories
target_include_directories(${PROJECT_NAME} PUBLIC src)

# Link libraries
if(KOMODO_BACKEND_GLFW)
  add_subdirectory(src/lib/glfw)
  target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
endif()

if(KOMODO_BACKEND_OPENGL)
  add_subdirectory(src/lib/glad)
  target_link_libraries(${PROJECT_NAME} PRIVATE glad)
endif()

if(KOMODO_BACKEND_VULKAN)
  add_subdirectory(src/lib/volk)
  target_link_libraries(${PROJECT_NAME} PRIVATE volk)
endif()

# Compile defines
if(KOMODO_PLATFORM_WINDOWS)
  target_compile_definitions(${PROJECT_NAME} PUBLIC KOMODO_PLATFORM_WINDOWS)
elseif(KOMODO_PLATFORM_MACOS)
  target_compile_definitions(${PROJECT_NAME} PUBLIC KOMODO_PLATFORM_MACOS)
elseif(KOMODO_PLATFORM_LINUX)
  target_compile_definitions(${PROJECT_NAME} PUBLIC KOMODO_PLATFORM_LINUX)
endif()

if(KOMODO_BACKEND_GLFW)
  target_compile_definitions(${PROJECT_NAME} PUBLIC KOMODO_BACKEND_GLFW)
endif()
if(KOMODO_BACKEND_OPENGL)
  target_compile_definitions(${PROJECT_NAME} PUBLIC KOMODO_BACKEND_OPENGL)
endif()
if(KOMODO_BACKEND_VULKAN)
  target_compile_definitions(${PROJECT_NAME} PUBLIC KOMODO_BACKEND_VULKAN)
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:KOMODO_BUILD_DEBUG>)
target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<CONFIG:Release>:KOMODO_BUILD_RELEASE>)

# Add example project
add_subdirectory(example)
