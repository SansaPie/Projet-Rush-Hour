#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "game.h"
#include "game1.h"
#include "piece.h"
#include "piece1.h"
#include <string.h>

/**
 * @brief function allowing the reading of pieces features from an annexed file.
 */
piece * lecture(piece * pieces_test, int * n, FILE * entree) {
	
	/* 
	 * var used for the lecture of the file.
	 */
	int number_pieces;
	int c_x;	   // x-coor.
	int c_y;	   // y-coor.
	int m_x;	   // move_x.
	int m_y;	   // move_y.
	int w;		   // width.
	int h;		   // height.

	if(entree == NULL){
		printf("error when opening the file\n");
		exit(EXIT_FAILURE);
	}  
	fscanf(entree, "%d", &number_pieces);
	pieces_test = allocation_piece_tab(number_pieces, "main"); 
	/* 
	 * creation of the tab.
	 */
	for(int i=0; i<number_pieces; i++)
	{
		fscanf(entree, "%d %d %d %d %d %d", &c_x, &c_y, &m_x, &m_y, &w, &h);
		pieces_test[i] = new_piece(c_x, c_y, w, h, m_x, m_y);
	}
	*n = number_pieces;
	return pieces_test;
}

/**
 * @brief Allocates a char matrix.
 */
char ** allocation_char_matrix(int width, int height){
	char ** grid = malloc(sizeof(char*)*width);
	if(grid==NULL){
		fprintf(stderr, "allocation_char_matrix : grid null\n");
		exit(EXIT_FAILURE);
	}
	for(int i=0 ; i<width ; i++){
		grid[i] = malloc(sizeof(char)*height);
		if(grid[i]==NULL){
			fprintf(stderr, "allocation_char_matrix : grid[%d] null\n", i);
			exit(EXIT_FAILURE);
		}
	}
	return grid;
}

/**
 * @brief Deletes a char matrix.
 */
void delete_char_matrix(char ** grid, int width){
	for(int i=0 ; i<width ; i++)
		free(grid[i]);
	free(grid);
}

/**
 * @brief function displaying game in terminal.
 * 
 */
void display_game(cgame g) {
	/* 
	 * creation of a char matrix representing our game's board.
	 */
	char ** grid = allocation_char_matrix(game_width(g), game_height(g)); 
	/* 
	 * initialisation of the tab with '.'.
	 */
	for (int i = 0; i < game_width(g); i++) {
		for (int j = 0; j < game_height(g); j++) {
			grid[i][j] ='.';
		}
	}
	for (int i = 0; i < game_nb_pieces(g); i++){

		int xCoor = get_x(game_piece(g,i));
		int yCoor = get_y(game_piece(g,i));

		for(int x=xCoor ; x<xCoor+get_width(game_piece(g, i)) ; x++){
			for(int y=yCoor ; y<yCoor+get_height(game_piece(g, i)) ; y++){
				grid[x][y]=i+'0';
			}
		}
	}
	
	/* 
	 * display the game's board.
	 */
	for (int y = game_height(g)-1; y>=0; y--) {
		for (int x = 0; x<game_width(g); x++) {
			printf("%c ", grid[x][y]);
		}
		printf("\n");
	}
	printf("\n");
	delete_char_matrix(grid, game_width(g));
}

/**
 * @brief tests if the movement is possible, and if so, execute it.
 * @param piece_played index in the game of the piece we want to move.
 * @param distance : number of cases we want to move the piece.
 * @param d direction of the move.
 */
void display_success_movement(game g, int piece_played, int distance, dir d){
	if(play_move(g, piece_played, d, abs(distance))){
		printf("Vous avez bouge la piece %d de %d cases vers ", piece_played, abs(distance));
		if(d==RIGHT)
			printf("la droite.\n\n");
		else if(d==LEFT)
			printf("la gauche.\n\n");
		else if(d==UP)
			printf("le haut.\n\n");
		else
			printf("le bas.\n\n");
	}else
		printf("Mouvement impossible.\n");
}

/**
 * @brief moves the piece in the direction and the distance chosen.
 * @param piece_played index in the game of the piece we want to move.
 * @param distance number of cases we want to move the piece.
 */
void move_rh(game g, int piece_played, int distance){
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
 * @brief asks the player to write a string.
 * @param buffer tab of char in which the string written by the player is stocked.
 * @param size width of the buffer.
 * @return string written.
 */
char * scan(char * buffer , int size) {
	char * result = fgets(buffer, size, stdin);
	if ( result != NULL) {
		char * lresult = strchr(buffer, '\n');
		if (lresult != NULL)
			*lresult = '\0';
	}
	rewind(stdin); 
	/*
	 * going back to the entrance flux.
	 */
	return result;
}

char * input_config_user(char * answer, int size){
	char * config_user = malloc(strlen("../config/"));
	strcat(config_user, "../config/");	
	printf("Entrez le nom complet de votre fichier y compris son extension.\n");
	answer = scan(answer, size);
	config_user = realloc(config_user, strlen(config_user)+strlen(answer));
	strcat(config_user, answer);
	return config_user;
}

/**
 * @brief choice of the rush hour config.
 * @param pieces_test array of pieces which will be in the game.
 * @param n number of pieces in the game.
 * @param choice choice of the configuration by the user earlier in the program.
 */
game choice_config_rh(piece * pieces_test, int * n, int choice, char * answer, int size){
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
			printf("choice_config : choice invalid\n");
			break;
	}
	if (entree == NULL) {
		fprintf(stderr, "Fichier not valid:");
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
 * @brief same as choice_config_rh but with a game of ane_rouge.
 */
game choice_config_ar(piece * pieces_test, int * n, int choice, char * answer, int size){
	FILE *entree = NULL;
	switch(choice){
	case 0:;
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
		fprintf(stderr, "Fichier not valid:");
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
 * @brief asks the user for which piece he wants to play.
 */
int input_piece_played(char * answer, int size, cgame g){
	int piece_played = -1;
	bool condition = true;
	while(condition){
		printf("Quelle piece voulez-vous jouer ? Rentrez son numero.\n");
		piece_played = atoi(scan(answer, size));
		condition = (piece_played<0 || piece_played>=game_nb_pieces(g));
		if(condition)
			printf("Veuillez rentrer un numero de piece existant. (0 a %d)\n", game_nb_pieces(g)-1);
	}
	return piece_played;
}

/**
 * @brief asks the user the distance he wants to move the piece chosen.
 */
int input_distance(char * answer, int size, cgame g){
	int distance = game_height(g);
	bool condition = true;
	while(condition){
		distance = atoi(scan(answer, size));
		condition = (abs(distance)>(game_height(g)-1) || abs(distance)>(game_width(g)-1));
		if(condition)
			printf("Veuillez rentrer une distance valide.\n");
	}
	return distance;
}

/**
 * @brief asks the user in which direction the piece is to be moved.
 */
dir input_direction(char * direction, int size){
	while(1){
		if(!strcmp(direction, "RIGHT"))
			return RIGHT;
		else if(!strcmp(direction, "LEFT"))
			return LEFT;
		else if(!strcmp(direction, "UP"))
			return UP;
		else if(!strcmp(direction, "DOWN"))
			return DOWN;
		else{
			printf("Direction invalide. Veuillez entrer UP, DOWN, RIGHT ou LEFT.\n");
			direction = scan(direction, size);
		}
	}
}

/**
 * @brief proceeding of a rush-hour game.
 */
void rush_hour(char * answer, int size, game g){
	/**
	 * tests if the game is valid.
	 */
	if(!game_valid(g)){
		fprintf(stderr, "rush_hour : game invalid\n");
		exit(EXIT_FAILURE);
	}

	/**
	 *display the rules of the game.
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

/**
 * @brief same as rush_hour but for an ane_rouge game.
 */
void ane_rouge(char * answer, int size, game g){
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

int main(){
	int size = 30;
	int n = 0;
	piece * pieces_test = NULL;
	char * answer = malloc(sizeof(char)*size);
	char playing_game = 'O';

	/**
	 * loop allowing the user to play as many game as he wants.
	 */
	while(playing_game=='O' || playing_game=='o'){
		int choice = -1;
		bool condition = true;
		game g = NULL;

		printf("\nA quel jeu souhaitez-vous jouer ?\n1. Rush-hour\n2. Ane rouge\n");
		while(condition){
			choice = atoi(scan(answer, size));
			condition = (choice!=1 && choice!=2);
			if(condition)
				printf("Veuillez selectionner un numero de jeu correct.\n");
		}
		if(choice == 1){
			printf("La liste des configurations disponibles est : \n"
				"	1. easy_rh_1.txt\n"
				"	2. easy_rh_2.txt\n"
				"	3. normal_rh_1.txt \n"
				" 	4. normal_rh_2.txt \n"
				" 	5. difficult_rh_1.txt \n"
				"	6. difficult_rh_2.txt \n"
				"\nEntrez le numero de la configuration que vous souhaitez utiliser.\n"
				"Si vous souhaitez utiliser votre propre configuration, tapez 0.\n"
				"Veillez avant cela a bien avoir placer votre .txt dans le dossier config du jeu.\n");
			choice = -1;
			condition = true;
			while(condition){
				choice = atoi(scan(answer, size));
				condition = (choice<0 || choice>6);
				if(condition)
					printf("Veuillez selectionner un numero de configuration correcte.\n");
			}
			g = choice_config_rh(pieces_test, &n, choice, answer, size); // initialization of the game.
			rush_hour(answer, size, g);
		}
		else{
			printf("La liste des configurations disponibles est : \n"
				"	1. easy_ar_1.txt\n"
				"	2. normal_ar_1.txt\n"
				"	3. difficult_ar_1.txt\n"
				"	4. difficult_ar_2.txt\n"
				"\nEntrez le numero de la configuration que vous souhaitez utiliser.\n");
			choice = 0;
			condition = true;
			while(condition){
				choice = atoi(scan(answer, size));
				condition = (choice<1 || choice>4);
				if(condition)
					printf("Veuillez selectionner un numero de configuration correcte.\n");
			}
			g = choice_config_ar(pieces_test, &n, choice, answer, size); // initialization of the game.
			ane_rouge(answer, size, g);
		}
		printf("\nFelicitations : vous avez battu le jeu en %d coups !\n", g->moves);
		delete_game(g);

		printf("\nSouhaitez-vous rejouer ? (O/N)\n");
		condition = true;
		while(condition){
			answer = scan(answer, size);
			playing_game = answer[0];
			condition = (playing_game!='O' && playing_game!='N' && playing_game!='o' && playing_game!='n');
			if(condition)
				printf("Veuillez entrer la lettre O ou N.\n");
		}
	}
	free(answer);
	return EXIT_SUCCESS;
}