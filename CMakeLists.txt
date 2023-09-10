cmake_minimum_required(VERSION 3.27)
project(Komodo)

set(KOMODO_SRC_FILES
  src/komodo/include/komodo.hpp
)
source_group("src" FILES ${KOMODO_SRC_FILES})

set(KOMODO_SRC_INSTANCE_FILES
  src/komodo/src/komodo/instance/instance.hpp src/komodo/src/komodo/instance/instance.cpp
)
source_group("src/komodo/instance" FILES ${KOMODO_SRC_INSTANCE_FILES})


set(KOMODO_SRC_OPENGL_INSTANCE_FILES
  src/komodo/src/backend/opengl/instance/opengl_instance.hpp src/komodo/src/backend/opengl/instance/opengl_instance.cpp
)
source_group("src/backend/opengl/instance" FILES ${KOMODO_SRC_OPENGL_INSTANCE_FILES})

add_library(${PROJECT_NAME}
  ${KOMODO_SRC_FILES}
  ${KOMODO_SRC_INSTANCE_FILES}
  ${KOMODO_SRC_OPENGL_INSTANCE_FILES}
)

target_include_directories(${PROJECT_NAME} PUBLIC src/komodo/include)
target_include_directories(${PROJECT_NAME} PRIVATE src/komodo/src)

add_subdirectory(example)
