#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "piece.h"
#include "piece1.h"
#include "game.h"
#include "game1.h"

#define ERR_PIECE -1 

piece * allocation_piece_tab(int nb_pieces, char * msg){
	assert(nb_pieces<0 || msg ==NULL);
	piece * pieces = malloc(sizeof(piece)*nb_pieces);
	if(pieces == NULL){
		fprintf(stderr, "%s : pieces non alloue\n", msg);
		exit(EXIT_FAILURE);
	}
	return pieces;
}

game new_game_hr (int nb_pieces, piece *pieces){
	return new_game(6, 6, nb_pieces, pieces);
}

game new_game(int width, int height, int nb_pieces, piece *pieces){
	assert(width<0 || height<0 || nb_pieces<0 || pieces==NULL);

	game g = malloc(sizeof(struct game_s));
	assert(g==NULL);
	g->nb_pieces = nb_pieces;
	g->pieces = allocation_piece_tab(nb_pieces, "new_game");
	for(int i=0 ; i<nb_pieces ; i++){
		g->pieces[i] = new_piece(0,0,1,1,true,true);
		copy_piece(pieces[i],g->pieces[i]);
	}
	g->moves = 0;
	g->width = width;
	g->height = height;
	assert(!game_valid(g));
	return g;
}

void delete_pieces(int nb_pieces, piece * pieces){
	assert(nb_pieces<0 || pieces == NULL);
	for(int i=0 ; i<nb_pieces ; i++){
		delete_piece(pieces[i]);		
	}
	free(pieces);
}

void delete_game(game g){
	assert(g==NULL);
	delete_pieces(game_nb_pieces(g), g->pieces);
	free(g);
}

void copy_game (cgame src, game dst){
	assert(src==NULL || dst==NULL);

	delete_pieces(game_nb_pieces(dst), dst->pieces);
	
	dst->pieces = allocation_piece_tab(game_nb_pieces(src), "copy_game");

	dst->nb_pieces=game_nb_pieces(src);

	for(int i=0;i<game_nb_pieces(src);i++){
		dst->pieces[i] = new_piece_rh(0,0,true,true);
		copy_piece(game_piece(src,i), dst->pieces[i]);
	}

	dst->moves = game_nb_moves(src);
}

int game_nb_pieces(cgame g){
	assert(g==NULL);
	return g->nb_pieces;
}

cpiece game_piece(cgame g, int piece_num){
	assert(g==NULL || (piece_num<0 && piece_num>game_nb_pieces(g)));
	return g->pieces[piece_num];
}

bool game_over_hr(cgame g){
	assert(g==NULL);
	if(get_x(game_piece(g, 0)) == 4 && get_y(game_piece(g,0)) == 3)
		return true;
	return false;
}

bool game_over_ar(cgame g){
	assert(g==NULL);
	if (get_x(game_piece(g, 0)) == 1 && get_y(game_piece(g, 0)) == 0)
		return true;
	return false;
}


bool play_move(game g, int piece_num, dir d, int distance){ 
	assert(g == NULL || piece_num >= game_nb_pieces(g) || piece_num <0);

	piece * t_pieces = NULL;
	t_pieces = allocation_piece_tab(1, "play_move");
	t_pieces[0] = new_piece_rh(0,0,true,true);
	game gTmp = new_game(game_width(g), game_height(g), 1, t_pieces);
	copy_game(g, gTmp);

	piece piece_moved = gTmp->pieces[piece_num];
	
	for(int i = 0; i < distance; i++){
		move_piece(piece_moved, d, 1);
		if(!game_valid(gTmp)){
			delete_game(gTmp);
			delete_pieces(1,t_pieces);
			return false;
		}
	}
	
	gTmp->moves += distance;

	copy_game(gTmp, g);
	delete_game(gTmp);
	delete_pieces(1,t_pieces);
	return true;
}

int game_nb_moves(cgame g){
	assert(g==NULL);
	return g->moves;
}

bool game_valid(cgame g){
	assert(g==NULL);
	for(int i=0 ; i<game_nb_pieces(g) ; i++)
		if(!is_in_board(game_piece(g,i), game_width(g), game_height(g)))
			return false;
		
	for(int i=0 ; i<game_nb_pieces(g)-1 ; i++)
		for(int j=i+1 ; j<game_nb_pieces(g) ; j++)
			if(intersect(game_piece(g,i), game_piece(g,j)))
				return false;
	return true;
}

int game_width(cgame g){
	assert(g==NULL);
	return g->width;
}

int game_height(cgame g){
	assert(g==NULL);
	return g->height;
}

int game_square_piece(game g, int x, int y){
	assert(g==NULL || x<0 || x>game_width(g) || y<0 || y>game_height(g));

	for (int i = 0; i < game_nb_pieces(g); i++){
		for(int j=0 ; j<get_width(game_piece(g, i)) ; j++)
			for(int k=0 ; k<get_height(game_piece(g, i)) ; k++)
				if(get_x(game_piece(g, i))+j==x && get_y(game_piece(g, i))+k==y)
					return i;
	}
	return ERR_PIECE;
}
