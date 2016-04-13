set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_library(game STATIC game.c piece.c input.c)
add_library(games STATIC ane_rouge.c rush_hour.c)

add_executable(main main.c) 
target_link_libraries(main game games)
