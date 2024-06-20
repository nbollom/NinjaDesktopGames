cmake_minimum_required(VERSION 3.27)
project(nanovg)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES
    src/nanovg.c
)

add_library(nanovg ${SOURCES})
target_include_directories(nanovg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)