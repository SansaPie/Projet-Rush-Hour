cmake_minimum_required(VERSION 2.8)

project(RUSH_HOUR)

set(RUSH_HOUR_VERSION_MAJOR "1")
set(RUSH_HOUR_VERSION_MINOR "1")
set(RUSH_HOUR_VERSION_PATCH "2")
set(RUSH_HOUR_VERSION "${RUSH_HOUR_VERSION_MAJOR}.${RUSH_HOUR_VERSION_MINOR}.${RUSH_HOUR_VERSION_PATCH}")

set(CMAKE_INSTALL_PREFIX ../build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_C_FLAGS "-std=c99 -g -Wall -Werror")
#set(CMAKE_EXE_LINKER_FLAGS "-ftest-coverage -fprofile-arcs")

include_directories(include)

add_subdirectory(src)
add_subdirectory(src/test)
add_subdirectory(config)

ENABLE_TESTING()
add_test(test_game_ar bin/test/test_game_ar.exe "TEST 1")
add_test(test_game_rh bin/test/test_game1.exe "TEST 2")
add_test(test_piece_rh bin/test/test_piece1.exe "TEST 3")