#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "piece.h"
#include "game1.h"

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
	if(distance==NULL || size<0){
		fprintf(stderr, "input_distance : parametres incorrects.\n");
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
