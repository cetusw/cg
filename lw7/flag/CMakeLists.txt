cmake_minimum_required(VERSION 3.20)

project(ring LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_executable(ring
	main.cpp
	src/controller/Application.cpp
	src/view/GlfwWindow.cpp
	src/view/SceneRenderer.cpp
	src/view/Shader.cpp
	src/view/ShaderProgram.cpp
)

target_include_directories(ring PRIVATE src)
target_compile_definitions(ring PRIVATE SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	target_compile_options(ring PRIVATE -Wall -Wextra -Wpedantic)
endif ()

target_link_libraries(ring PRIVATE
	OpenGL::GL
	glfw
	GLEW::GLEW
	glm::glm
)
