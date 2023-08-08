cmake_minimum_required(VERSION 3.20)

project(hello-triangle)

add_executable(hello-triangle main.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
target_link_libraries(hello-triangle glfw)
target_link_libraries(hello-triangle OpenGL::GL)