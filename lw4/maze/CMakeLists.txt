cmake_minimum_required(VERSION 3.20)

project(maze LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_executable(maze
	main.cpp
	src/controller/Application.cpp
	src/model/Maze.cpp
	src/model/PlayerCamera.cpp
	src/view/GlfwWindow.cpp
	src/view/SceneRenderer.cpp
)

target_include_directories(maze PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	target_compile_options(maze PRIVATE -Wall -Wextra -Wpedantic)
endif ()

target_link_libraries(maze PRIVATE
	OpenGL::GL
	OpenGL::GLU
	glfw
	GLEW::GLEW
	glm::glm
)
