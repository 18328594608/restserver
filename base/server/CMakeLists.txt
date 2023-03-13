cmake_minimum_required(VERSION 3.6)
project(server)

set(SRC
        CoreServer.cpp
        Server.cpp
        wsServer.cpp
        PraseServer.cpp
        )

add_library(${PROJECT_NAME} OBJECT ${SRC})

