cmake_minimum_required(VERSION 2.6)
project(rush-hour)
add_definitions(-std=c99 -Wall -Werror -g)
set(CMAKE_INSTALL_PREFIX ../build)

add_library(game game.c piece.c)

add_executable(rush-hour main.c)
target_link_libraries(rush-hour game)