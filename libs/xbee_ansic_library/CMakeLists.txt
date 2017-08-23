cmake_minimum_required(VERSION 3.5)

message( STATUS- "Compiling XBee Library")

add_definitions(-DPOSIX -DXBEE_ATMODE_DEBUG -DXBEE_DEVICE_ENABLE_ATMODE)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
set(BASE_INCL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${BASE_INCL_DIR})
add_library(XBee SHARED ${SOURCES})
