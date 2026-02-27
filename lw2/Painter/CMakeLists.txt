cmake_minimum_required(VERSION 3.15)
project(Painter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "Use dynamic SFML" FORCE)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include(FetchContent)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.90.4
)
FetchContent_MakeAvailable(imgui)

set(IMGUI_DIR ${imgui_SOURCE_DIR} CACHE PATH "Path to imgui" FORCE)
set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "Disable internal SFML search" FORCE)

FetchContent_Declare(
        imgui-sfml
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
        GIT_TAG v2.6
)
FetchContent_MakeAvailable(imgui-sfml)

FetchContent_Declare(
        pfd
        GIT_REPOSITORY https://github.com/samhocevar/portable-file-dialogs.git
        GIT_TAG main
)
FetchContent_GetProperties(pfd)
if (NOT pfd_POPULATED)
    FetchContent_Populate(pfd)
endif ()

set(APP_SOURCES
        main.cpp
        Model/Canvas.cpp
        Model/Canvas.h
        View/AppView.cpp
        View/AppView.h
        Controller/AppController.cpp
        Controller/AppController.h
        Model/Canvas.h
)

add_executable(Painter ${APP_SOURCES})

find_package(OpenGL REQUIRED)

target_link_libraries(Painter
        sfml-graphics
        sfml-window
        sfml-system
        ImGui-SFML::ImGui-SFML
        OpenGL::GL
)

target_include_directories(Painter PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
        ${pfd_SOURCE_DIR}
)