#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "game1.h"
#include "piece.h"

#define NB_PIECES 2
#define SIZE_TAS 15
#define INIT_INDEX_TAS 0

typedef struct File {
	game gameG;
	struct File *next;
}*file;

typedef struct VraiFile{
	file premier;
	file dernier;
}*vraiFile;

typedef struct Tas {
	int capacite;
	int index;
	game *tab;
}*tas;

// Temporaire

/**
 * @brief Allocates a char matrix.
 */
char ** allocation_char_matrix(int width, int height){
	if(width<0 || height<0){
		fprintf(stderr, "allocation_char_matrix : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	char ** grid = malloc(sizeof(char*)*width);
	if(grid==NULL){
		fprintf(stderr, "allocation_char_matrix : grid null\n");
		exit(EXIT_FAILURE);
	}
	for(int i=0 ; i<width ; i++){
		grid[i] = malloc(sizeof(char)*height);
		if(grid[i]==NULL){
			fprintf(stderr, "allocation_char_matrix : grid[%d] null\n", i);
			exit(EXIT_FAILURE);
		}
	}
	return grid;
}

/**
 * @brief Deletes a char matrix.
 */
void delete_char_matrix(char ** grid, int width){
	if(grid==NULL || width<0){
		fprintf(stderr, "delete_char_matrix : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	for(int i=0 ; i<width ; i++)
		free(grid[i]);
	free(grid);
}

/**
 * @brief function displaying game in terminal.
 * 
 */
void display_game(cgame g) {
	if(g==NULL){
		fprintf(stderr, "display_game : g null.\n");
		exit(EXIT_FAILURE);
	}
	/* 
	 * creation of a char matrix representing our game's board.
	 */
	char ** grid = allocation_char_matrix(game_width(g), game_height(g)); 
	/* 
	 * initialization of the tab with '.'.
	 */
	for (int i = 0; i < game_width(g); i++) {
		for (int j = 0; j < game_height(g); j++) {
			grid[i][j] ='.';
		}
	}
	for (int i = 0; i < game_nb_pieces(g); i++){
		int xCoor = get_x(game_piece(g,i));
		int yCoor = get_y(game_piece(g,i));

		for(int x=xCoor ; x<xCoor+get_width(game_piece(g, i)) ; x++){
			for(int y=yCoor ; y<yCoor+get_height(game_piece(g, i)) ; y++){
				grid[x][y]=i+'0';
			}
		}
	}
	
	/* 
	 * display the game's board.
	 */
	for (int y = game_height(g)-1; y>=0; y--) {
		for (int x = 0; x<game_width(g); x++) {
			printf("%c ", grid[x][y]);
		}
		printf("\n");
	}
	printf("\n");
	delete_char_matrix(grid, game_width(g));
}

void display_game_in_file(vraiFile f){
	int i=0;
	file tmp = f->premier;
	while(tmp!=NULL){
		printf("\n\n\n%d : \n", i);
		display_game(tmp->gameG);
		i++;
		tmp = tmp->next;
	}
}

// Fin temporaire


tas new_tas(int capacite) {
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

void free_tas(tas t) {
	if (t != NULL) {
		for(int i=0 ; i<t->index ; i++){
			delete_game(t->tab[i]);
		}
		free(t->tab);
		free(t);
	}
}

void resize_tas(tas t) { // A revoir
	int newCapacite = 2 * t->capacite;
	t->tab = realloc(t->tab, newCapacite * sizeof(game));
	if (t->tab == NULL)
		exit(EXIT_FAILURE);
	t->capacite = newCapacite;
}

void push(tas t, game g) {
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

vraiFile new_file(){
	vraiFile f = malloc(sizeof(struct VraiFile));
	f->premier = NULL;
	f->dernier = NULL;
	return f;
}

void enfiler(vraiFile f, game g) {
	file nouvelElement = malloc(sizeof(struct File));
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

	if (f->premier == NULL){
		f->premier = nouvelElement;
		f->dernier = f->premier;
	}
	else if(f->premier->next==NULL){
		f->premier->next = nouvelElement;
		f->dernier = nouvelElement;
	}
	else{
		f->dernier->next = nouvelElement;
		f->dernier = f->dernier->next;
	}
}

void defiler(vraiFile f) {
	if (f != NULL){
		if(f->premier==f->dernier){
			delete_game(f->premier->gameG);
			f->premier = NULL;
			f->dernier = NULL;
		}
		else{
			file tmp = f->premier;
			while(tmp->next != f->dernier){
					tmp = tmp->next;
				}
			delete_game(tmp->next->gameG);
			f->dernier = tmp;
			f->dernier->next = NULL;
		}
	}
}

void free_file(vraiFile f){
	while(f->premier != NULL){
		defiler(f);
	}
	free(f);
}

bool equals(cgame g, cgame g1) {	
	if (game_nb_pieces(g) != game_nb_pieces(g1))
		return false;
	
	for (int i = 0; i < game_nb_pieces(g); i++) {
		if (!(get_x(game_piece(g, i)) == get_x(game_piece(g1, i)) && get_y(game_piece(g, i)) == get_y(game_piece(g1, i))))
			return false;
		if (!(can_move_x(game_piece(g, i)) == can_move_x(game_piece(g1, i)) && can_move_y(game_piece(g, i)) == can_move_y(game_piece(g1, i))))
			return false;
		if (!(get_width(game_piece(g, i)) == get_width(game_piece(g1, i)) && get_height(game_piece(g, i)) == get_height(game_piece(g1, i))))
			return false;
	}
	
	return true;
}

bool existe_config(cgame g, tas t) {
	for (int i = 0; i < t->index; i++) {
		if (equals(g, t->tab[i]))
			return true;
	}
	return false;
}

vraiFile solv(game g) {
	vraiFile f = new_file();
	tas t = new_tas(SIZE_TAS);
	enfiler(f, g); 
	if (game_over_hr(g))
		return f;
	push(t, g);

	piece * t_pieces = allocation_piece_tab(1, "solv");
	t_pieces[0] = new_piece(1,1,1,1,true,true);
	game tmp = new_game(game_width(g), game_height(g), 1, t_pieces);
	
	file tmp_f = f->premier;

	while (tmp_f != NULL && !game_over_hr(f->dernier->gameG)) {
		for (int i = 0; i < game_nb_pieces(g); i++) {
			for (dir d = UP; d <= RIGHT; d++) {
				enfiler(f, tmp_f->gameG);
				copy_game(f->dernier->gameG, tmp);
				if (play_move(f->dernier->gameG, i, d, 1) && !equals(f->dernier->gameG, tmp)) {
					if (!existe_config(f->dernier->gameG, t))
						push(t, f->dernier->gameG);
					else
						defiler(f);
				}else
					defiler(f);
			}
		}
		tmp_f = tmp_f->next;
	}
	free_tas(t);
	delete_pieces(1, t_pieces);
	delete_game(tmp);
	return f;
}

int main(void) {
	piece * pieces = malloc(sizeof(piece)*NB_PIECES);
	pieces[0] = new_piece_rh(0, 3, true, true);
	pieces[1] = new_piece_rh(3, 3, true, false);
	game jeuSolveur = new_game_hr(NB_PIECES, pieces);

	vraiFile moves_to_display = solv(jeuSolveur);
	display_game_in_file(moves_to_display);
	free_file(moves_to_display);
	delete_pieces(NB_PIECES, pieces);
	delete_game(jeuSolveur);
	return EXIT_SUCCESS;
}