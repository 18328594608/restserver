cmake_minimum_required(VERSION 3.6)
project(msg)

set(SRC
       Msg.cpp
        )

add_library(${PROJECT_NAME} OBJECT ${SRC})

