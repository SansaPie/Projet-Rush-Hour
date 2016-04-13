set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_library(game STATIC game.c piece.c)

add_executable(main main.c solveur.c)
target_link_libraries(main game)

add_executable(solv solv2.c)
target_link_libraries(solv game)

#add_executable(interface InterfaceGraphique.c)
#target_link_libraries(interface game)

#add_executable(solveur solveur.c test/test_general.c)
#target_link_libraries(solveur game)
