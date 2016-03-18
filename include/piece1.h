#ifndef PIECE_1_H
#define PIECE_1_H
#include <stdbool.h>

/**
 * @brief Returns true if the piece is small.
 */
bool is_small(cpiece p);

/**
 * @brief Returns false if the piece isn't entirely or at all in the board.
 */
bool is_in_board(cpiece p, int width, int height);

#endif