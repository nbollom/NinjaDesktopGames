cmake_minimum_required(VERSION 3.27)
project(common)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES
    common.hpp
    common.cpp
    window.hpp
    window.cpp
    toolbar.hpp
    colour.hpp
    colour.cpp
    scene.hpp
    toolbar.cpp
    drawable.hpp
    toolbar_item.hpp
    toolbar_button.cpp
    toolbar_button.hpp
    clickable.hpp
    clickable.cpp
    menu.cpp
    menu.hpp
    key_binding.hpp
)

find_package(OpenGL 3.2 REQUIRED)

include(FetchContent)
set(FETCHCONTENT_QUIET off)
set(FETCHCONTENT_UPDATES_DISCONNECTED on)

# General FetchContent stuff
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.9
)

FetchContent_Declare(
    GLEW
    GIT_REPOSITORY https://github.com/nigels-com/glew.git
    GIT_TAG glew-2.2.0
    FIND_PACKAGE_ARGS 2.2.0
)

set(nano_patch_command ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/nanovg.cmake CMakelists.txt)
FetchContent_Declare(
    nanovg
    GIT_REPOSITORY https://github.com/memononen/nanovg.git
)

FetchContent_MakeAvailable(glfw GLEW)

FetchContent_GetProperties(nanovg)
if(NOT nanovg_POPULATED)
    FetchContent_Populate(nanovg)
    file(COPY_FILE nanovg.cmake ${nanovg_SOURCE_DIR}/CMakeLists.txt ONLY_IF_DIFFERENT)
    add_subdirectory(${nanovg_SOURCE_DIR} ${nanovg_BINARY_DIR})
endif()

if(WIN32)
    set(extra_compile_options -Wall)
else ()
    set(extra_compile_options -Wall -Wextra -Wpedantic -Wnull-dereference -Wcast-align -Wnon-virtual-dtor)
endif()

add_library(common ${SOURCES})
target_link_libraries(common PUBLIC glfw nanovg OpenGL::GL GLEW)
target_include_directories(common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(common PRIVATE ${extra_compile_options})
