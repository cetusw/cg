cmake_minimum_required(VERSION 3.20)

project(cottage LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

add_executable(cottage
        src/main.cpp
)

target_link_libraries(cottage PRIVATE
        OpenGL::GL
        OpenGL::GLU
        glfw
        GLEW::GLEW
)