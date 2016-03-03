#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "piece.h"

void display_game(cgame g) { /* la fonction affiche le jeu dans le terminal */
	char grid[6][6]; /* on créé un tableau à deux dimensions qui représente notre plateau de jeu */
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
	piece *pieces_test = malloc(sizeof(struct piece_s)*4); /* on créé un tableau qui contient les pièces */
	if(pieces_test==NULL){ /* on vérifie que ce tableau a bien été alloué */
		fprintf(stderr,"main : pieces_test non alloue\n");
		exit(EXIT_FAILURE);
	}

	pieces_test[0] = new_piece_rh(3,0,true,true);
	pieces_test[1] = new_piece_rh(0,0,true,true);
	pieces_test[2] = new_piece_rh(1,1,true,true);
	pieces_test[3] = new_piece_rh(3,3,true,false);
	pieces_test[4] = new_piece_rh(4,4,true,false);
	game g = new_game_hr(5, pieces_test); /* initialisation d'un premier jeu */

	while(!game_over_hr(g)){ /* tant que le jeu n'est pas fini, on demande à l'utilisateur ce qu'il veut jouer */
		display_game(g);
		char tmp[6] = "";
		printf("Quelle piece voulez-vous jouer ? Rentrez son numéro. \n");
		int number_piece = atoi(fgets(tmp, sizeof(tmp), stdin));
		printf("Vous avez choisi la piece %d. De combien de cases voulez-vous la bouger ? Entrez un nombre entre 0 et 5. \n", number_piece);		
		int distance = atoi(fgets(tmp, sizeof(tmp), stdin));		
		printf("Vous voulez bouger la piece %d de %d cases. Dans quelle direction voulez-vous la bouger ? UP, DOWN, LEFT ou RIGHT ? \n", number_piece, distance);
		fgets(tmp, sizeof(tmp), stdin);
		printf("%s \n", tmp);
		char right[7]="RIGHT";
		if (strcmp(tmp, right) ==0)
		{
			printf("Vous voulez bouger la piece %d de %d cases vers la droite. \n", number_piece, distance);
			play_move(g, number_piece, RIGHT, distance);
		}
		else if (strcmp(tmp, "LEFT") ==0)
		{
			printf("Vous voulez bouger la piece %d de %d cases vers la gauche. \n", number_piece, distance);
			play_move(g, number_piece, LEFT, distance);
		}
		else if (strcmp(tmp, "UP") ==0)
		{
			printf("Vous voulez bouger la piece %d de %d cases vers le haut. \n", number_piece, distance);
			play_move(g, number_piece, UP, distance);
		}
		else if (strcmp(tmp, "DOWN") ==0)
		{
			printf("Vous voulez bouger la piece %d de %d cases vers le bas. \n", number_piece, distance);
			play_move(g, number_piece, DOWN, distance);
		}
		else
		{
			printf("Merci d'entrer une direction valide. UP, DOWN, RIGHT ou LEFT \n");
		}
	}
	delete_game(g);

	return 1;
}
