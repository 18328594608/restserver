cmake_minimum_required(VERSION 3.6)
project(protocol)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../http)


set(SRC
        BaseProtocol.cpp
        UserInfo.cpp
        ProtocolHdl.cpp
        DepositChange.cpp
        HistoryOrders.cpp
        )

add_library(${PROJECT_NAME} OBJECT ${SRC})