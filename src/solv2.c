#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "game1.h"
#include "piece.h"

#define NB_PIECES 1
#define SIZE_TAS 15
#define INIT_INDEX_TAS 0

typedef struct File {
	game gameG;
	struct File *next;
}*file;

typedef struct Tas {
	int capacite;
	int index;
	game *tab;
}*tas;


void resizeTas(tas t) {
	int newCapacite = 2 * t->capacite;
	t->tab = realloc(t->tab, newCapacite * sizeof(game));
	if (t->tab == NULL)
		exit(EXIT_FAILURE);
	t->capacite = newCapacite;
}

void push(tas t, game g) {
	if (t->capacite <= t->index)
		resizeTas(t);
	t->index++;
	t->tab[t->index] = g;
	
}

void freeTas(tas t) {
	if (t != NULL) {
		free(t->tab);
		free(t);
	}
}

tas creerTas(game g) {
	tas t = malloc(sizeof(struct Tas));
	t->capacite = SIZE_TAS;
	t->index = INIT_INDEX_TAS;
	t->tab = g;
}

file enfiler(file f, game g) {
	file nouvelElement = malloc(sizeof(struct File));
	if (nouvelElement == NULL)
		exit(EXIT_FAILURE);
	piece * t_pieces = NULL;
	t_pieces = allocation_piece_tab(1, "enfiler");
	t_pieces[0] = new_piece_rh(0, 0, true, true);
	
	game gTmp = new_game_hr( 1, t_pieces);

	copy_game(g, gTmp);
	nouvelElement->gameG = gTmp;
	nouvelElement->next = NULL;
	if (f == NULL) // si la liste est nulle on revoie seulement l'element insere.
		return nouvelElement;
	else {
		file tmp = f;// pointeur temporaire pour parcourir la file.
		
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = nouvelElement;

		return f;
	}
}


file defiler(file f) {
	if (f != NULL) {
		file nouveauPremierElement = f->next;
		free(f);
		return nouveauPremierElement;
	}
	else
		return NULL;
}


bool equals(cgame g, cgame g1) {
	int nbPiece_g = game_nb_pieces(g);
	int nbPiece_g1 = game_nb_pieces(g1);
	
	if (nbPiece_g != nbPiece_g1)
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



bool existeConfig(cgame g, tas t) {
	for (int i = 0; i < t->index; i++) {
		if (equals(g, t->tab[i]))
			return false;
	}
	return true;
}


int solv(game g) {
	if (game_over_hr(g))
		return game_nb_moves(g);
	file f = NULL;
	tas t = NULL;
	enfiler(f, g); 
	push(t, g);
	
	while (f != NULL) {
		for (int i = 0; i < NB_PIECES; i++) {
			for (dir d = UP; d < RIGHT; d++) {

				if (play_move(f->gameG, i, d, 1)) {
					if (game_over_hr(f->gameG))
						return game_nb_moves(f->gameG);
					if (existeConfig(f->gameG, t)) {
						push(t, f->gameG); // tester si la config n'existe pas deja.
						enfiler(f, f->gameG);
					}
				}

			}
			
		}
		defiler(f);
	}
	return game_nb_moves(g);// je sais pas
}



int main(void) {
	piece pieces[NB_PIECES];
	pieces[0] = new_piece_rh(2, 0, true, true);
	
	game jeuSolveur = new_game_hr(1, pieces);
	printf("hello\n");
	int nbmv = solv(jeuSolveur);
	printf("Jeu en %d coup", nbmv);
	return EXIT_SUCCESS;
}