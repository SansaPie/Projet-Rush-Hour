#ifndef _TEST_GENERAL_H_
#define _TEST_GENERAL_H_
#include <stdbool.h>
#include "game.h"
#include "game1.h"
#include "piece.h"
#include "piece1.h"

#define NB_PIECES 7

piece pieces[NB_PIECES];

/**
* @brief test if value is equal to expected; if not, displays an error message containing msg to standard error output
* @return true if expected==value
*/
bool test_equality_bool(bool expected, bool  value, char *msg);

/**
* @brief test if value is equal to expected; if not, displays an error message containing msg to standard error output
*/
bool test_equality_int(int expected, int value, char *msg);

/**
* @brief test if value is equal to expected ; if not program abort
* @return true if expected == value
*/
bool test_equality_piece(cpiece expected, cpiece value, char *msg);

/**
* @brief same test as test_equality_piece
*/
bool test_equality_game(cgame expected, cgame value, char * msg);

/**
* @brief Test les toutes pieces du jeu.
* @return vrai si les pieces sont correctes, faux sinon.
*/
bool test_game_piece(cgame gtest);

void set_up();

void tear_down();

#endif // !_TEST_GENERAL_H_
