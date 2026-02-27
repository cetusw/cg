cmake_minimum_required(VERSION 4.0)
project(Viewer)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Viewer
        main.cpp
        Model/Image.cpp
        View/ImageView.cpp
        View/BackgroundView.cpp
        View/MenuView.cpp
        Application.cpp
        Utils/PipeDescriptor.cpp
        View/Observer/IObserver.h
        Model/Observable/Observable.cpp
        Model/Observable/Observable.h
        Controller/ImageController.cpp
        Controller/ImageController.h
        Controller/AppController.cpp
        Controller/AppController.h
        Model/WindowSettings.cpp
        Model/WindowSettings.h
        Model/Menu.cpp
        Model/Menu.h
)

target_link_libraries(Viewer PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
)