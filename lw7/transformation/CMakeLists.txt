cmake_minimum_required(VERSION 3.20)

project(transformation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_executable(transformation
        main.cpp
        src/controller/Application.cpp
        src/controller/CameraController.cpp
        src/view/GlfwWindow.cpp
        src/view/ParametricGrid.cpp
        src/view/SceneRenderer.cpp
        src/view/Shader.cpp
        src/view/ShaderProgram.cpp
        src/view/ShaderProgram.h
)

target_include_directories(transformation PRIVATE src)
target_compile_definitions(transformation PRIVATE SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(transformation PRIVATE -Wall -Wextra -Wpedantic)
endif ()

target_link_libraries(transformation PRIVATE
        OpenGL::GL
        OpenGL::GLU
        glfw
        GLEW::GLEW
        glm::glm
)
