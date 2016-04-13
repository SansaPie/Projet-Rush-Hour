#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "piece.h"
#include "game.h"
#include "game1.h"
#include "input.h"

/**
 * @brief function displaying game in terminal.
 * 
 */
void display_game(cgame g){
	if(g==NULL){
		fprintf(stderr, "display_game : g null.\n");
		exit(EXIT_FAILURE);
	}
	/* 
	 * creation of a char matrix representing our game's board.
	 */
	char ** grid = allocation_char_matrix(game_width(g), game_height(g)); 
	/* 
	 * initialization of the tab with '.'.
	 */
	for (int i = 0; i < game_width(g); i++){
		for (int j = 0; j < game_height(g); j++){
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
	if(g==NULL || piece_played<0 || piece_played>=game_nb_pieces(g)){
		fprintf(stderr, "display_success_movement : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
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
 * @brief function allowing the reading of pieces features from an annexed file.
 */
piece * lecture(piece * pieces_test, int * n, FILE * entree) {
	if(pieces_test==NULL || n==NULL){
		fprintf(stderr, "lecture : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
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
		printf("Erreur durant l'ouverture du fichier\n");
		exit(EXIT_FAILURE);
	}  
	fscanf(entree, "%d", &number_pieces);
	pieces_test = allocation_piece_tab(number_pieces, "main"); 
	/* 
	 * creation of the tab.
	 */
	for(int i=0; i<number_pieces; i++){
		fscanf(entree, "%d %d %d %d %d %d", &c_x, &c_y, &m_x, &m_y, &w, &h);
		pieces_test[i] = new_piece(c_x, c_y, w, h, m_x, m_y);
	}
	*n = number_pieces;
	return pieces_test;
}

/**
 * @brief asks the player to write a string.
 * @param buffer tab of char in which the string written by the player is stocked.
 * @param size width of the buffer.
 * @return string written.
 */
char * scan(char * buffer , int size) {
	if(buffer==NULL || size<0){
		fprintf(stderr, "scan : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	char * result = fgets(buffer, size, stdin);
	if (result != NULL) {
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

/**
 * @brief Allocates a char matrix.
 */
char ** allocation_char_matrix(int width, int height){
	if(width<0 || height<0){
		fprintf(stderr, "allocation_char_matrix : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
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
	if(grid==NULL || width<0){
		fprintf(stderr, "delete_char_matrix : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	for(int i=0 ; i<width ; i++)
		free(grid[i]);
	free(grid);
}

char * input_config_user(char * answer, int size){
	if(answer==NULL || size<0){
		fprintf(stderr, "input_config_user : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	char * config_user = malloc(strlen("../config/"));
	strcat(config_user, "../config/");	
	printf("Entrez le nom complet de votre fichier y compris son extension.\n");
	answer = scan(answer, size);
	config_user = realloc(config_user, strlen(config_user)+strlen(answer));
	strcat(config_user, answer);
	return config_user;
}

/**
 * @brief asks the user for which piece he wants to play.
 */
int input_piece_played(char * answer, int size, cgame g){
	if(g==NULL || answer==NULL || size<0){
		fprintf(stderr, "input_piece_played : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
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
	if(g==NULL || answer==NULL || size<0){
		fprintf(stderr, "input_distance : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
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
	if(direction==NULL || size<0){
		fprintf(stderr, "input_direction : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
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
