cmake_minimum_required(VERSION 3.27)
project(mines)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES
    main.cpp
        state.cpp
        state.hpp
        game_scene.cpp
        game_scene.hpp
        game.cpp
        game.hpp
        cell.cpp
        cell.hpp
)

add_executable(mines ${SOURCES})
target_link_libraries(mines common)
target_compile_options(mines PRIVATE -Wall -Wextra -Wpedantic -Wnull-dereference -Wcast-align -Wnon-virtual-dtor -Wno-unused-parameter)