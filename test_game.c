#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "piece.h" 

#define NB_PIECES 4

bool test_game_piece(cgame gtest);

bool test_equality_int(int expected, int value, char * msg) {   
	if (expected != value)
		fprintf(stderr, "%s expected int is not equal to value int\n", msg);
	return expected == value;
}

/**
* @brief test if value is equal to expected; if not, displays an error message containing msg to standard error output
*/

bool test_equality_bool(bool expected, bool value, char * msg) {   
	if (expected != value)
		fprintf(stderr, "%s expected boolean is not equal to value boolean\n", msg);
	return expected == value;
}


/*
* @brief test if value is equal to expected ; if not program abort
* @return true if expected == value
*
*/

bool test_equality_piece(cpiece expected, cpiece value, char *msg) {   
	if ((get_x(expected) != get_x(value)) || (get_y(expected) != get_y(value)) || (is_horizontal(expected) != is_horizontal(value)) || (is_small(expected) != is_small(value))) {
		fprintf(stderr, "%s expected piece is not equal to value piece\n", msg);
		return false;
	}
	return true;
}

/*
* @brief same test as test_equality_piece
*
*/

bool test_equality_game(cgame expected, cgame value, char * msg) {   
	bool result = true;
	for (int i = 0; i < NB_PIECES; i++) {
		// printf("%d\n",i); A quoi ça sert ?
		result = result && test_equality_piece(game_piece(expected, i), game_piece(value, i) , msg);
	}
	if ( !result )
		fprintf(stderr, "%s expected game is not equal to value game\n", msg);
	return result;
}


piece pieces[NB_PIECES];

void set_up() {   
	pieces[0] = new_piece_rh(3, 3, true, true);
	pieces[1] = new_piece_rh(3, 0, true, false);
	pieces[2] = new_piece_rh(4, 1, true, true);
	pieces[3] = new_piece_rh(5, 3, false, false);
}
void tear_down() {   
	for (int i = 0; i < NB_PIECES; i++)
		delete_piece(pieces[i]);
}


void set_up_win() {  
	pieces[0] = new_piece_rh(4, 3, true, true);
}

void tear_down_win() {  
	delete_piece(pieces[0]);
}

bool test_new_game_hr() {
	bool result = true;
	set_up();
	game test = new_game_hr(NB_PIECES , pieces);
	result = result && test_game_piece(test);
	result = result && test_equality_int(NB_PIECES, game_nb_pieces(test), "game_nb_pieces");
	result = result && test_equality_int(0, game_nb_moves(test) , "game_nb_moves");
	tear_down();
	delete_game(test);
	return result;
}

//cette fonction n'est pas au point.
bool test_copy_game() { //KO
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

bool test_game_nb_pieces() {   
	bool result = true;
	set_up();
	game test = new_game_hr(NB_PIECES, pieces);
	result = result && test_equality_int(NB_PIECES, game_nb_pieces(test), "game_nb_piece");
	tear_down();
	delete_game(test);
	return result;
}

bool test_game_piece(cgame gtest) {
	bool result = true;
	for (int i = 0; i < NB_PIECES; i ++)
		result = result && test_equality_piece(pieces[i], game_piece(gtest, i), "game_piece");
	return result;
}

bool test_game_over_hr() {  
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

int main(){
	bool result = true;
	result = result && test_equality_bool(true, test_new_game_hr(), "new_game");
	result = result && test_equality_bool(true, test_copy_game(), "copy_game");
	result = result && test_equality_bool(true, test_game_nb_pieces(), "game_nb_pieces");
	result = result && test_equality_bool(true, test_game_over_hr(), "game_over");
	if (!result) {
		printf("Test_game KO!\n");
		return EXIT_FAILURE;
	}
	printf("Test Game OK!\n");
	return EXIT_SUCCESS;
}