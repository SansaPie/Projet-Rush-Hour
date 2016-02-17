#include <stdio.h>
#include <stdlib.h>
#include "game.h"

typedef struct game_s*{
	int nb_pieces;
	piece *pieces;
	int moves;
} game;

typedef const struct game_s*{
	game_s* Game;
} cgame;

game new_game_hr (int nb_pieces, piece *pieces){
	if(nb_pieces<0 || pieces==NULL)
		exit(EXIT_FAILURE);
	game g = malloc(sizeof(struct game_s));
	g->nb_pieces = nb_pieces;
	for(int i=0 ; i<nb_pieces ; i++){
		g->pieces[i] = pieces[i];
	}
	g->moves = 0;
	return g;
}

void delete_game(game g){
	free(g);
}

void copy_game (cgame src, game dst){
	if(src==NULL || dst==NULL)
		exit(EXIT_FAILURE);
	dst->moves = src->moves;
	dst->nb_pieces = src->nb_pieces;
	for(int i=0 ; i<nb_pieces ; i++){
		dst->pieces[i]=src->pieces[i];
	}
}

int game_nb_pieces(cgame g){
	if(g==NULL)
		exit(EXIT_FAILURE);
	return g->nb_pieces;
}

cpiece game_piece(cgame g, int piece_num){
	if(g==NULL || piece_num>0 && piece_num<g->nb_pieces)
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

bool play_move(game g, int piece_num, dir d, int distance){
	
}

int game_nb_moves(cgame g){
	return g->moves;
}