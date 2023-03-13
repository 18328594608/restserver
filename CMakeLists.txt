cmake_minimum_required(VERSION 3.21)
project(rsetserver)
set(CMAKE_CXX_STANDARD 17)


if(APPLE)
    # 在 macOS 系统下执行的代码
    set(OPENSSL_INCLUDE_DIR /opt/homebrew/opt/openssl@3/include)
    set(OPENSSL_CRYPTO_LIBRARY /opt/homebrew/opt/openssl@3/lib/libcrypto.dylib)
    set(OPENSSL_SSL_LIBRARY /opt/homebrew/opt/openssl@3/lib/libssl.dylib)
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

#set(ZLIB_INCLUDE_DIR /opt/homebrew/opt/zlib/include)
#set(WORKFLOW_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/_include/workflow)
#set(WORKFLOW_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/_lib)
#set(WORKFLOW_LIB_DIR ${PROJECT_SOURCE_DIR}/_lib)
#set(WFRSET_LIB_DIR ${PROJECT_SOURCE_DIR}/_lib/wfrest)

set(THIRD_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/_include/third_lib)
set(BASS_LOG_DIR ${PROJECT_SOURCE_DIR}/base)

if(ANDROID)
    link_directories(${OPENSSL_LINK_DIR})
else()
    find_library(LIBRT rt)
    find_package(OpenSSL REQUIRED)
endif()

if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/workflow/workflow-config.cmake.in")
    find_package(workflow REQUIRED CONFIG HINTS ./wfrest/workflow)
endif ()

find_package(wfrest REQUIRED CONFIG HINTS .)
find_package(ZLIB REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR} ${ZLIB_INCLUDE_DIR}
        ${WORKFLOW_INCLUDE_DIR} ${WFREST_INCLUDE_DIR}
        ${BASS_LOG_DIR})
include_directories(${THIRD_LIB_DIR})
link_directories(${WFREST_LIB_DIR} ${WORKFLOW_LIB_DIR})

#boost
find_package(Boost REQUIRED COMPONENTS system filesystem)
include_directories(${Boost_INCLUDE_DIRS})

#websocket
find_package(websocketpp REQUIRED CONFIG HINTS .)
include_directories(${WEBSOCKETPP_INCLUDE_DIR})
if (WEBSOCKETPP_FOUND)
    message("---------------- ${WEBSOCKETPP_INCLUDE_DIR}")
endif ()

add_subdirectory(http)
add_subdirectory(protocol)
add_subdirectory(base)
add_subdirectory(websocketpp)



include_directories(${WEBSOCKETPP_INCLUDE_DIR})

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_executable(rsetserver main.cpp)

if (APPLE)
    set(LINK_LIB ZLIB::ZLIB wfrest workflow  http protocol base)
else ()
    set(LINK_LIB wfrest workflow  ZLIB::ZLIB http protocol base)
endif ()

target_link_libraries(rsetserver PRIVATE
        ZLIB::ZLIB
        wfrest
        libworkflow.a
        ${Boost_LIBRARIES}
        http
        protocol
        base)