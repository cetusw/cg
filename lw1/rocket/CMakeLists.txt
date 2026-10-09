cmake_minimum_required(VERSION 3.20)
project(rocket LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SFML_STATIC_LIBRARIES ON)

find_package(SFML 3 COMPONENTS Graphics REQUIRED)

add_executable(rocket
	main.cpp
	src/Application.cpp
	src/model/Picture.cpp
	src/model/Rocket.cpp
	src/view/PictureView.cpp
	src/controller/PictureController.cpp
	src/controller/DragController.cpp
)

target_link_libraries(rocket PRIVATE SFML::Graphics)
