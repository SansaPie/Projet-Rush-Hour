#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "game.h"
#include "game1.h"
#include "piece.h"
#include "piece1.h"
#include <string.h>
#include "ane_rouge.c"
#include "rush_hour.c"

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
	for (int y = game_height(g)-1; y>=0; y--) {
		for (int x = 0; x<game_width(g); x++) {
			printf("%c ", grid[x][y]);
		}
		printf("\n");
	}
	printf("\n");
	delete_char_matrix(grid, game_width(g));
}

/**
 * @brief tests if the movement is possible, and if so, execute it.
 * @param piece_played index in the game of the piece we want to move.
 * @param distance : number of cases we want to move the piece.
 * @param d direction of the move.
 */
void display_success_movement(game g, int piece_played, int distance, dir d){
	if(g==NULL || piece_played<0 || piece_played>=game_nb_pieces(g)){
		fprintf(stderr, "display_success_movement : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	if(play_move(g, piece_played, d, abs(distance))){
		printf("Vous avez bouge la piece %d de %d cases vers ", piece_played, abs(distance));
		if(d==RIGHT)
			printf("la droite.\n\n");
		else if(d==LEFT)
			printf("la gauche.\n\n");
		else if(d==UP)
			printf("le haut.\n\n");
		else
			printf("le bas.\n\n");
	}else
		printf("Mouvement impossible.\n");
}

int main(){
	int size = 30;
	int n = 0;
	piece * pieces_test = NULL;
	char * answer = malloc(sizeof(char)*size);
	char playing_game = 'O';

	/**
	 * loop allowing the user to play as many game as he wants.
	 */
	while(playing_game=='O' || playing_game=='o'){
		int choice = -1;
		bool condition = true;
		game g = NULL;

		printf("\nA quel jeu souhaitez-vous jouer ?\n1. Rush-hour\n2. Ane rouge\n");
		while(condition){
			choice = atoi(scan(answer, size));
			condition = (choice!=1 && choice!=2);
			if(condition)
				printf("Veuillez selectionner un numero de jeu correct.\n");
		}
		if(choice == 1){
			printf("La liste des configurations disponibles est : \n"
				"	1. easy_rh_1.txt\n"
				"	2. easy_rh_2.txt\n"
				"	3. normal_rh_1.txt \n"
				" 	4. normal_rh_2.txt \n"
				" 	5. difficult_rh_1.txt \n"
				"	6. difficult_rh_2.txt \n"
				"\nEntrez le numero de la configuration que vous souhaitez utiliser.\n"
				"Si vous souhaitez utiliser votre propre configuration, tapez 0.\n"
				"Veillez avant cela a bien avoir placer votre .txt dans le dossier config du jeu.\n");
			choice = -1;
			condition = true;
			while(condition){
				choice = atoi(scan(answer, size));
				condition = (choice<0 || choice>6);
				if(condition)
					printf("Veuillez selectionner un numero de configuration correcte.\n");
			}
			g = choice_config_rh(pieces_test, &n, choice, answer, size); // initialization of the game.
			rush_hour(answer, size, g);
		}
		else{
			printf("La liste des configurations disponibles est : \n"
				"	1. easy_ar_1.txt\n"
				"	2. normal_ar_1.txt\n"
				"	3. difficult_ar_1.txt\n"
				"	4. difficult_ar_2.txt\n"
				"\nEntrez le numero de la configuration que vous souhaitez utiliser.\n");
			choice = 0;
			condition = true;
			while(condition){
				choice = atoi(scan(answer, size));
				condition = (choice<1 || choice>4);
				if(condition)
					printf("Veuillez selectionner un numero de configuration correcte.\n");
			}
			g = choice_config_ar(pieces_test, &n, choice, answer, size); // initialization of the game.
			ane_rouge(answer, size, g);
		}
		printf("\nFelicitations : vous avez battu le jeu en %d coups !\n", g->moves);
		delete_game(g);

		printf("\nSouhaitez-vous rejouer ? (O/N)\n");
		condition = true;
		while(condition){
			answer = scan(answer, size);
			playing_game = answer[0];
			condition = (playing_game!='O' && playing_game!='N' && playing_game!='o' && playing_game!='n');
			if(condition)
				printf("Veuillez entrer la lettre O ou N.\n");
		}
	}
	free(answer);
	return EXIT_SUCCESS;
}