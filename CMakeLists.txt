cmake_minimum_required(VERSION 3.21)
project(rsetserver)
set(CMAKE_CXX_STANDARD 17)

##set(WFREST_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/_include)

if(APPLE)
    # 在 macOS 系统下执行的代码
    set(OPENSSL_INCLUDE_DIR /opt/homebrew/opt/openssl@3/include)
    set(OPENSSL_CRYPTO_LIBRARY /opt/homebrew/opt/openssl@3/lib/libcrypto.dylib)
    set(OPENSSL_SSL_LIBRARY /opt/homebrew/opt/openssl@3/lib/libssl.dylib)
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

#set(ZLIB_INCLUDE_DIR /opt/homebrew/opt/zlib/include)
#set(WORKFLOW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/_include/workflow)
#set(WORKFLOW_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/_lib)
#set(WORKFLOW_LIB_DIR ${PROJECT_SOURCE_DIR}/_lib)
#set(WFRSET_LIB_DIR ${PROJECT_SOURCE_DIR}/_lib/wfrest)

set(SPD_LOG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/_include/third_lib)
set(BASS_LOG_DIR ${PROJECT_SOURCE_DIR}/base)

if(ANDROID)
    link_directories(${OPENSSL_LINK_DIR})
else()
    find_library(LIBRT rt)
    find_package(OpenSSL REQUIRED)
endif()

find_package(wfrest REQUIRED CONFIG HINTS .)
if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/workflow/workflow-config.cmake.in")
    find_package(workflow REQUIRED CONFIG HINTS ./wfrest/workflow)
endif ()

if (wfrest_FOUND)
    message(STATUS "Found wfrest: ${WFREST_LIB_DIR} ${WORKFLOW_LIB_DIR}")
else()
    message(FATAL_ERROR "Could not find wfrest library-----------------------------------")
endif()

find_package(ZLIB REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR} ${ZLIB_INCLUDE_DIR}
        ${WORKFLOW_INCLUDE_DIR} ${WFREST_INCLUDE_DIR}
        ${BASS_LOG_DIR})

link_directories(${WFREST_LIB_DIR} ${WORKFLOW_LIB_DIR})
include_directories(${SPD_LOG_DIR})

add_subdirectory(http)
add_subdirectory(protocol)
add_subdirectory(base)

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
        workflow
        ${Boost_LIBRARIES}
        http
        protocol
        base)