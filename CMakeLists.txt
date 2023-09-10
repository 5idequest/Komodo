cmake_minimum_required(VERSION 3.27)
project(Komodo)

add_library(${PROJECT_NAME}
  src/komodo/include/komodo.hpp src/komodo/src/komodo.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC src/komodo/include)
target_include_directories(${PROJECT_NAME} PRIVATE src/komodo/src)

add_subdirectory(example)
