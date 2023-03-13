cmake_minimum_required(VERSION 3.6)
project(base)

add_subdirectory(common)
add_subdirectory(msg)
add_subdirectory(tool)
add_subdirectory(server)

set(SRC
        admin/Admin.cpp
        admin/WsAdmin.cpp
        json.hpp
        Log.cpp
        Config.cpp
        )

add_library(${PROJECT_NAME} OBJECT ${SRC})

