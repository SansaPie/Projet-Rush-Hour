cmake_minimum_required (VERSION 2.8)

project (projet)

add_definitions (-std=c99 -Wall -Werror -g)

set (CMAKE_INSTALL_PREFIX .)

enable_testing ()

add_library(libpiece piece.c)
