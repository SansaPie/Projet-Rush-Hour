#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "piece.h"

int main(){
	piece *pieces_test = malloc(sizeof(struct piece)*5);
	if(pieces_test==NULL){
		fprintf(stderr,"pieces_test non alloue\n");
		exit(EXIT_FAILURE);
	}

	pieces_test[1] = new_piece_rh(0,0,true,true);
	pieces_test[0] = new_piece_rh(3,0,true,true);
	pieces_test[2] = new_piece_rh(1,1,true,true);
	pieces_test[3] = new_piece_rh(3,3,true,false);
	pieces_test[4] = new_piece_rh(4,4,true,false);
	g = new_game_hr(5, pieces_test);

	while(!game_over_hr(g)){
		play_move(g, 3, UP, 1);
		play_move(g, 0, RIGHT, 3);
	}

	printf("GG\n");

	return 1;
}