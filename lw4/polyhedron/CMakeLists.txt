cmake_minimum_required(VERSION 3.20)

project(polyhedron LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_executable(polyhedron
	main.cpp
	controller/Application.cpp
	controller/CameraController.cpp
	io/ObjParser.cpp
	model/Mesh.cpp
	model/Scene.cpp
	view/GlfwWindow.cpp
	view/MeshRenderer.cpp
	view/SceneRenderer.cpp
)

target_include_directories(polyhedron PRIVATE .)
target_compile_definitions(polyhedron PRIVATE SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_options(polyhedron PRIVATE -Wall -Wextra -Wpedantic)

target_link_libraries(polyhedron PRIVATE
	OpenGL::GL
	OpenGL::GLU
	glfw
	GLEW::GLEW
	glm::glm
)
