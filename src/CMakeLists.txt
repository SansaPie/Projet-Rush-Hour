set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_library(game STATIC game.c piece.c)

add_executable(main main.c)
target_link_libraries(main game)

add_executable(mainInterfaceGraphique mainIntGraph.c intGraph.c)
target_link_libraries(mainInterfaceGraphique game ${SDL_LIBRARIES} ${SDLIMAGE_LIBRARIES})

add_executable(solveur solv.c)
target_link_libraries(solveur game)