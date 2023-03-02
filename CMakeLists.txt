cmake_minimum_required(VERSION 3.21)
project(rsetserver)
set(CMAKE_CXX_STANDARD 17)


set(OPENSSL_INCLUDE_DIR /opt/homebrew/opt/openssl@3/include)
set(OPENSSL_CRYPTO_LIBRARY /opt/homebrew/opt/openssl@3/lib/libcrypto.dylib)
set(OPENSSL_SSL_LIBRARY /opt/homebrew/opt/openssl@3/lib/libssl.dylib)
set(ZLIB_INCLUDE_DIR /opt/homebrew/opt/zlib/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
#set(WORKFLOW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/_include/workflow)
#set(WORKFLOW_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/_lib)

set(WORKFLOW_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/_include/workflow)
set(WFREST_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/_include)
set(SPD_LOG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/_include/third_lib)
set(BASS_LOG_DIR ${PROJECT_SOURCE_DIR}/base)


set(WORKFLOW_LIB_DIR ${PROJECT_SOURCE_DIR}/_lib)
set(WFRSET_LIB_DIR ${PROJECT_SOURCE_DIR}/_lib/wfrest)

if(ANDROID)
    link_directories(${OPENSSL_LINK_DIR})
else()
    find_library(LIBRT rt)
    find_package(OpenSSL REQUIRED)
endif()


find_package(workflow REQUIRED CONFIG HINTS ..)
find_package(wfrest REQUIRED CONFIG HINTS ..)
find_package(ZLIB REQUIRED)


include_directories(${OPENSSL_INCLUDE_DIR} ${ZLIB_INCLUDE_DIR}
        ${WORKFLOW_INCLUDE_DIR} ${WFREST_INCLUDE_DIR}
        ${BASS_LOG_DIR})

link_directories(${WORKFLOW_LIB_DIR} ${WFRSET_LIB_DIR})
include_directories(${SPD_LOG_DIR})

add_subdirectory(http)
add_subdirectory(protocol)
add_subdirectory(base)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(rsetserver main.cpp)
target_link_libraries(rsetserver PRIVATE
        ZLIB::ZLIB
        libworkflow.a
        libwfrest.a
        http
        protocol
        base)