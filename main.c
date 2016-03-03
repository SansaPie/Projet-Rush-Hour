#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "piece.h"

void display_game2(cgame g) {
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
	//pieces_test[4] = new_piece_rh(4,4,true,false);
	game g = new_game_hr(4, pieces_test);
	/*
	while(!game_over_hr(g)){
		play_move(g, 3, UP, 1);
		play_move(g, 0, RIGHT, 3);
		break;
	}*/
	display_game2(g);

	printf("GG easy\n");

	delete_game(g);

	return 1;
}