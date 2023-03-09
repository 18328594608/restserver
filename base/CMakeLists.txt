cmake_minimum_required(VERSION 3.6)
project(base)

set(SRC
        json.hpp
        Log.cpp
        Config.cpp
        )

add_library(${PROJECT_NAME} OBJECT ${SRC})

