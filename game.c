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
		g->pieces[i] = new_piece_rh(0,0,true,true);
		copy_piece(pieces[i],game_piece(g,i));
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
		for(int i=0 ; i<game_nb_pieces(g) ; i++){
			delete_piece(game_pieces(g,i));
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
	for(int i=0;i<game_nb_pieces(dst) ;i++){
			delete_piece(game_piece(dst,i));
	}
	
	piece * ptr_tmp = realloc(dst->pieces, sizeof(struct piece_s)*game_nb_pieces(src));
	if(ptr_tmp == NULL){
		fprintf(stderr, "copy_game : erreur realloc dst->pieces\n");
		exit(EXIT_FAILURE);
	}
	dst->pieces = ptr_tmp;
	dst->nb_pieces=game_nb_pieces(src);

	for(int j=0;j<game_nb_pieces(src);j++){
		dst->pieces[j] = game_piece(g,j)];
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
	if(get_x(game_piece(g, 0)) == 3 && get_y(game_piece(g,0)) == 4)
		return true;
	return false;
}


bool play_move(game g, int piece_num, dir d, int distance){ 
	if (g == NULL || piece_num >= game_nb_pieces(g) || piece_num <0 || distance < 0){
		fprintf(stderr, "play_move : parametres invalides\n");
		return false;
	}

	/*piece * t_pieces = malloc(sizeof(struct piece_s)*game_nb_pieces(g));
	for(int i=0;i<game_nb_pieces(g);i++){
		t_pieces[i] = new_piece_rh(0,0,true,true);
	}*/

	game gTmp = new_game_hr(game_nb_pieces(g), g->pieces);
	copy_game(g, gTmp);

	piece piece_moved = gTmp->pieces[piece_num];

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
	for(int i=0 ; i<game_nb_pieces(g)-1 ; i++){
		for(int j=i+1 ; j<game_nb_pieces(g) ; j++){
			if(intersect(game_piece(g,i), game_piece(g,j)){
				fprintf(stderr, "game_valid : la piece %d et la piece %d se chevauchent\n", i, j);
				return false;
			}
		}
	}

	for(int k=0 ; k<game_nb_pieces(g) ; k++){
		if(!is_in_board(game_piece(g,k)){
			fprintf(stderr, "game_valid : la piece %d est hors du tableau\n", k);
			return false;
		}
	}
	return true;
}