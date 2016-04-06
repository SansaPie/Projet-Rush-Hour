#include <stdio.h>
#include <stdlib.h>
#include "test_general.h"


bool test_equality_int(int expected, int value, char * msg) {
	if (expected != value)
		fprintf(stderr, "ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
	return expected == value;
}

bool test_equality_bool(bool expected, bool value, char * msg) {
	if (expected != value)
		fprintf(stderr, "ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
	return expected == value;
}

bool test_equality_piece(cpiece expected, cpiece value, char *msg) {
	if ((get_x(expected) != get_x(value)) || (get_y(expected) != get_y(value)) || 
		(is_horizontal(expected) != is_horizontal(value)) || 
		(is_small(expected) != is_small(value))) {
		fprintf(stderr, "%s expected piece is not equal to value piece\n", msg);
		return false;
	}
	return true;
}

bool test_equality_game(cgame expected, cgame value, char * msg) {
	bool result = true;
	for (int i = 0; i < NB_PIECES; i++) {
		result = result && test_equality_piece(game_piece(expected, i), game_piece(value, i), msg);
	}
	if (!result)
		fprintf(stderr, "%s expected game is not equal to value game\n", msg);
	return result;
}

bool test_game_piece(cgame gtest) {
	bool result = true;
	for (int i = 0; i < NB_PIECES; i++)
		result = result && test_equality_piece(pieces[i], game_piece(gtest, i), "game_piece");
	return result;
}

/* configue de test
...6.3
44.6.3
.5.003
.5....
...122
...1..
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

void tear_down() {
	for (int i = 0; i < NB_PIECES; i++)
		delete_piece(pieces[i]);
}