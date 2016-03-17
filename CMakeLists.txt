cmake_minimum_required(VERSION 2.8)
project(rush-hour)

add_definitions(-std=c99 -Wall -Werror -g)

set(CMAKE_INSTALL_PREFIX ../build)

include_directories(include)
add_subdirectory(src)
add_subdirectory(src/test)
add_subdirectory(config)