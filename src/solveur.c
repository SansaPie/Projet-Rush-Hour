#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "piece.h"
#include "game1.h"
#include "piece1.h"
#include <time.h>
#include "solveur.h"
#include "test_general.h" // pour les tests seulements	

//#define DISTANCE 1

//////////////////////////////////////////////////////////
void pieces_movable(cgame g, int* tabX, int taille) {
	int cptX = 1;
	for (int j = 0; j < game_nb_pieces(g); j++) {
		for (dir d = UP; d <= RIGHT; d++) {
			if (can_move_piece(g, j, d, DISTANCE)) {
				*(tabX+cptX) = j;
				cptX++;
				break;
			}
		}
	}
	(*tabX) = cptX; // taille... /!\.
}

bool can_move_piece(cgame g, int piece_num ,dir d,int distance){
	piece * t_pieces = NULL;
	t_pieces = allocation_piece_tab(1, "play_move");
	t_pieces[0] = new_piece_rh(0, 0, true, true);
	game gTmp = new_game(game_width(g), game_height(g), 1, t_pieces);
	copy_game(g, gTmp);

	piece piece_moved = gTmp->pieces[piece_num];

	for (int i = 0; i < distance; i++) {
		switch (d) {
			case RIGHT:
				if (can_move_x(piece_moved)) {
					piece_moved->x += distance;
				} else {
					delete_game(gTmp);
					delete_pieces(1, t_pieces);
					return false;
				}
				break;
			case LEFT:
				if (can_move_x(piece_moved)){
					piece_moved->x -= distance;
				} else {
					delete_game(gTmp);
					delete_pieces(1, t_pieces);
					return false;
				}
				break;
			case UP:
				if (can_move_y(piece_moved)){
					piece_moved->y += distance;
				} else {
					delete_game(gTmp);
					delete_pieces(1, t_pieces);
					return false;
				}
				break;
			case DOWN:
				if (can_move_y(piece_moved)){
					piece_moved->y -= distance;
				} else {
					delete_game(gTmp);
					delete_pieces(1, t_pieces);
					return false;
				}
				break;
		}
		if (!game_valid(gTmp)) {
			delete_game(gTmp);
			delete_pieces(1, t_pieces);
			return false;
		}
	}
	delete_game(gTmp);
	delete_pieces(1, t_pieces);
	return true;
}

int random_number(int min, int max) {
	return rand() % (max - min) + min;
}

void solveur(game g) {
	srand(time(NULL));
	int *tabX = malloc(sizeof(int)*NB_PIECES);
	int nb_random_c = -1;

	//display_game(g);
	while (!game_over_hr(g)) {
		pieces_movable(g, tabX, NB_PIECES);
		int nb_randomX = random_number(1, (*tabX));
		int tuileX = *(tabX + nb_randomX);

		if (can_move_x(game_piece(g,tuileX))) {
			nb_random_c = random_number(1, 4);
			if (nb_random_c == 2) { nb_random_c++; }
			if (play_move(g, tuileX, nb_random_c, DISTANCE)) { printf("vertical %d\n", nb_random_c); }
		}
		else {
			nb_random_c = random_number(0, 3);
			if (nb_random_c == 1) { nb_random_c++; }
			if (play_move(g, tuileX, nb_random_c, DISTANCE)) { printf("horizontal %d\n", nb_random_c); }
		}
		printf("c : %d\n", nb_random_c);
		//display_game(g);
	}
	printf("%d\n", g->moves);
	free(tabX);

}

/*

int main(void) {
	int *tabX = malloc(sizeof(int)*NB_PIECES);
	set_up();
	
	//game g = new_game_hr(NB_PIECES, pieces);
	game g = new_game()
	display_game(g);
	solveur(g);
	//pieces_movable(g, tabX, NB_PIECES);
	//for (int i = 0; i < *(tabX); i++)
	//	printf("%d\n", *(tabX + i));
	tear_down();
	free(tabX);

}*/


void solveurV2(game g) {
	int pieceNumber = -1;
	while (!game_over_hr(g)) {
		// test si la piece 0 peut bouger en direction de la sortie.
		while (game_square_piece(g,get_x(game_piece(g, 0)), get_y(game_piece(g,0)) + 1 ) != -1) {
			play_move(g, 0, RIGHT, DISTANCE);

		}
	}
}