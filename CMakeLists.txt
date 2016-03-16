cmake_minimum_required(VERSION 2.8)
project(rush-hour)
add_definitions(-std=c99 -Wall -Werror -g)
set(CMAKE_INSTALL_PREFIX ../build)

add_library(game game.c piece.c)

add_executable(main main.c)
target_link_libraries(main game)

add_executable(test_game1 test_game1.c)
target_link_libraries(test_game1 game)


add_executable(test_piece1 test_piece1.c)
target_link_libraries(test_piece1 game)

file(GLOB Fichiers_Config . *[0-9].txt)

file(INSTALL ${Fichiers_Config}  DESTINATION config)
