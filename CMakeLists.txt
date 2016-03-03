cmake_minimum_required (VERSION 2.8)

project (projet)

add_definitions (-std=c99 -Wall -Werror -g)

set (CMAKE_INSTALL_PREFIX .)

enable_testing ()

add_library(piece piece.c)

add_library(game game.c)

add_executable(test_piece piece.c test_piece.c)

add_executable(test_game game.c test_game.c piece.c)

add_executable(main main.c game.c piece.c)

add_executable(test_piece1 test_piece1.c piece.c)