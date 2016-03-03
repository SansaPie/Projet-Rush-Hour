#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "piece.h"

void display_game(cgame g){ // A modifier
	char disp[6][6];
	for(int i=0 ; i<6 ; i++){
		for(int j=0 ; j<6 ; j++){
			disp[i][j]='.';
		}
	}

	for (int k=0 ; k<game_nb_pieces(g) ; k++){
		char tmp='a';
		switch(k){
			case 0:
				tmp = '0';
				break;
			case 1:
				tmp='1';
				break;
			case 2:
				tmp='2';
				break;
			case 3:
				tmp='3';
				break;
			case 4:
				tmp='4';
				break;
			case 5:
				tmp='5';
				break;
		}
		disp[5-get_x(g->pieces[k])][get_y(g->pieces[k])] = tmp;
	}

	for(int x=0;x<6;x++){
		for(int y=0;y<6;y++){
			printf("%c ", disp[x][y]);
		}
		printf("\n");
	}
}

int main(){
	piece *pieces_test = malloc(sizeof(struct piece_s)*5);
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
		play_move(g, 3, UP, 1);
		play_move(g, 0, RIGHT, 3);
		break;
	}
	display_game(g);

	printf("GG easy\n");

	delete_game(g);

	return 1;
}