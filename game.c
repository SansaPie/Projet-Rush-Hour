#include <stdio.h>
#include <stdlib.h>
#include "game.h"

/* 
bool test_equality_bool(bool expected, bool value, char * msg);

bool test_intersect(game g, int piece_num); 

Ces deux fonctions, codées plus bas, sont en lien avec la fonction play_move. Ce sont des ébauches d'idées mais je suis pas du tout sûre que ce soit intelligent, 
donc si l'un d'entre vous pouvait y jeter un oeil, ce serait cool. Dans le cas où vous les supprimeriez, n'oubliez pas de les virer également de game.h

~ Lisa

*/

game new_game_hr (int nb_pieces, piece *pieces){
	if(nb_pieces<0 || pieces==NULL)
		exit(EXIT_FAILURE);
	game g = malloc(sizeof(struct game_s));
	g->nb_pieces = nb_pieces;
	for(int i=0 ; i<nb_pieces ; i++){
		g->pieces[i] = pieces[i];
	}
	g->moves = 0;
	if(!game_valid(g))
		exit(EXIT_FAILURE);
	return g;
}

void delete_game(game g){
	if ( g != NULL) // ajout test
		free(g);
}

void copy_game (cgame src, game dst){
	if(src==NULL || dst==NULL)
		exit(EXIT_FAILURE);
	dst->moves = src->moves;
	dst->nb_pieces = src->nb_pieces;
	for(int i=0 ; i<src->nb_pieces ; i++){
		dst->pieces[i]=src->pieces[i];
	}
}

int game_nb_pieces(cgame g){
	if(g==NULL)
		exit(EXIT_FAILURE);
	return g->nb_pieces;
}

cpiece game_piece(cgame g, int piece_num){
	if(g==NULL || (piece_num>0 && piece_num<g->nb_pieces))
		exit(EXIT_FAILURE);
	return g->pieces[piece_num];
}

bool game_over_hr(cgame g){
	if(g==NULL)
		exit(EXIT_FAILURE);
	if(g->pieces[0]->x == 4 && g->pieces[0]->y == 3)
		return true;
	return false;
}


bool test_equality_bool(bool expected, bool value, char * msg) { // A REVOIR
	if (expected != value){
		fprintf(stderr,"ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
		exit(EXIT_FAILURE);
	}
	return expected == value;
}


bool test_intersect(game g, int piece_num) { // A REVOIR
	bool result = true;
    	for (int j =0; j<NB_PIECES; j++) {
     		result = result && test_equality_bool(i==j, intersect(g->pieces[piece_num], pieces[j]),"intersect");
		if result = false
			return result;
	}
	return result;
}


bool play_move(game g, int piece_num, dir d, int distance){ 
	if (piece_num >= g->nb_pieces || piece_num <0 || distance < 0)
		return false;

	piece piece_moved = NULL;
	copy_piece(g->pieces[piece_num], piece_moved);

	game gTmp = NULL;
	copy_game(g, gTmp);

	if((d==LEFT||d==RIGHT && isHorizontal(piece_moved))||
		(d==UP||d==DOWN && !isHorizontal(piece_moved))){
		move_piece(piece_moved, d, distance);
	}

	if(piece_moved->x<0 || piece_moved->x>6 && 
		piece_moved->y<0 || piece_moved->y>6 &&
		!game_valid(gTmp))
		return false;

	g = gTmp;

	return true;
}

int game_nb_moves(cgame g){
	return g->moves;
}

bool game_valid(cgame g){
	for(int i=0 ; i<g->nb_pieces-1 ; i++){
		for(int j=i+1 ; j<g->nb_pieces ; j++){
			if(intersect(g->pieces[i], g->pieces[j])
				return false;
		}
	}
	return true;
}