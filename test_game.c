#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "test_piece1.c"
#include "game.h"
#include "piece.h" // Si on inclut les .h, pas besoin d'inclure les .c

#define NB_PIECES 4

/*
* @brief test if value is equal to expected ; if not program abort
* @return true if expected == value
*
*/

bool test_equality_piece(cpiece expected, cpiece value, char *msg) {
	if ( expected != value )	
		exit(EXIT_FAILURE);
	return expected == value;
}

/*
* @brief same test as test_equality_piece
*
*/

bool test_equality_game(cgame expected, cgame value, char * msg) {
	bool result = true;
	for (int i = 0; i < NB_PIECES; i++) {
		result = result && test_equality_piece(game_piece(expected, i), game_piece(value, i) , msg);
	}
	if ( !result )
		exit(EXIT_FAILURE);
	return result;
}


piece pieces[NB_PIECES];

void set_up() {
	pieces[0] = new_piece_rh(3, 3, true, true);
	pieces[1] = new_piece_rh(3, 0, true, false);
	pieces[2] = new_piece_rh(4, 1, true, true);
	pieces[3] = new_piece_rh(5, 3, false, false);
}

bool test_new_game_hr() {
	bool result = true;
	game test = new_game_hr(NB_PIECES , pieces);
	for (int i = 0; i < NB_PIECES; i++)
		result = result && test_equality_piece(pieces[i], game_piece(test, i), "game_piece");
	delete_game(test);
	return result;
}


bool test_copy_game() {
	bool result = true;
	game test = new_game_hr(NB_PIECES, pieces);
	game copy_test = NULL;
	copy_game(test, copy_test);
	result = result && test_equality_game(test, copy_test, "copy_game");
	delete_game(test);
	delete_game(copy_test);
	return result;
}

bool test_game_nb_pieces() {
	bool result = true;
	game test = new_game_hr(NB_PIECES, pieces);
	result = result && test_equality_int(NB_PIECES, game_nb_pieces(test), "game_nb_piece");
	return result;
}

bool test_game_piece() {
	bool result = true;
	/* attention ne pas refaire le meme test que pour 
	* la fonction de test new_game_hr
	*/
	}
}

bool test_

int main(){
	
}