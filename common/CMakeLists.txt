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
    ${CMAKE_CURRENT_BINARY_DIR}/resources.cpp
    resources.hpp
)

file(READ DejaVuSans.ttf embedded_font_data HEX)
string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," embedded_font_data ${embedded_font_data})
configure_file(resources.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/resources.cpp @ONLY)

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
        gl3w
        GIT_REPOSITORY https://github.com/skaslev/gl3w.git
)

set(nano_patch_command ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/nanovg.cmake CMakelists.txt)
FetchContent_Declare(
    nanovg
    GIT_REPOSITORY https://github.com/memononen/nanovg.git
)

FetchContent_MakeAvailable(glfw gl3w)

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
target_link_libraries(common PUBLIC glfw nanovg OpenGL::GL gl3w)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(common PRIVATE ${extra_compile_options})
