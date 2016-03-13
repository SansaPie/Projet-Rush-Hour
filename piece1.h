#ifndef PIECE_1_H
#define PIECE_1_H
#include <stdbool.h>

/**
 * @brief Allocates a boolean matrix
 */
bool ** allocation_bool_matrix(int width, int height);

/**
 * @brief Returns false if the piece is not put over an other in tmp
 * @param p piece put in board
 * @param tmp board as a boolean matrix
 * @param x-coor of the piece
 * @param y-coor of the piece
 */
bool put_piece_in_board(cpiece p, bool *** tmp, int x, int y);

/**
 * @brief Returns true if the piece is small
 */
bool is_small(cpiece p);

/**
 * @brief Returns false if the piece isn't entirely in the board
 */
bool is_in_board(cpiece p);

#endif