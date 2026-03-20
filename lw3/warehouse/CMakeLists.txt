cmake_minimum_required(VERSION 4.0)
project(warehouse)

set(CMAKE_CXX_STANDARD 20)

add_executable(warehouse main.cpp
        Warehouse.cpp
        Warehouse.h
        workers/Worker.cpp
        workers/Worker.h
        workers/Supplier.cpp
        workers/Supplier.h
        workers/Client.cpp
        workers/Client.h
        workers/Auditor.cpp
        workers/Auditor.h
        utils/Rand.h
        utils/Config.h
        utils/SignalHandler.cpp
        utils/SignalHandler.h
        Application.cpp
        Application.h
)
