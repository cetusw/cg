cmake_minimum_required(VERSION 3.20)

project(cottage LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

add_executable(cottage
    main.cpp
    src/controller/Application.cpp
    src/model/Cottage.cpp
    src/model/Garage.cpp
    src/model/House.cpp
    src/model/Porch.cpp
    src/model/Scene.cpp
    src/view/GlfwWindow.cpp
    src/view/SceneRenderer.cpp
    src/view/Texture2D.cpp
)

target_include_directories(cottage PRIVATE src lib)
target_compile_definitions(cottage PRIVATE COTTAGE_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(cottage PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_link_libraries(cottage PRIVATE
    OpenGL::GL
    OpenGL::GLU
    glfw
    GLEW::GLEW
)
