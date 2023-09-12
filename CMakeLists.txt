cmake_minimum_required(VERSION 3.27)
project(Komodo)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  set(KOMODO_PLATFORM_WINDOWS TRUE)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
  set(KOMODO_PLATFORM_MACOS TRUE)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  set(KOMODO_PLATFORM_LINUX TRUE)
endif()

if(KOMODO_PLATFORM_WINDOWS OR KOMODO_PLATFORM_MACOS OR KOMODO_PLATFORM_LINUX)
  set(KOMODO_BACKEND_OPENGL TRUE)
endif()

if(KOMODO_BACKEND_OPENGL)
  set(KOMODO_BACKEND_GLFW TRUE)
endif()

message(${CMAKE_SYSTEM_NAME})

set(KOMODO_SRC_FILES
  src/komodo/komodo.hpp
)
source_group("src" FILES ${KOMODO_SRC_FILES})

set(KOMODO_SRC_INSTANCE_FILES
  src/komodo/instance/instance.hpp src/komodo/instance/instance.cpp
)
source_group("src/komodo/instance" FILES ${KOMODO_SRC_INSTANCE_FILES})

set(KOMODO_SRC_WINDOW_FILES
  src/komodo/window/window.hpp src/komodo/window/window.cpp
)
source_group("src/komodo/window" FILES ${KOMODO_SRC_WINDOW_FILES})

if(KOMODO_BACKEND_GLFW)
  set(KOMODO_SRC_GLFW_INSTANCE_FILES
    src/komodo/backend/glfw/instance/glfw_instance.hpp src/komodo/backend/glfw/instance/glfw_instance.cpp
  )
  source_group("src/backend/glfw/instance" FILES ${KOMODO_SRC_GLFW_INSTANCE_FILES})

  set(KOMODO_SRC_GLFW_WINDOW_FILES
    src/komodo/backend/glfw/window/glfw_window.hpp src/komodo/backend/glfw/window/glfw_window.cpp
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
  )
  source_group("src/backend/opengl/window" FILES ${KOMODO_SRC_OPENGL_WINDOW_FILES})
endif()

add_library(${PROJECT_NAME}
  ${KOMODO_SRC_FILES}

  ${KOMODO_SRC_INSTANCE_FILES}
  ${KOMODO_SRC_WINDOW_FILES}

  ${KOMODO_SRC_GLFW_INSTANCE_FILES}
  ${KOMODO_SRC_GLFW_WINDOW_FILES}

  ${KOMODO_SRC_OPENGL_INSTANCE_FILES}
  ${KOMODO_SRC_OPENGL_WINDOW_FILES}
)

target_include_directories(${PROJECT_NAME} PUBLIC src)

add_subdirectory(src/lib/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

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

add_subdirectory(example)
