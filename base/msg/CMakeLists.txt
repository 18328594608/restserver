cmake_minimum_required(VERSION 3.6)
project(msg)

set(SRC
       Msg.cpp
        ReqMsg.cpp
        RspMsg.cpp
        )

add_library(${PROJECT_NAME} OBJECT ${SRC})

