cmake_minimum_required(VERSION 4.0)
project(Asteroids CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(
        ${OPENGL_INCLUDE_DIRS}
        ${GLUT_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}
)

set(SOURCE_FILES
        main.cpp
        model/Ship.cpp
        view/GameView.cpp
        controller/GLApplication.cpp
        controller/GLApplication.h
        controller/AsteroidsApplication.cpp
        controller/AsteroidsApplication.h
)

add_executable(Asteroids ${SOURCE_FILES})

target_link_libraries(Asteroids
        ${GLUT_LIBRARIES}
        ${OPENGL_LIBRARIES}
        GLU
        m
)