cmake_minimum_required(VERSION 3.20)

project(scene LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

find_path(LIB3DS_INCLUDE_DIR lib3ds/file.h REQUIRED)
find_library(LIB3DS_LIBRARY NAMES 3ds-1 lib3ds-1 REQUIRED)

add_executable(scene
        main.cpp
        src/controller/Application.cpp
        src/controller/CameraController.cpp
        src/model/Model3ds.cpp
        src/model/ModelInstance.cpp
        src/model/Scene.cpp
        src/view/GlfwWindow.cpp
        src/view/SceneRenderer.cpp
        src/view/Texture2D.cpp
        src/model/types/Camera.h
        src/model/types/Camera.h
        src/controller/Application.cpp
)

target_include_directories(scene PRIVATE src ${LIB3DS_INCLUDE_DIR})
target_compile_definitions(scene PRIVATE SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(scene PRIVATE -Wall -Wextra -Wpedantic)
endif ()

target_link_libraries(scene PRIVATE
        OpenGL::GL
        OpenGL::GLU
        glfw
        GLEW::GLEW
        glm::glm
        ${LIB3DS_LIBRARY}
)
