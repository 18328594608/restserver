cmake_minimum_required(VERSION 3.6)
project(http)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../base)

set(SRC
        http_server/Server.cpp
        http_client/HttpClient.cpp
        HttpErrMsg.cpp
        )

add_library(${PROJECT_NAME} OBJECT ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/protocol)
