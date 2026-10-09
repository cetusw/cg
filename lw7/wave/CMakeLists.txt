cmake_minimum_required(VERSION 3.20)

project(wave LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_path(STB_IMAGE_INCLUDE_DIR stb/stb_image.h REQUIRED)

add_executable(wave
	main.cpp
	src/controller/Application.cpp
	src/view/GlfwWindow.cpp
	src/view/SceneRenderer.cpp
	src/view/Shader.cpp
	src/view/ShaderProgram.cpp
	src/view/Texture2D.cpp
)

target_include_directories(wave PRIVATE src ${STB_IMAGE_INCLUDE_DIR})
target_compile_definitions(wave PRIVATE SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	target_compile_options(wave PRIVATE -Wall -Wextra -Wpedantic)
endif ()

target_link_libraries(wave PRIVATE
	OpenGL::GL
	glfw
	GLEW::GLEW
	glm::glm
)
