cmake_minimum_required(VERSION 4.0)
project(polyhedron)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

add_executable(polyhedron main.cpp
        controller/GLFWApplication.cpp
        controller/GLFWApplication.h
        controller/PolyhedronApp.cpp
        controller/PolyhedronApp.h
        model/Face.h
        view/Polyhedron.cpp
        view/Polyhedron.h
        controller/DirectLight.cpp
        controller/DirectLight.h
)

target_link_libraries(polyhedron
        glfw
        GL
        GLU
        glm::glm
)