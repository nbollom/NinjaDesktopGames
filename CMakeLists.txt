cmake_minimum_required(VERSION 3.27)
project(ninja_desktop_games)

#find_program(CCACHE_PROGRAM ccache)
#if(CCACHE_PROGRAM)
#    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
#endif()

add_subdirectory(common)
add_subdirectory(mines)

add_custom_target(ninja_desktop_games ALL DEPENDS common mines)
