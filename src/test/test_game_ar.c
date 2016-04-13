#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "piece.h"
#include "piece1.h"
#include "game.h"
#include "game1.h"
#include "test_general.h"

#define HEIGHT_AR 5
#define WIDTH_AR 4

/**
 * @brief Sets up a game in a winning state.
 */
void set_up_win_ar(){
	pieces[0] = new_piece_rh(1, 0, true, true);
}

/**
 * @brief Deletes the game previously set up.
 */
void tear_down_win_ar(){
	delete_piece(pieces[0]);
}

/**
 * @brief Tests the function game_square_piece.
 * @returns true if it works ; false otherwise.
 */
bool test_game_square_piece_ar(){
	bool result = true;
	set_up();
	game test = new_game(WIDTH_AR, HEIGHT_AR, NB_PIECES, pieces);
	result = result && test_equality_int(2, game_square_piece(test, 4, 1), "game_square_piece present");
	result = result && test_equality_int(-1, game_square_piece(test, 0, 0), "game_square_piece not present");
	delete_game(test);
	tear_down();
	return result;
}

/**
 * @brief Tests the function copy_game.
 * @returns true if it works ; false otherwise.
 */
bool test_copy_game_ar(){
	bool result = true;
	set_up();
	game test = new_game(WIDTH_AR, HEIGHT_AR, NB_PIECES, pieces);

	piece * t_pieces = malloc(sizeof(struct piece_s)*game_nb_pieces(test));
	for (int i = 0; i < game_nb_pieces(test); i++) {
		t_pieces[i] = new_piece(0, 0, 1, 1, true, true);
	}

	game copy_test = new_game(1, 1, NB_PIECES, pieces);
	copy_game(test, copy_test);
	result = result && test_equality_game(test, copy_test, "copy_game");
	delete_pieces(game_nb_pieces(test), t_pieces);
	tear_down();
	delete_game(test);
	delete_game(copy_test);
	return result;
}

/**
 * @brief Tests the function game_over_ar.
 * @returns true if it works ; false otherwise.
 */
bool test_game_over_ar(){
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

/**
 * @brief Tests the function new_game.
 * @returns true if it works ; false otherwise.
 */
bool test_new_game(){
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

/**
 * @brief Tests the function game_nb_pieces.
 * @returns true if it works ; false otherwise.
 */
bool test_game_nb_pieces_ar(){
	bool result = true;
	set_up();
	game test = new_game(WIDTH_AR, HEIGHT_AR, NB_PIECES, pieces);
	result = result && test_equality_int(NB_PIECES, game_nb_pieces(test), "game_nb_piece");
	tear_down();
	delete_game(test);
	return result;
}

/**
 * @brief main test.
 * @return exit_success.
 */
int main(){
	bool result = true;
	result = result && test_equality_bool(true, test_new_game(), "new_game");
	result = result && test_equality_bool(true, test_game_over_ar(), "game_over_ar");
	result = result && test_equality_bool(true, test_game_square_piece_ar(), "game_square_piece_ar");
	result = result && test_equality_bool(true, test_copy_game_ar(), "copy_game_ar");
	result = result && test_equality_bool(true, test_game_nb_pieces_ar(), "game_nb_pieces_ar");
	if (!result){
		printf("Test_game_ar failed!\n");
		return EXIT_FAILURE;
	}
	printf("Test_game_ar passed!\n");
	return EXIT_SUCCESS;
}