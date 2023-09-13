cmake_minimum_required(VERSION 3.27)
project(glad)

add_library(${PROJECT_NAME} include/glad/gl.h include/KHR/khrplatform.h src/gl.c)

target_include_directories(${PROJECT_NAME} PUBLIC include)
