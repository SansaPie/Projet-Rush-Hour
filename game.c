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
	g->pieces = malloc(sizeof(piece)*nb_pieces);
	if(g->pieces == NULL){
		fprintf(stderr, "new_game_hr : g->pieces non alloue\n");
		exit(EXIT_FAILURE);
	}
	for(int i=0 ; i<nb_pieces ; i++){
		g->pieces[i] = new_piece_rh(0,0,true,true);
		copy_piece(pieces[i],g->pieces[i]);
	}
	g->moves = 0;
	if(!game_valid(g)){
		fprintf(stderr, "new_game_hr : jeu non valide\n");
		exit(EXIT_FAILURE);
	}
	return g;
}

void delete_pieces(int nb_pieces, piece * pieces){
	if(pieces!=NULL){
		for(int i=0 ; i<nb_pieces ; i++){
			delete_piece(pieces[i]);		
		}
		free(pieces);
	}else{
		fprintf(stderr, "delete_pieces : pieces null\n");
		exit(EXIT_FAILURE);
	}
}

void delete_game(game g){
	if (g != NULL){
		delete_pieces(game_nb_pieces(g), g->pieces);
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

	delete_pieces(game_nb_pieces(dst), dst->pieces);
	
	dst->pieces = malloc(sizeof(piece)*game_nb_pieces(src));
	if(dst->pieces == NULL){
		fprintf(stderr, "copy_game : erreur malloc dst->pieces\n");
		exit(EXIT_FAILURE);
	}

	dst->nb_pieces=game_nb_pieces(src);

	for(int i=0;i<game_nb_pieces(src);i++){
		dst->pieces[i] = new_piece_rh(0,0,true,true);
		copy_piece(game_piece(src,i), dst->pieces[i]);
	}

	dst->moves = game_nb_moves(src);
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
	if(get_x(game_piece(g, 0)) == 4 && get_y(game_piece(g,0)) == 3)
		return true;
	return false;
}


bool play_move(game g, int piece_num, dir d, int distance){ 
	if (g == NULL || piece_num >= game_nb_pieces(g) || piece_num <0){
		fprintf(stderr, "play_move : parametres invalides\n");
		return false;
	}

	piece * t_pieces = malloc(sizeof(piece));
	t_pieces[0] = new_piece_rh(0,0,true,true);
	game gTmp = new_game_hr(1, t_pieces);
	copy_game(g, gTmp);

	piece piece_moved = gTmp->pieces[piece_num];
	
	for (int i = 0; i <= distance; i++) {
		if (((d == LEFT || d == RIGHT) && is_horizontal(piece_moved)) ||
			((d == UP || d == DOWN) && !is_horizontal(piece_moved))) {
			move_piece(piece_moved, d,i);
		}
		if (!game_valid(gTmp)) {
			delete_game(gTmp);
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
	for(int i=0 ; i<game_nb_pieces(g) ; i++){
		if(!is_in_board(game_piece(g,i))){
			fprintf(stderr, "game_valid : la piece %d est hors du tableau\n", i);
			return false;
		}
	}
	for(int i=0 ; i<game_nb_pieces(g)-1 ; i++){
		for(int j=i+1 ; j<game_nb_pieces(g) ; j++){
			if(intersect(game_piece(g,i), game_piece(g,j))){
				fprintf(stderr, "game_valid : la piece %d et la piece %d se chevauchent\n", i, j);
				return false;
			}
		}
	}
	return true;
}