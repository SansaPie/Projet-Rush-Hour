set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_library(game STATIC game.c piece.c)

add_executable(main main.c) 
target_link_libraries(main game)
