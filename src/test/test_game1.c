#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "game1.h"
#include "piece.h"
#include "piece1.h"
#include "test_general.h"

#define HEIGHT_RH 6
#define WIDTH_RH 6

/**
 * @brief Creation of piece 0 in victory position
 */
void set_up_win() {  
	pieces[0] = new_piece_rh(4, 3, true, true);
}

/**
 * @brief delete the victory piece
 */

void tear_down_win() {  
	delete_piece(pieces[0]);
}

/**
 * @brief Test initialisation of the game
 * @return true if initialisation is OK, false otherwise
 */
bool test_new_game_rh() { 
	bool result = true;
	set_up();
	game test = new_game_hr(NB_PIECES , pieces);
	result = result && test_game_piece(test);
	result = result && test_equality_int(NB_PIECES, game_nb_pieces(test), "game_nb_pieces");
	result = result && test_equality_int(0, game_nb_moves(test) , "game_nb_moves");
	result = result && test_equality_int(WIDTH_RH, game_width(test), "game_width");
	result = result && test_equality_int(HEIGHT_RH, game_height(test), "game_height");
	tear_down();
	delete_game(test);
	return result;
}

/**
 * @brief test the copy of the game
 * @return true if the copy is correct, false otherwise
 */
bool test_copy_game() { 
	bool result = true;
	set_up();
	game test = new_game_hr(NB_PIECES, pieces);

	piece * t_pieces = malloc(sizeof(struct piece_s)*game_nb_pieces(test));
	for(int i=0 ; i<game_nb_pieces(test) ; i++){
		t_pieces[i] = new_piece_rh(0,0,true,true);
	}
	game copy_test = new_game_hr(1, t_pieces);

	copy_game(test, copy_test);
	result = result && test_equality_game(test, copy_test, "copy_game");
	delete_pieces(game_nb_pieces(test), t_pieces);
	tear_down();
	delete_game(test);
	delete_game(copy_test);
	return result;
}

/**
 * @brief Test the number of pieces in the game
 * @return true if the number of pieces is ok, false otherwise
 */
bool test_game_nb_pieces() {   
	bool result = true;
	set_up();
	game test = new_game_hr(NB_PIECES, pieces);
	result = result && test_equality_int(NB_PIECES, game_nb_pieces(test), "game_nb_piece");
	tear_down();
	delete_game(test);
	return result;
}

/**
 * @brief test if the game is over
 * @return true if the game is over, false otherwise
 */
bool test_game_over_rh() {  
	bool result = true;
	
	set_up();
	game test = new_game_hr(NB_PIECES, pieces);
	result = result && test_equality_bool(false, game_over_hr(test), "game_over_hr not end");
	delete_game(test);
	tear_down();
	
	set_up_win();
	game test2 = new_game_hr(1, pieces);

	result = result && test_equality_bool(true, game_over_hr(test2), "game_over_hr end");
	delete_game(test2);
	tear_down_win();

	return result;
}

/**
 * @brief test the number of movements
 * @return true if the number is OK, false otherwise
 */
bool test_game_nb_moves(){ 
	bool result = true;

	set_up();
	game test = new_game_hr(NB_PIECES, pieces);
	result = result && test_equality_int(0, game_nb_moves(test), "game_nb_moves");
	play_move(test, 0, LEFT, 2);
	result = result && test_equality_int(0, game_nb_moves(test), "game_nb_moves");
	delete_game(test);
	tear_down();

	return result;
}

/**
 * @brief test if there is a piece present
 * @return true if there is one, false otherwise
 */

bool test_game_square_piece_rh() { 
	bool result = true;
	set_up();
	game test = new_game_hr(NB_PIECES, pieces);
	result = result && test_equality_int(2, game_square_piece(test, 4, 1) , "game_square_piece present");
	result = result && test_equality_int(-1, game_square_piece(test, 0, 0), "game_square_piece not present");
	delete_game(test);
	tear_down();
	return result; 
} 

bool test_play_move_rh() {
	bool result = true;

	set_up();
	game test = new_game_hr(NB_PIECES, pieces);

	// test de mouvements qui ne sont pas possible
	for (int i = 1; i < HEIGHT_RH; i++) {
		result = result && test_equality_bool(false, play_move(test, 3, UP, i), "play_move UP non autorise");
		result = result && test_equality_bool(false, play_move(test, 1, DOWN, i), "play_move DOWN non autorise");
		result = result && test_equality_bool(false, play_move(test, 2, RIGHT, i), "play_move RIGHT non autorise");
		result = result && test_equality_bool(false, play_move(test, 4, LEFT, i), "play_move LEFT non autorise");
		result = result && test_equality_bool(false, play_move(test, 5, UP, i), "play_move UP collision non autorise");
		result = result && test_equality_bool(false, play_move(test, 6, DOWN, i), "play_move DOWN collision non autorise");
		result = result && test_equality_bool(false, play_move(test, 0, RIGHT, i), "play_move RIGHT collision non autorise");
		result = result && test_equality_bool(false, play_move(test, 2, LEFT, i), "play_move LEFT collision non autorise");
		
	}
	// test de mouvement qui sont possibles d'une seule case
	result = result && test_equality_bool(true, play_move(test, 1, UP, 1), "play_move UP");
	result = result && test_equality_bool(true, play_move(test, 5, DOWN, 1), "play_move DOWN");
	result = result && test_equality_bool(true, play_move(test, 4, RIGHT, 1), "play_move RIGHT");
	result = result && test_equality_bool(true, play_move(test, 0, LEFT, 1), "play_move LEFT");


	delete_game(test);
	tear_down();
	return result;
}

/**
 * @brief main test
 * @return exit_success
 */
int main(){
	bool result = true;
	result = result && test_equality_bool(true, test_new_game_rh(), "new_game_rh");
	result = result && test_equality_bool(true, test_copy_game(), "copy_game");
	result = result && test_equality_bool(true, test_game_nb_pieces(), "game_nb_pieces");
	result = result && test_equality_bool(true, test_game_over_rh(), "game_over_rh");
	result = result && test_equality_bool(true, test_game_nb_moves(), "game_nb_moves");
	result = result && test_equality_bool(true, test_game_square_piece_rh(), "game_square_piece_rh");
	result = result && test_equality_bool(true, test_play_move_rh(), "play_move_rh");
	if (!result) {
		printf("Test_game KO!\n");
		return EXIT_FAILURE;
	}
	printf("Test Game OK!\n");
	return EXIT_SUCCESS;
}
