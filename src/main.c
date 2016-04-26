#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "game.h"
#include "game1.h"
#include "piece.h"
#include "piece1.h"
#include "intGraph.h"

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

/**
 * @brief asks the player to write a string.
 * @param buffer tab of char in which the string written by the player is stocked.
 * @param size width of the buffer.
 * @return string written.
 */
char * scan(char * buffer , int size){
	if(buffer==NULL || size<0){
		fprintf(stderr, "scan : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	char * result = fgets(buffer, size, stdin);
	if (result != NULL){
		char * lresult = strchr(buffer, '\n');
		if (lresult != NULL)
			*lresult = '\0';
	}
	rewind(stdin); 
	/*
	 * going back to the entrance flux.
	 */
	return result;
}

/**
 * @brief checks if the string s is a digital number
 */
bool expected_digit(char * s){
	int c = *s;
	if(c=='\n')
		return false;
	if(s[0]=='-' || s[0]=='+')
		s++;
	for(int i=0 ; i<strlen(s) ; i++){
		if(isdigit(s[i])==0)
			return false;
	}
	return true;
}

/**
 * @brief asks the user the name of the file he wants to play with.
 */
char * input_config_user(char * answer, int size){
	if(answer==NULL || size<0){
		fprintf(stderr, "input_config_user : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	char * config_user = malloc(strlen("../config/"));
	strcat(config_user, "../config/");	
	printf("Entrez le nom complet de votre fichier y compris son extension.\n");
	answer = scan(answer, size);
	config_user = realloc(config_user, strlen(config_user)+strlen(answer));
	strcat(config_user, answer);
	return config_user;
}

/**
 * @brief choice of the rush hour config.
 * @param pieces_test array of pieces which will be in the game.
 * @param n number of pieces in the game.
 * @param choice choice of the configuration by the user earlier in the program.
 */
game choice_config_rh(piece * pieces_test, int choice, char * answer, int size){
	if(answer==NULL || size<0){
		fprintf(stderr, "choice_config_rh : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	int n, width, height = 0;
	FILE *entree = NULL;
	switch(choice){
		case 0:;
			char * config_user = input_config_user(answer, size);
			entree = fopen(config_user, "r+");
			free(config_user);
			break;
		case 1:
			entree = fopen("../config/easy_rh_1.txt", "r+");
			break;
		case 2:
			entree = fopen("../config/easy_rh_2.txt", "r+");
			break;
		case 3:
			entree = fopen("../config/normal_rh_1.txt", "r+");
			break;
		case 4:
			entree = fopen("../config/normal_rh_2.txt", "r+");
			break;
		case 5:
			entree = fopen("../config/difficult_rh_1.txt", "r+");
			break;
		case 6:
			entree = fopen("../config/difficult_rh_2.txt", "r+");
			break;
		default:
			printf("choice_config : choix invalide.\n");
			break;
	}
	if (entree == NULL){
		fprintf(stderr, "Fichier non valide.\n");
		exit(EXIT_FAILURE);
	}
	pieces_test = lecture(pieces_test, &n, &width, &height, entree);
	game g = new_game(width, height, n, pieces_test); 
	/*
	 * the height and width are always the same for the rush hour game.
	 */
	fclose(entree);
	delete_pieces(n, pieces_test);
	return g;
}

/**
 * @brief same as choice_config_rh but with a game of ane_rouge.
 */
game choice_config_ar(piece * pieces_test, int choice, char * answer, int size){
	if(answer==NULL || size<0){
		fprintf(stderr, "choice_config_ar : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	int n, width, height = 0;
	FILE *entree = NULL;
	switch(choice){
		case 0:; // This ; stands for the prevention of a bug, it's not a typo
			char * config_user = input_config_user(answer, size);
			entree = fopen(config_user, "r+");
			free(config_user);
		case 1:
			entree = fopen("../config/easy_ar_1.txt", "r+");
			break;
		case 2:
			entree = fopen("../config/normal_ar_1.txt", "r+");
			break;
		case 3:
			entree = fopen("../config/difficult_ar_1.txt", "r+");
			break;
		case 4:
			entree = fopen("../config/difficult_ar_2.txt", "r+");
			break;
	}
	if (entree == NULL) {
		fprintf(stderr, "Fichier non valide.\n");
		exit(EXIT_FAILURE);
	}
	pieces_test = lecture(pieces_test, &n, &width, &height, entree);
	game g = new_game(width, height, n, pieces_test); 
	/*
	 * the height and the width are always the same for this game.
	 */
	fclose(entree);
	delete_pieces(n, pieces_test);
	return g;
}

int main(){
	int size = 30;
	piece * pieces_test = NULL;
	char * answer = malloc(sizeof(char)*size);
	char playing_game = 'O';
	char game_type = 'r';
	
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
			g = choice_config_rh(pieces_test, choice, answer, size); // initialization of the game.
			game_type = 'r';
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
				char * test = malloc(size);
				test = scan(answer, size);
				choice = atoi(test);
				condition = (!expected_digit(test) || choice<1 || choice>4);
				if(condition)
					printf("Veuillez selectionner un numero de configuration correcte.\n");
			}
			g = choice_config_ar(pieces_test, choice, answer, size); // initialization of the game.
			game_type = 'a';
		}
		graphic_game(g, game_type);
		if(game_over(g, game_type))
			printf("\nFelicitations : vous avez battu le jeu en %d coups !\n", g->moves);
		else
			printf("\nDommage, peut-etre une prochaine fois.\n");
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