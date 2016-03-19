include_directories(src)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/test)

add_executable(test_game1 test_game1.c test_general.c)
target_link_libraries(test_game1 game)

add_executable(test_piece1 test_piece1.c test_general.c)
target_link_libraries(test_piece1 game)

add_executable(test_game_ar test_game_ar.c test_general.c)
target_link_libraries(test_game_ar game)
