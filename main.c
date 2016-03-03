#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "piece.h"

void display_game(cgame g) {
	char grid[6][6];
	int nbpieces = game_nb_pieces(g);
	
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			grid[i][j] ='.';
		}
	}

	for (int i = 0; i < nbpieces; i++){

		if (is_horizontal(game_piece(g,i))) {
			grid[nbpieces - get_x(game_piece(g,i)) + 1][get_y(game_piece(g,i))] = i + '0';
			if (!is_small(game_piece(g, i)))
				grid[nbpieces - get_x(game_piece(g, i)) + 2][get_y(game_piece(g,i))] = i + '0';
		}
		else {
			grid[nbpieces - get_x(game_piece(g, i))][get_y(game_piece(g, i)) + 1] = i + '0';
			if (!is_small(game_piece(g, i)))
				grid[nbpieces - get_x(game_piece(g, i))][get_y(game_piece(g, i)) + 2] = i + '0';
			
		}


		grid[nbpieces - get_x(game_piece(g,i))][get_y(game_piece(g,i))] = i + '0';
		

	}
	
	for (int x = 0; x<6; x++) {
		for (int y = 0; y<6; y++) {
			printf("%c ", grid[x][y]);
		}
		printf("\n");
	}
}

int main(){
	piece *pieces_test = malloc(sizeof(struct piece_s)*4);
	if(pieces_test==NULL){
		fprintf(stderr,"main : pieces_test non alloue\n");
		exit(EXIT_FAILURE);
	}

	pieces_test[0] = new_piece_rh(3,0,true,true);
	pieces_test[1] = new_piece_rh(0,0,true,true);
	pieces_test[2] = new_piece_rh(1,1,true,true);
	pieces_test[3] = new_piece_rh(3,3,true,false);
	pieces_test[4] = new_piece_rh(4,4,true,false);
	game g = new_game_hr(5, pieces_test);

	while(!game_over_hr(g)){
		display_game(g);
		int number_piece=0;
		int distance = 0;
		char direction[6] = "";
		printf("Quelle pièce voulez-vous jouer ?");
		scanf("%d", &number_piece);
		printf("Vous avez choisi la pièce %d. De combien de cases voulez-vous la bouger ? Entrez un nombre entre 0 et 5.", number_piece);
		scanf("%d", &distance);
		printf("Vous voulez bouger la pièce %d de %d cases. Dans quelle direction voulez-vous la bouger ? UP, DOWN, LEFT ou RIGHT ?", number_piece, distance);
		fgets(direction, sizeof(direction), stdin);
		if (strcmp(direction, "RIGHT") ==0)
		{
			printf("Vous voulez bouger la pièce %d de %d cases vers la droite.", number_piece, distance);
			play_move(g, number_piece, RIGHT, distance);
		}
		else if (strcmp(direction, "LEFT") ==0)
		{
			printf("Vous voulez bouger la pièce %d de %d cases vers la gauche.", number_piece, distance);
			play_move(g, number_piece, LEFT, distance);
		}
		else if (strcmp(direction, "UP") ==0)
		{
			printf("Vous voulez bouger la pièce %d de %d cases vers le haut.", number_piece, distance);
			play_move(g, number_piece, UP, distance);
		}
		else if (strcmp(direction, "DOWN") ==0)
		{
			printf("Vous voulez bouger la pièce %d de %d cases vers le bas.", number_piece, distance);
			play_move(g, number_piece, DOWN, distance);
		}
		else
		{
			printf("Merci d'entrer une direction valide. UP, DOWN, RIGHT ou LEFT");
		}
	}

	delete_game(g);

	return 1;
}
