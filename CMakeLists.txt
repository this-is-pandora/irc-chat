cmake_minimum_required(VERSION 3.15)

project(IRC_CHAT VERSION 1.0
                 DESCRIPTION "Implements an IRC network"
                 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(("${PROJECT_SOURCE_DIR}"))
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

file(GLOB ALL_SRCS 
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/include/security/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(irc ${ALL_SRCS})