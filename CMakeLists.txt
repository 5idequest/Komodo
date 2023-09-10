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
  set(KOMODO_PLATFORM_SUPPORTS_OPENGL TRUE)
endif()

message(${CMAKE_SYSTEM_NAME})

set(KOMODO_SRC_FILES
  src/komodo/include/komodo.hpp
)
source_group("src" FILES ${KOMODO_SRC_FILES})

set(KOMODO_SRC_INSTANCE_FILES
  src/komodo/src/komodo/instance/instance.hpp src/komodo/src/komodo/instance/instance.cpp
)
source_group("src/komodo/instance" FILES ${KOMODO_SRC_INSTANCE_FILES})

if(KOMODO_PLATFORM_SUPPORTS_OPENGL)
  set(KOMODO_SRC_OPENGL_INSTANCE_FILES
    src/komodo/src/backend/opengl/instance/opengl_instance.hpp src/komodo/src/backend/opengl/instance/opengl_instance.cpp
  )
  source_group("src/backend/opengl/instance" FILES ${KOMODO_SRC_OPENGL_INSTANCE_FILES})
endif()

add_library(${PROJECT_NAME}
  ${KOMODO_SRC_FILES}
  ${KOMODO_SRC_INSTANCE_FILES}
  ${KOMODO_SRC_OPENGL_INSTANCE_FILES}
)

target_include_directories(${PROJECT_NAME} PUBLIC src/komodo/include)
target_include_directories(${PROJECT_NAME} PRIVATE src/komodo/src)

if(KOMODO_PLATFORM_WINDOWS)
  target_compile_definitions(${PROJECT_NAME} PRIVATE KOMODO_PLATFORM_WINDOWS)
elseif(KOMODO_PLATFORM_MACOS)
  target_compile_definitions(${PROJECT_NAME} PRIVATE KOMODO_PLATFORM_MACOS)
elseif(KOMODO_PLATFORM_LINUX)
  target_compile_definitions(${PROJECT_NAME} PRIVATE KOMODO_PLATFORM_LINUX)
endif()

add_subdirectory(example)
