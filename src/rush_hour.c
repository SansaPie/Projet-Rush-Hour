#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "game.h"
#include "game1.h"
#include "piece.h"
#include "piece1.h"
#include "input.h"

/**
 * @brief moves the piece in the direction and the distance chosen.
 * @param piece_played index in the game of the piece we want to move.
 * @param distance number of cases we want to move the piece.
 */
void move_rh(game g, int piece_played, int distance){
	if(g==NULL || piece_played<0 || piece_played>=game_nb_pieces(g)){
		fprintf(stderr, "move_rh : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	if(distance>0){
		if(is_horizontal(game_piece(g, piece_played)))
			display_success_movement(g, piece_played, distance, RIGHT);
		else
			display_success_movement(g, piece_played, distance, UP);
	}else{
		if(is_horizontal(game_piece(g, piece_played)))
			display_success_movement(g, piece_played, distance, LEFT);
		else
			display_success_movement(g, piece_played, distance, DOWN);
	}
}

/**
 * @brief choice of the rush hour config.
 * @param pieces_test array of pieces which will be in the game.
 * @param n number of pieces in the game.
 * @param choice choice of the configuration by the user earlier in the program.
 */
game choice_config_rh(piece * pieces_test, int * n, int choice, char * answer, int size){
	if(pieces_test==NULL || n==NULL || answer==NULL || size<0){
		fprintf(stderr, "choice_config_rh : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	FILE *entree = NULL;
	switch(choice){
		case 0:;
			char * config_user = input_config_user(answer, size);
			entree = fopen(config_user, "r+");
			free(config_user);
			break;
		case 1:
			entree = fopen("../config/easy_rh_1.txt", "r+");
			break;
		case 2:
			entree = fopen("../config/easy_rh_2.txt", "r+");
			break;
		case 3:
			entree = fopen("../config/normal_rh_1.txt", "r+");
			break;
		case 4:
			entree = fopen("../config/normal_rh_2.txt", "r+");
			break;
		case 5:
			entree = fopen("../config/difficult_rh_1.txt", "r+");
			break;
		case 6:
			entree = fopen("../config/difficult_rh_2.txt", "r+");
			break;
		default:
			printf("choice_config : choice invalide.\n");
			break;
	}
	if (entree == NULL) {
		fprintf(stderr, "Fichier non valide.\n");
		exit(EXIT_FAILURE);
	}
	pieces_test = lecture(pieces_test, n, entree);
	game g = new_game(6,6,*n, pieces_test); 
	/*
	 * the height and width are always the same for the rush hour game.
	 */
	fclose(entree);
	delete_pieces(*n, pieces_test);
	return g;
}

/**
 * @brief proceeding of a rush-hour game.
 */
void rush_hour(char * answer, int size, game g){
	if(g==NULL || answer==NULL || size<0){
		fprintf(stderr, "rush_hour : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	/**
	 * tests if the game is valid.
	 */
	if(!game_valid(g)){
		fprintf(stderr, "rush_hour : game invalid\n");
		exit(EXIT_FAILURE);
	}

	/**
	 * display the rules of the game.
	 */
	printf("Ce jeu a ete code par Lucas, Lisa et Clement. \n"
		"Le but de ce jeu est d'amener la voiture 0 toucher le cote droit du plateau.\n"
		"Vous ne pouvez bouger les pieces horizontales que de gauche a droite, "
		"et les verticales que de haut en bas. \n"
		"Un nombre negatif fera bouger une voiture horizontale a gauche, "
		"un nombre positif la fera bouger a droite.\n"
		"Un nombre negatif fera bouger une voiture verticale vers le bas, "
		"et un nombre positif la fera bouger vers le haut.\n"
		"Essayez de resoudre ce puzzle en un minimum de coups possible !\n\n");

	/** 
	 * while the game isn't over, asks the user what he wants to play.
	 */
	while(!game_over_hr(g)){
		display_game(g);
		int piece_played = input_piece_played(answer, size, g);
		printf("Vous avez choisi la piece %d. De combien de cases voulez-vous la bouger ?\n"
			, piece_played);
		int distance = input_distance(answer, size, g);
		move_rh(g, piece_played, distance);
	}

	display_game(g);
}