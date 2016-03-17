//////////////////////////////////////////////////////////// Rajout de ASSERT a faire ////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "game.h"
#include "game1.h"
#include "piece.h"
#include "piece1.h"
#include "math.h" // Vérifier si nécessaire

/**
 * @brief function allowing the reading of pieces features from an annexed file
 */
piece * lecture(piece * pieces_test, int * n, FILE * entree) {
	/* 
	 * var use for the lecture of the file
	 */

	int number_pieces;
	int c_x;	   // x-coor
	int c_y;	   // y-coor
	int m_x;	   // move_x
	int m_y;	   // move_y
	int w;		   // width
	int h;		   // height

	if( entree == NULL )
	{
		printf("error when opening the file\n");
		exit(EXIT_FAILURE);
	}  
	fscanf(entree, "%d", &number_pieces);
	pieces_test = allocation_piece_tab(number_pieces, "main"); 
	/* 
	 * creation of the tab
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
 * @brief Allocates a char matrix
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
 * @brief Deletes a char matrix
 */
void delete_char_matrix(char ** grid, int width){
	for(int i=0 ; i<width ; i++)
		free(grid[i]);
	free(grid);
}

/**
 * @brief function displaying game in terminal
 * 
 */
void display_game(cgame g) {
	/* 
	 * creation of a 2D tab, representing our game's board
	 */
	char ** grid = allocation_char_matrix(game_width(g), game_height(g)); 
	/* 
	 * initialisation of the tab with '.' 
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
	 * display the game's board
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
 * @brief test if the movement is possible, and if so, execute it
 * @param number_piece index in the game of the piece we want to move
 * @param distance : number of cases we want to move the piece
 * @param d direction of the move
 */

void display_success_movement(game g, int number_piece, int distance, dir d){
	if(play_move(g, number_piece, d, abs(distance))){
		printf("Vous avez bouge la piece %d de %d cases vers ", number_piece, abs(distance));
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
 * @brief move the piece in the direction and the distance chosen
 * @param number_piece index in the game of the piece we want to move
 * @param distance direction in which we want to move the piece
 */

void move_rh(game g, int number_piece, int distance)
{
	if(distance>0){
		if(is_horizontal(game_piece(g, number_piece)))
			display_success_movement(g, number_piece, distance, RIGHT);
		else
			display_success_movement(g, number_piece, distance, UP);
	}else{
		if(is_horizontal(game_piece(g, number_piece)))
			display_success_movement(g, number_piece, distance, LEFT);
		else
			display_success_movement(g, number_piece, distance, DOWN);
	}
}

/**
 * @brief ask the player to write a string
 * @param buffer tab of char in which we're going to stock the string written by the player
 * @param size width of the buffer
 * @return string written
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
	 * going back to the entrance flux
	 */
	return result;
}

/**
 * @brief choice of the rush hour config
 *
 */
game choice_config_rh(piece * pieces_test, int * n, int choice)
{
	FILE *entree = NULL;
	switch(choice){
		case 1:
			entree = fopen("config/easy_rh_1.txt", "r+");
			break;
		case 2:
			entree = fopen("config/easy_rh_2.txt", "r+");
			break;
		case 3:
			entree = fopen("config/normal_rh_1.txt", "r+");
			break;
		case 4:
			entree = fopen("config/normal_rh_2.txt", "r+");
			break;
		case 5:
			entree = fopen("config/difficult_rh_1.txt", "r+");
			break;
		case 6:
			entree = fopen("config/difficult_rh_2.txt", "r+");
			break;
		default:
			printf("choice_config : choice invalid\n");
			break;
	}
	pieces_test = lecture(pieces_test, n, entree);
	game g = new_game(6,6,*n, pieces_test); 
	/*
	 * the height and width are always the same for the rush hour game
	 */
	fclose(entree);
	delete_pieces(*n, pieces_test);
	return g;
}

void rush_hour(char * answer, int size, game g){
	/* 
	 * test if the position is OK
	 */
	if(!game_valid(g)){
		fprintf(stderr, "rush_hour : game invalid\n");
		exit(EXIT_FAILURE);
	}

	/* 
	 * display the rules
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

	while(!game_over_hr(g)){ 
	/* 
	 * while the game is not over, we're asking the player what he wants to play
	 */
		display_game(g);
		int number_piece = -1;
		bool condition = true;
		while(condition){
			printf("Quelle piece voulez-vous jouer ? Rentrez son numero.\n");
			number_piece = atoi(scan(answer, size));
			condition = (number_piece<0 || number_piece>game_nb_pieces(g));
			if(condition)
				printf("Veuillez rentrer un numero de piece existant. (0 a %d)\n", game_nb_pieces(g));
		}
		printf("Vous avez choisi la piece %d. De combien de cases voulez-vous la bouger ?\n"
			, number_piece);
		int distance = game_height(g);
		condition = true;
		while(condition){
			distance = atoi(scan(answer, size));
			condition = (abs(distance)>=(game_height(g)-1) || abs(distance)>=(game_width(g)-1));
			if(condition)
				printf("Veuillez rentrer une distance valide.\n");
		}
		move_rh(g, number_piece, distance);
	}

	display_game(g);
	printf("\nFelicitations : vous avez battu le jeu en %d coups !\n", g->moves);
	
	delete_game(g);
}

game choice_config_ar(piece * pieces_test, int * n, int choice){
	FILE *entree = NULL;
	switch(choice){
		case 1:
			entree = fopen("config/easy_ar_1.txt", "r+");
			break;
		case 2:
			entree = fopen("config/normal_ar_1.txt", "r+");
			break;
		case 3:
			entree = fopen("config/difficult_ar_1.txt", "r+");
			break;
		case 4:
			entree = fopen("config/difficult_ar_2.txt", "r+");
			break;
	}
	pieces_test = lecture(pieces_test, n, entree);
	game g = new_game(4,5,*n, pieces_test); 
	/*
	 * the height and the width are always the same for this game
	 */
	fclose(entree);
	delete_pieces(*n, pieces_test);
	return g;
}

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

void ane_rouge(char * answer, int size, game g){
	/* 
	 * test if the position of the pieces are OK
	 */
	if(!game_valid(g)){
		fprintf(stderr, "ane_rouge : game invalid\n");
		exit(EXIT_FAILURE);
	}

	/* 
	 * display the rules
	 */
	printf("Ce jeu a ete code par Lucas, Lisa et Clement. \n"
		"Le but de ce jeu est d'amener la piece 0 en bas du plateau.\n"
		"Vous pouvez bouger les pieces horizontalement et verticalement.\n"
		"Essayez de resoudre ce puzzle en un minimum de coups possible !\n\n");

	while(!game_over_ar(g)){ 
	/* 
	 * while the game isn't over, we ask the player what he wants to play
	 */
		display_game(g);
		int number_piece = -1;
		bool condition = true;
		while(condition){
			printf("Quelle piece voulez-vous jouer ? Rentrez son numero.\n");
			number_piece = atoi(scan(answer, size));
			condition = (number_piece<0 || number_piece>game_nb_pieces(g));
			if(condition)
				printf("Veuillez rentrer un numero de piece existant. (0 a %d)\n", game_nb_pieces(g)-1);
		}

		printf("Vous avez choisi la piece %d. Dans quelle direction voulez-vous la bouger ?\n(UP, DOWN, RIGHT, LEFT)\n"
			, number_piece);
		char * s_direction = scan(answer, size);
		dir direction = input_direction(s_direction, size);

		printf("Et enfin de combien de cases va-t-elle se mouvoir ?\n");
		int distance = game_height(g);
		condition = true;
		while(condition){
			distance = atoi(scan(answer, size));
			condition = (abs(distance)>=game_height(g) || abs(distance)>=game_width(g));
			if(condition)
				printf("Veuillez rentrer une distance valide.\n");
		}
		display_success_movement(g, number_piece, distance, direction);
	}

	display_game(g);
	printf("\nFelicitations : vous avez battu le jeu en %d coups !\n", g->moves);
	
	delete_game(g);
}


int main(){
	int size = 30;
	int n = 0;
	piece * pieces_test = NULL;

	char * answer = malloc(sizeof(char)*size);
	printf("A quel jeu souhaitez-vous jouer ?\n1. Rush-hour\n2. Ane rouge\n");

	int choice = -1;
	bool condition = true;
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
			"\nEntrez le numero de la configuration que vous souhaitez utiliser.\n");
		choice = 0;
		condition = true;
		while(condition){
			choice = atoi(scan(answer, size));
			condition = (choice<1 || choice>6);
			if(condition)
				printf("Veuillez selectionner un numero de configuration correcte.\n");
		}
		game g = choice_config_rh(pieces_test, &n, choice);
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
		game g = choice_config_ar(pieces_test, &n, choice);
		ane_rouge(answer, size, g);
	}
	free(answer);
	return EXIT_SUCCESS;
}
