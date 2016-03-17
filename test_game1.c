#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "game1.h"
#include "piece.h"
#include "piece1.h"
#include "test_general.h"

#define NB_PIECES 7
#define HEIGHT_HR 6
#define WIDTH_HR 6

bool test_game_piece(cgame gtest);

/**
 * @brief test if value is equal to expected ; if not program abort
 * @return true if expected == value
 */

bool test_equality_piece(cpiece expected, cpiece value, char *msg) {   
	if ((get_x(expected) != get_x(value)) || (get_y(expected) != get_y(value)) || (is_horizontal(expected) != is_horizontal(value)) || (is_small(expected) != is_small(value))) {
		fprintf(stderr, "%s expected piece is not equal to value piece\n", msg);
		return false;
	}
	return true;
}

/**
 * @brief same test as test_equality_piece
 */

bool test_equality_game(cgame expected, cgame value, char * msg) {   
	bool result = true;
	for (int i = 0; i < NB_PIECES; i++) {
		result = result && test_equality_piece(game_piece(expected, i), game_piece(value, i) , msg);
	}
	if ( !result )
		fprintf(stderr, "%s expected game is not equal to value game\n", msg);
	return result;
}

piece pieces[NB_PIECES];

/**
 * @brief Initialisation de 4 pieces.
 */
void set_up() {
	pieces[0] = new_piece_rh(3, 3, true, true);
	pieces[1] = new_piece_rh(3, 0, true, false);
	pieces[2] = new_piece_rh(4, 1, true, true);
	pieces[3] = new_piece_rh(5, 3, false, false);
	pieces[4] = new_piece_rh(0, 4, true, true);
	pieces[5] = new_piece_rh(1, 2, true, false);
	pieces[6] = new_piece_rh(3, 4, true, false);
}

/* configue de test
...6.3
44.6.3
.5.003
.5....
...122
...1..
*/

/**
 * @brief Suppression des pieces.
 */
void tear_down() {   
	for (int i = 0; i < NB_PIECES; i++)
		delete_piece(pieces[i]);
}

/**
 * @brief Creation de la piece zero dans la position de victoire.
 */
void set_up_win() {  
	pieces[0] = new_piece_rh(4, 3, true, true);
}

/**
 * @brief Suppression de la piece.
 */

void tear_down_win() {  
	delete_piece(pieces[0]);
}

/**
 * @brief Teste de l'initialisation du jeu.
 * @return vrai si l'initialisation est correcte, faux sinon.
 */
bool test_new_game_hr() { 
	bool result = true;
	set_up();
	game test = new_game_hr(NB_PIECES , pieces);
	result = result && test_game_piece(test);
	result = result && test_equality_int(NB_PIECES, game_nb_pieces(test), "game_nb_pieces");
	result = result && test_equality_int(0, game_nb_moves(test) , "game_nb_moves");
	result = result && test_equality_int(WIDTH_HR, game_width(test), "game_width");
	result = result && test_equality_int(HEIGHT_HR, game_height(test), "game_height");
	tear_down();
	delete_game(test);
	return result;
}

/**
 * @brief Teste de la copie du jeu.
 * @return vrai si la copie est correcte, faux sinon.
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
 * @brief Teste le nombre de pieces du jeu.
 * @return vrai si le nombre de pieces est correct, faux sinon.
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
 * @brief Teste les toutes pieces du jeu.
 * @return vrai si les pieces sont correctes, faux sinon.
 */
bool test_game_piece(cgame gtest) {
	bool result = true;
	for (int i = 0; i < NB_PIECES; i ++)
		result = result && test_equality_piece(pieces[i], game_piece(gtest, i), "game_piece");
	return result;
}

/**
 * @brief Test la condition de victoire.
 */
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

/**
 * @brief Teste le nombre de mouvements.
 * @return vrai si le nombre de mouvements est correct, faux sinon.
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

bool test_game_square_piece_hr() { 
	bool result = true;
	set_up();
	game test = new_game_hr(NB_PIECES, pieces);
	result = result && test_equality_int(2, game_square_piece(test, 4, 1) , "game_square_piece present");
	result = result && test_equality_int(-1, game_square_piece(test, 0, 0), "game_square_piece not present");
	delete_game(test);
	tear_down();
	return result; 
} 

bool test_play_move_hr() {
	bool result = true;

	set_up();
	game test = new_game_hr(NB_PIECES, pieces);

	// test de mouvements qui ne sont pas possible
	for (int i = 1; i < HEIGHT_HR; i++) {
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


int main(){
	bool result = true;
	result = result && test_equality_bool(true, test_new_game_hr(), "new_game_hr");
	result = result && test_equality_bool(true, test_copy_game(), "copy_game");
	result = result && test_equality_bool(true, test_game_nb_pieces(), "game_nb_pieces");
	result = result && test_equality_bool(true, test_game_over_hr(), "game_over_hr");
	result = result && test_equality_bool(true, test_game_nb_moves(), "game_nb_moves");
	result = result && test_equality_bool(true, test_game_square_piece_hr(), "game_square_piece_hr");
	//result = result && test_equality_bool(true, test_game_over_ar(), "game_over_ar");
	//result = result && test_equality_bool(true, test_new_game(), "new_game_ar");
	result = result && test_equality_bool(true, test_play_move_hr(), "play_move_hr");
	if (!result) {
		printf("Test_game KO!\n");
		return EXIT_FAILURE;
	}
	printf("Test Game OK!\n");
	return EXIT_SUCCESS;
}