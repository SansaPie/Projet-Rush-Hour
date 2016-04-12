#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "game.h"
#include "game1.h"
#include "piece.h"
#include "piece1.h"

/**
 * @brief Tests if a game of ane_rouge is over.
 */
bool game_over_ar(cgame g) {
	if (g == NULL) {
		fprintf(stderr, "game_over_ar : g invalide\n");
		exit(EXIT_FAILURE);
	}
	if (get_x(game_piece(g, 0)) == 1 && get_y(game_piece(g, 0)) == 0)
		return true;
	return false;
}

/**
 * @brief same as choice_config_rh but with a game of ane_rouge.
 */
game choice_config_ar(piece * pieces_test, int * n, int choice, char * answer, int size){
	if(pieces_test==NULL || n==NULL || answer==NULL || size<0){
		fprintf(stderr, "choice_config_ar : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	FILE *entree = NULL;
	switch(choice){
	case 0:; // This ; stands for the prevention of a bug, it's not a typo
			char * config_user = input_config_user(answer, size);
			entree = fopen(config_user, "r+");
			free(config_user);
		case 1:
			entree = fopen("../config/easy_ar_1.txt", "r+");
			break;
		case 2:
			entree = fopen("../config/normal_ar_1.txt", "r+");
			break;
		case 3:
			entree = fopen("../config/difficult_ar_1.txt", "r+");
			break;
		case 4:
			entree = fopen("../config/difficult_ar_2.txt", "r+");
			break;
	}
	if (entree == NULL) {
		fprintf(stderr, "Fichier non valide.\n");
		exit(EXIT_FAILURE);
	}
	pieces_test = lecture(pieces_test, n, entree);
	game g = new_game(4,5,*n, pieces_test); 
	/*
	 * the height and the width are always the same for this game.
	 */
	fclose(entree);
	delete_pieces(*n, pieces_test);
	return g;
}

/**
 * @brief same as rush_hour but for an ane_rouge game.
 */
void ane_rouge(char * answer, int size, game g){
	if(g==NULL || answer==NULL || size<0){
		fprintf(stderr, "ane_rouge : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	/**
	 * tests if the game is valid.
	 */
	if(!game_valid(g)){
		fprintf(stderr, "ane_rouge : game invalid\n");
		exit(EXIT_FAILURE);
	}

	/**
	 * display the rules of the game.
	 */
	printf("Ce jeu a ete code par Lucas, Lisa et Clement. \n"
		"Le but de ce jeu est d'amener la piece 0 en bas du plateau.\n"
		"Vous pouvez bouger les pieces horizontalement et verticalement.\n"
		"Essayez de resoudre ce puzzle en un minimum de coups possible !\n\n");

	/**
	 * while the game isn't over, asks the user what he wants to play.
	 */
	while(!game_over_ar(g)){
		display_game(g);
		int piece_played = input_piece_played(answer, size, g);

		printf("Vous avez choisi la piece %d. Dans quelle direction voulez-vous la bouger ?\n(UP, DOWN, RIGHT, LEFT)\n"
			, piece_played);
		char * s_direction = scan(answer, size);
		dir direction = input_direction(s_direction, size);

		printf("Et enfin de combien de cases va-t-elle se mouvoir ?\n");
		int distance = input_distance(answer, size, g);
		display_success_movement(g, piece_played, distance, direction);
	}

	display_game(g);
}