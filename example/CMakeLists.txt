cmake_minimum_required(VERSION 3.27)
project(KomodoExample)

set(KOMODO_EXAMPLE_SRC_FILES
  src/main.cpp
)
source_group("src" FILES ${KOMODO_EXAMPLE_SRC_FILES})

add_executable(${PROJECT_NAME}
  ${KOMODO_EXAMPLE_SRC_FILES}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME} PRIVATE Komodo)
