#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "game1.h"
#include "piece.h"
#include "piece1.h"
#include "test_general.h"

#define NB_PIECES 7
#define HEIGHT_AR 5
#define WIDTH_AR 4

void set_up() {
	pieces[0] = new_piece_rh(3, 3, true, true);
	pieces[1] = new_piece_rh(3, 0, true, false);
	pieces[2] = new_piece_rh(4, 1, true, true);
	pieces[3] = new_piece_rh(5, 3, false, false);
	pieces[4] = new_piece_rh(0, 4, true, true);
	pieces[5] = new_piece_rh(1, 2, true, false);
	pieces[6] = new_piece_rh(3, 4, true, false);
}

void tear_down() {
	for (int i = 0; i < NB_PIECES; i++)
		delete_piece(pieces[i]);
}

void set_up_win_ar() {
	pieces[0] = new_piece_rh(1, 0, true, true);
}

void tear_down_win_ar() {
	delete_piece(pieces[0]);
}

bool test_game_square_piece() {
	bool result = true;
	set_up();
	game test = new_game(WIDTH_HR, HEIGHT_HR, NB_PIECES, pieces);
	result = result && test_equality_int(2, game_square_piece(test, 4, 1), "game_square_piece present");
	result = result && test_equality_int(-1, game_square_piece(test, 0, 0), "game_square_piece not present");
	delete_game(test);
	tear_down();
	return result;
}

bool test_game_over_ar() {
	bool result = true;

	set_up();
	game test = new_game(WIDTH_AR, HEIGHT_AR, NB_PIECES, pieces);
	result = result && test_equality_bool(false, game_over_hr(test), "game_over_ar not end");
	delete_game(test);
	tear_down();

	set_up_win_ar();
	game test2 = new_game(WIDTH_AR, HEIGHT_AR, 1, pieces);

	result = result && test_equality_bool(true, game_over_ar(test2), "game_over_ar end");
	delete_game(test2);
	tear_down_win_ar();

	return result;
}

bool test_new_game() {
	bool result = true;
	set_up();
	game test = new_game(WIDTH_AR, HEIGHT_AR, NB_PIECES, pieces);
	result = result && test_game_piece(test);
	result = result && test_equality_int(NB_PIECES, game_nb_pieces(test), "game_nb_pieces");
	result = result && test_equality_int(0, game_nb_moves(test), "game_nb_moves");
	result = result && test_equality_int(WIDTH_AR, game_width(test), "game_width");
	result = result && test_equality_int(HEIGHT_AR, game_height(test), "game_height");
	delete_game(test);
	tear_down();
	return result;
}