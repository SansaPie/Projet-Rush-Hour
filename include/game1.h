#ifndef _GAME_1_H_
#define _GAME_1_H_
#include <stdbool.h>
#include "piece.h"

/**
 * @brief Allocates memory for an array of piece.
 * @param nb_pieces number of pieces to allocate.
 * @param pieces array to allocate.
 * @param msg name of the function where the allocation takes place.
 */
piece * allocation_piece_tab(int nb_pieces, char * msg);

/**
 * @brief Destroys pieces and frees allocated memory.
 * @param nb_pieces number of pieces to destroy.
 * @param pieces the pieces to destroy.
 */
void delete_pieces(int nb_pieces, piece * pieces);

/**
 * @brief Tests if the pieces of g are not in collision or out.
 * @return true if the game is valid.
 */
bool game_valid(cgame g);

#endif
