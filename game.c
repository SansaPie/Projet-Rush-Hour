#include <stdio.h>
#include <stdlib.h>
#include "piece.h"
#include "game.h"

game new_game_hr (int nb_pieces, piece *pieces){
	if(nb_pieces<0 || pieces==NULL){
		fprintf(stderr, "new_game_hr : parametres incorrects\n");
		exit(EXIT_FAILURE);
	}
	game g = malloc(sizeof(struct game_s));
	if(g==NULL){
		fprintf(stderr,"new_game_hr : g non alloue\n");
		exit(EXIT_FAILURE);
	}
	g->nb_pieces = nb_pieces;
	g->pieces = malloc(sizeof(struct piece_s)*nb_pieces);
	for(int i=0 ; i<nb_pieces ; i++){
		g->pieces[i] = pieces[i];
	}
	g->moves = 0;
	if(!game_valid(g)){
		fprintf(stderr, "new_game_hr : jeu non valide\n");
		exit(EXIT_FAILURE);
	}
	return g;
}

void delete_game(game g){
	if (g != NULL){
		for(int i=0 ; i<g->nb_pieces ; i++){
			delete_piece(g->pieces[i]);
		}
		free(g);
	}else{
		fprintf(stderr, "delete_game : g null\n");
		exit(EXIT_FAILURE);
	}
}

void copy_game (cgame src, game dst){
	if(src==NULL || dst==NULL){
		fprintf(stderr, "copy_game : parametres invalides\n");
		exit(EXIT_FAILURE);
	}
	game * dstTmp = &dst;
	*dstTmp = new_game_hr(src->nb_pieces, src->pieces);
	(*dstTmp)->moves = src->moves;
}

int game_nb_pieces(cgame g){
	if(g==NULL){
		fprintf(stderr, "game_nb_pieces : g invalide\n");
		exit(EXIT_FAILURE);
	}
	return g->nb_pieces;
}

cpiece game_piece(cgame g, int piece_num){
	if(g==NULL || (piece_num<0 && piece_num>game_nb_pieces(g))){
		fprintf(stderr, "game_piece : g invalide\n");
		exit(EXIT_FAILURE);
	}
	return g->pieces[piece_num];
}

bool game_over_hr(cgame g){
	if(g==NULL){
		fprintf(stderr, "game_over_hr : g invalide\n");
		exit(EXIT_FAILURE);
	}
	if(g->pieces[0]->x == 3 && g->pieces[0]->y == 4)
		return true;
	return false;
}


bool play_move(game g, int piece_num, dir d, int distance){ 
	if (g == NULL || piece_num >= g->nb_pieces || piece_num <0 || distance < 0){
		fprintf(stderr, "play_move : parametres invalides\n");
		return false;
	}

	piece piece_moved = NULL;
	copy_piece(g->pieces[piece_num], piece_moved);

	game gTmp = NULL;
	copy_game(g, gTmp);

	if(((d==LEFT||d==RIGHT) && is_horizontal(piece_moved))||
		((d==UP||d==DOWN) && !is_horizontal(piece_moved))){
		move_piece(piece_moved, d, distance);
	}
	if(!game_valid(gTmp))
		return false;
	gTmp->moves += distance;

	g = gTmp;

	return true;
}

int game_nb_moves(cgame g){
	if(g==NULL){
		fprintf(stderr, "game_nb_moves : g invalide\n");
		exit(EXIT_FAILURE);
	}
	return g->moves;
}

bool game_valid(cgame g){
	if(g==NULL){
		fprintf(stderr, "game_valid : g invalide\n");
		exit(EXIT_FAILURE);
	}
	for(int i=0 ; i<g->nb_pieces-1 ; i++){
		for(int j=i+1 ; j<g->nb_pieces ; j++){
			if(intersect(g->pieces[i], g->pieces[j])){
				fprintf(stderr, "game_valid : la piece %d et la piece %d se chevauchent\n", i, j);
				return false;
			}
		}
	}

	for(int k=0 ; k<g->nb_pieces ; k++){
		if(!is_in_board(g->pieces[k])){
			fprintf(stderr, "game_valid : la piece %d est hors du tableau\n", k);
			return false;
		}
	}
	return true;
}