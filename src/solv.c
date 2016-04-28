#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "game.h"
#include "game1.h"
#include "piece.h"
#include "solv.h"

#define NB_PIECES 2
#define SIZE_TAS 15
#define INIT_INDEX_TAS 0


void usage(char * commande){
	fprintf(stderr, "usage : %s \npremier argument : char 'a' ou 'r' \nsecond argument : char * (fichier .txt)\n"
		, commande);
	exit(EXIT_FAILURE);
}

piece * lecture(piece * pieces_test, int * n, int * width, int * height, FILE * entree){
	if(n==NULL || width==NULL || height==NULL){
		fprintf(stderr, "lecture : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	/**
	 * var used for the lecture of the file.
	 */
	int board_width;
	int board_height;
	int number_pieces;
	int c_x;	   // x-coor.
	int c_y;	   // y-coor.
	int m_x;	   // move_x.
	int m_y;	   // move_y.
	int w;		   // width of the piece.
	int h;		   // height of the piece.

	if(entree == NULL){
		printf("erreur durant l'ouverture du fichier\n");
		exit(EXIT_FAILURE);
	}
	fscanf(entree, "%d %d", &board_width, &board_height); // width and height of the game board
	fscanf(entree, "%d", &number_pieces);
	pieces_test = allocation_piece_tab(number_pieces, "main"); 
	/**
	 * creation of the tab.
	 */
	for(int i=0; i<number_pieces; i++){
		fscanf(entree, "%d %d %d %d %d %d", &c_x, &c_y, &m_x, &m_y, &w, &h);
		pieces_test[i] = new_piece(c_x, c_y, w, h, m_x, m_y);
	}
	*n = number_pieces;
	*width = board_width;
	*height = board_height;
	return pieces_test;
}

tas new_tas(int capacite){
	if(capacite<=0){
		fprintf(stderr, "new_tas : capacite inferieur ou egal a 0\n");
		exit(EXIT_FAILURE);
	}
	tas t = malloc(sizeof(struct Tas));
	if(t==NULL){
		fprintf(stderr, "new_tas : echec allocation t\n");
		exit(EXIT_FAILURE);
	}
	t->capacite = capacite;
	t->index = INIT_INDEX_TAS;
	t->tab = malloc(sizeof(game)*capacite);
	if(t->tab == NULL){
		fprintf(stderr, "new_tas : echec allocation t-tab\n");
		exit(EXIT_FAILURE);
	}
	return t;
}

void free_tas(tas t){
	if (t != NULL) {
		for(int i=0 ; i<t->index ; i++){
			delete_game(t->tab[i]);
		}
		free(t->tab);
		free(t);
	}
}

void resize_tas(tas t){
	int newCapacite = 2 * t->capacite;
	t->tab = realloc(t->tab, newCapacite * sizeof(game));
	if (t->tab == NULL)
		exit(EXIT_FAILURE);
	t->capacite = newCapacite;
}

void push(tas t, game g){
	piece * tmp = allocation_piece_tab(1, "push");
	tmp[0] = new_piece(1,1,1,1,true,true);

	if (t->capacite <= t->index)
		resize_tas(t);
	t->tab[t->index] = new_game(game_width(g), game_height(g), 1, tmp);
	copy_game(g, t->tab[t->index]);
	t->index++;

	delete_pieces(1, tmp);
}

tas copy_tas(tas src, tas dst){
	if(src == NULL){
		fprintf(stderr, "copy_tas : src null\n");
		exit(EXIT_FAILURE);
	}
	free_tas(dst);
	dst = new_tas(src->capacite);
	for(int i=0 ; i<src->index ; i++){
		push(dst, src->tab[i]);
	}
	return dst;
}

file new_file(){
	file f = malloc(sizeof(struct File));
	f->premier = NULL;
	return f;
}

void enfiler(file f, game g){
	maillon nouvelElement = malloc(sizeof(struct Maillon));
	if (nouvelElement == NULL){
		fprintf(stderr, "enfiler : erreur allocation nouvelElement\n");
		exit(EXIT_FAILURE);
	}
	piece * t_pieces = allocation_piece_tab(1, "enfiler");
	t_pieces[0] = new_piece(1,1,1,1, true, true);
	nouvelElement->gameG = new_game(game_width(g), game_height(g), 1, t_pieces);
	delete_pieces(1, t_pieces);

	copy_game(g, nouvelElement->gameG);
	nouvelElement->next = NULL;

	if (f->premier == NULL)
		f->premier = nouvelElement;
	else{
		maillon tmp = f->premier;
		while(tmp->next!=NULL){
			tmp=tmp->next;
		}
		tmp->next = nouvelElement;
	}
}

void defiler(file f){
	if (f != NULL){
		if(f->premier->next==NULL){
			delete_game(f->premier->gameG);
			free(f->premier);
			f->premier = NULL;
		}
		else{
			maillon tmp = f->premier;
			tmp = tmp->next;
			delete_game(f->premier->gameG);
			free(f->premier);
			f->premier = tmp;
		}
	}
}

void free_file(file f){
	while(f->premier != NULL){
		defiler(f);
	}
	free(f);
}

bool equals(cgame g, cgame g1){	
	if (game_nb_pieces(g) != game_nb_pieces(g1))
		return false;
	
	for (int i = 0; i < game_nb_pieces(g); i++){
		if (!(get_x(game_piece(g, i)) == get_x(game_piece(g1, i)) && get_y(game_piece(g, i)) == get_y(game_piece(g1, i))))
			return false;
		if (!(can_move_x(game_piece(g, i)) == can_move_x(game_piece(g1, i)) && can_move_y(game_piece(g, i)) == can_move_y(game_piece(g1, i))))
			return false;
		if (!(get_width(game_piece(g, i)) == get_width(game_piece(g1, i)) && get_height(game_piece(g, i)) == get_height(game_piece(g1, i))))
			return false;
	}
	
	return true;
}

bool is_config(cgame g, tas t){
	for (int i = t->index - 1 ; i >= 0; i--){
		if (equals(g, t->tab[i]))
			return true;
	}
	return false;
}

bool game_over(char game_type, file f){
	if((game_type!='a' && game_type!='r') || f==NULL){
		fprintf(stderr, "game_over : parametres incorrects\n");
		exit(EXIT_FAILURE);
	}

	maillon tmp = f->premier;
	while (tmp->next!=NULL){
		tmp = tmp->next;
	}

	if(game_type=='a')
		return game_over_ar(tmp->gameG);
	else
		return game_over_hr(tmp->gameG); 
}

int solv(game g, char game_type){
	file f = new_file();
	tas t = new_tas(SIZE_TAS);
	int res = game_nb_moves(g);
	enfiler(f, g); 
	if (game_over(game_type, f))
		return res;
	push(t, g);

	piece * t_pieces = allocation_piece_tab(1, "solv");
	t_pieces[0] = new_piece(1,1,1,1,true,true);
	game tmp = new_game(game_width(g), game_height(g), 1, t_pieces);
	delete_pieces(1, t_pieces);

	while (f->premier != NULL ){
		for (int i = 0; i < game_nb_pieces(g); i++){
			for (dir d = UP; d <= RIGHT; d++){
				copy_game(f->premier->gameG, tmp);
				
				if(play_move(tmp, i, d, 1)){
					if(game_over(game_type, f)){
						res = game_nb_moves(tmp);
						free_file(f);
						free_tas(t);
						delete_game(tmp);
						return res;
					}
					if (!is_config(tmp, t)){
						push(t, tmp);
						enfiler(f, tmp);
					}
				}
			}
		}
		defiler(f);
	}
	res = -1;
	free_tas(t);
	free_file(f);
	delete_game(tmp);
	return res;
}

int main(int argc, char * argv[]){

	if(argc!=3 || strlen(argv[1])!=1 || (argv[1][0]!='a' && argv[1][0]!='r')){
		usage(argv[0]);
	}

	int nb_pieces, width, height = 0;

	FILE * entree = fopen(argv[2], "r+");
	if(entree==NULL){
		fprintf(stderr, "main : erreur lors ouverture fichier\n");
		exit(EXIT_FAILURE);
	}

	piece * pieces_from_file = NULL;
	pieces_from_file = lecture(pieces_from_file, &nb_pieces, &width, &height, entree);
	game game_for_solveur = new_game(width, height, nb_pieces, pieces_from_file);

	int res = solv(game_for_solveur, argv[1][0]);
	printf("%d\n", res);

	delete_pieces(nb_pieces, pieces_from_file);
	delete_game(game_for_solveur);

	fclose(entree);
	return EXIT_SUCCESS;
}