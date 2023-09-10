cmake_minimum_required(VERSION 3.27)
project(Komodo)

set(KOMODO_SRC_FILES
  src/komodo/include/komodo.hpp src/komodo/src/komodo.cpp
)
source_group("src" FILES ${KOMODO_SRC_FILES})

add_library(${PROJECT_NAME}
  ${KOMODO_SRC_FILES}
)

target_include_directories(${PROJECT_NAME} PUBLIC src/komodo/include)
target_include_directories(${PROJECT_NAME} PRIVATE src/komodo/src)

add_subdirectory(example)
