#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game1.h"
#include "piece.h"

#define NB_PIECES 2
#define SIZE_TAS 15
#define INIT_INDEX_TAS 0

typedef struct Maillon{
	game gameG;
	struct Maillon *next;
}*maillon;

typedef struct File{
	maillon premier;
	maillon dernier;
}*file;

typedef struct Tas{
	int capacite;
	int index;
	game *tab;
}*tas;

void usage(char * commande){
	fprintf(stderr, "usage : %s \npremier argument : char 'a' ou 'r' \nsecond argument : char * (fichier .txt)\n"
		, commande);
	exit(EXIT_FAILURE);
}

/**
 * @brief function allowing the reading of pieces features from an annexed file.
 */
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

// Temporaire

/**
 * @brief allocates a char matrix.
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
 * @brief deletes a char matrix.
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
void display_game(cgame g){
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
	for (int i = 0; i < game_width(g); i++){
		for (int j = 0; j < game_height(g); j++){
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
	for (int y = game_height(g)-1; y>=0; y--){
		for (int x = 0; x<game_width(g); x++){
			printf("%c ", grid[x][y]);
		}
		printf("\n");
	}
	printf("\n");
	delete_char_matrix(grid, game_width(g));
}

void display_game_in_file(file f){
	int i=0;
	maillon tmp = f->premier;
	while(tmp!=NULL){
		printf("\n\n\n%d : \n", i);
		display_game(tmp->gameG);
		i++;
		tmp = tmp->next;
	}
}

// Temporaire

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
	f->dernier = NULL;
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

void defiler(file f){
	if (f != NULL){
		if(f->premier==f->dernier){
			delete_game(f->premier->gameG);
			free(f->premier);
			f->premier = NULL;
			f->dernier = NULL;
		}
		else{
			maillon tmp = f->premier;
			while(tmp->next != f->dernier){
				tmp = tmp->next;
			}
			delete_game(tmp->next->gameG);
			free(tmp->next);
			f->dernier = tmp;
			f->dernier->next = NULL;
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
	for (int i = 0; i < t->index; i++){
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
	if(game_type=='a')
		return game_over_ar(f->dernier->gameG);
	else
		return game_over_hr(f->dernier->gameG); 
}

file solv(game g, char game_type){
	file f = new_file();
	tas t = new_tas(SIZE_TAS);
	enfiler(f, g); 
	if (game_over_hr(g))
		return f;
	push(t, g);

	piece * t_pieces = allocation_piece_tab(1, "solv");
	t_pieces[0] = new_piece(1,1,1,1,true,true);
	game tmp = new_game(game_width(g), game_height(g), 1, t_pieces);
	
	maillon tmp_f = f->premier;
	bool move_played = false;

	while (tmp_f != NULL && !game_over(game_type, f)){
		for (int i = 0; i < game_nb_pieces(g); i++){
			for (dir d = UP; d <= RIGHT; d++){
				enfiler(f, tmp_f->gameG);
				copy_game(f->dernier->gameG, tmp);
				while(play_move(f->dernier->gameG, i, d, 1) && !equals(f->dernier->gameG, tmp)){
					if(move_played){
						enfiler(f, f->dernier->gameG);
						copy_game(f->dernier->gameG, tmp);
					}
					if (!is_config(f->dernier->gameG, t))
						push(t, f->dernier->gameG);
					else
						defiler(f);
					move_played = true;
				}
				if(!move_played)
					defiler(f);
				else
					move_played=false;
			}
			if(game_over(game_type, f))
				break;
		}
		tmp_f = tmp_f->next;
	}
	free_tas(t);
	delete_pieces(1, t_pieces);
	delete_game(tmp);
	return f;
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

	file moves_to_display = solv(game_for_solveur, argv[1][0]);
	//display_game_in_file(moves_to_display); // temporaire
	printf("Jeu termine en %d coups.\n", game_nb_moves(moves_to_display->dernier->gameG));
	free_file(moves_to_display);

	delete_pieces(nb_pieces, pieces_from_file);
	delete_game(game_for_solveur);

	fclose(entree);
	return EXIT_SUCCESS;
}