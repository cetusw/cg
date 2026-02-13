cmake_minimum_required(VERSION 4.0)
project(Letters)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Letters main.cpp
        Model/Letter.cpp
        Model/Letter.h
        View/LetterView.cpp
        View/LetterView.h
        Controller/Simulation.cpp
        Controller/Simulation.h
)

target_link_libraries(Letters sfml-graphics sfml-window sfml-system)
