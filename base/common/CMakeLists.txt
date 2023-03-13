cmake_minimum_required(VERSION 3.6)
project(common)

set(SRC
        proxy/Proxy.cpp
        websocket/WebSocket.cpp
        pool/Pool.cpp
        )

add_library(${PROJECT_NAME} OBJECT ${SRC})

