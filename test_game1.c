#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "piece.h"

void display_game(cgame g) { /* la fonction affiche le jeu dans le terminal */
	char grid[6][6]; /* on créé un tableau à deux dimensions qui représente notre plateau de jeu */
	
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			grid[i][j] ='.';
		}
	}

	for (int i = 0; i < game_nb_pieces(g); i++){

		int xCoordDisplay = get_x(game_piece(g,i));
		int yCoordDisplay = 5-get_y(game_piece(g,i));

		grid[xCoordDisplay][yCoordDisplay] = i + '0';
		if (!is_horizontal(game_piece(g,i))) {
			grid[xCoordDisplay][yCoordDisplay -1] = i + '0';
			if (!is_small(game_piece(g, i)))
				grid[xCoordDisplay][yCoordDisplay - 2] = i + '0';
		}
		else {
			grid[xCoordDisplay + 1][yCoordDisplay] = i + '0';
			if (!is_small(game_piece(g, i)))
				grid[xCoordDisplay + 2][yCoordDisplay] = i + '0';	
		}
	}
	
	for (int x = 0; x<6; x++) {
		for (int y = 0; y<6; y++) {
			printf("%c ", grid[y][x]);
		}
		printf("\n");
	}
}

int main(){
	piece *pieces_test = malloc(sizeof(piece)*5);
	if(pieces_test==NULL){
		fprintf(stderr,"main : pieces_test non alloue\n");
		exit(EXIT_FAILURE);
	}
	pieces_test[0] = new_piece_rh(0,3,true,true);
	pieces_test[1] = new_piece_rh(0,0,false,true);
	pieces_test[2] = new_piece_rh(1,1,false,true);
	pieces_test[3] = new_piece_rh(3,3,false,false);
	pieces_test[4] = new_piece_rh(4,4,true,false);
	game g = new_game_hr(5, pieces_test);
	printf("g : \n");
	display_game(g);

	piece * t_pieces = malloc(sizeof(piece));
	t_pieces[0] = new_piece_rh(0,0,true,true);
	game gTmp = new_game_hr(1,t_pieces);
	copy_game(g, gTmp);
	printf("gTmp : \n");
	display_game(gTmp);

	delete_game(gTmp);
	delete_game(g);
	delete_pieces(1, t_pieces);
	delete_pieces(5, pieces_test);
	return EXIT_SUCCESS;
}