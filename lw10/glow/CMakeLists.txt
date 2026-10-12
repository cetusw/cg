cmake_minimum_required(VERSION 3.20)

project(glow LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_executable(glow
	main.cpp
	src/controller/Application.cpp
	src/controller/CameraController.cpp
	src/model/Cottage.cpp
	src/model/Fence.cpp
	src/model/FencePost.cpp
	src/model/FenceSection.cpp
	src/model/Garage.cpp
	src/model/House.cpp
	src/model/Lamp.cpp
	src/model/Porch.cpp
	src/model/Scene.cpp
	src/view/Framebuffer.cpp
        src/view/blur/GaussianBlur.cpp
	src/view/GeometryRenderer.cpp
	src/view/GlfwWindow.cpp
	src/view/GlowRenderer.cpp
		src/view/blur/LightMotionBlur.cpp
	src/view/SceneRenderer.cpp
	src/view/Shader.cpp
	src/view/ShaderProgram.cpp
	src/view/Texture2D.cpp
)

target_include_directories(glow PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
	"${CMAKE_CURRENT_SOURCE_DIR}/lib"
)
target_compile_definitions(glow PRIVATE SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	target_compile_options(glow PRIVATE -Wall -Wextra -Wpedantic)
endif ()

target_link_libraries(glow PRIVATE
	OpenGL::GL
	OpenGL::GLU
	glfw
	GLEW::GLEW
	glm::glm
)
