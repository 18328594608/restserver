cmake_minimum_required(VERSION 3.6)
project(tool)

set(SRC
       Tool.cpp
        )

add_library(${PROJECT_NAME} OBJECT ${SRC})

