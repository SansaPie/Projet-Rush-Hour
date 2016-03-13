//////////////////////////////////////////////////////////// Rajout de ASSERT a faire ////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "piece.h"
#include "piece1.h"
#include "game.h"
#include "game1.h"

#define ERR_PIECE -1 

piece * allocation_piece_tab(int nb_pieces, char * msg){
	piece * pieces = malloc(sizeof(piece)*nb_pieces);
	if(pieces == NULL){
		fprintf(stderr, "%s : pieces non alloue\n", msg);
		exit(EXIT_FAILURE);
	}
	return pieces;
}

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
	g->pieces = allocation_piece_tab(nb_pieces, "new_game_hr");
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

game new_game(int width, int height, int nb_pieces, piece *pieces) {
	game g = new_game_hr(nb_pieces, pieces);
	g->height = height;
	g->width = width;
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
	
	dst->pieces = allocation_piece_tab(game_nb_pieces(src), "copy_game");

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
		exit(EXIT_FAILURE);
	}

	piece * t_pieces = NULL;
	t_pieces = allocation_piece_tab(1, "play_move");
	t_pieces[0] = new_piece_rh(0,0,true,true);
	game gTmp = new_game_hr(1, t_pieces);
	copy_game(g, gTmp);

	piece piece_moved = gTmp->pieces[piece_num];
	
	for (int i = 0; i < distance; i++) {
		if (((d == LEFT || d == RIGHT) && can_move_x(piece_moved)) ||
			((d == UP || d == DOWN) && can_move_y(piece_moved))) {
			move_piece(piece_moved, d, 1);
		}
		if (!game_valid(gTmp)) {
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
			printf("La piece %d se trouverait hors du tableau.\n", i);
			return false;
		}
	}
	for(int i=0 ; i<game_nb_pieces(g)-1 ; i++){
		for(int j=i+1 ; j<game_nb_pieces(g) ; j++){
			if(intersect(game_piece(g,i), game_piece(g,j))){
				printf("La piece %d et la piece %d se chevaucheraient.\n", i, j);
				return false;
			}
		}
	}
	return true;
}

int game_width(cgame g) {
	return g->width;
}

int game_height(cgame g) {
	return g->height;
}

int game_square_piece(game g, int x, int y) {
	if (g == NULL) {
		fprintf(stderr, "game_square_piece: g null\n");
		exit(EXIT_FAILURE);
	}
	if(x<0 || x>game_width(g) || y<0 || y>game_height(g)){
		printf("game_square_piece : coordonnees non valides\n");
		return ERR_PIECE;
	}
	for (int i = 0; i < game_nb_pieces(g); i++) {
		int xcoor = get_x(game_piece(g, i));
		int ycoor = get_y(game_piece(g, i));
		if (x == xcoor && y == ycoor)
			return i;
	}
	return ERR_PIECE;
}
