//////////////////////////////////////////////////////////// Rajout de ASSERT a faire ////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "game.h"
#include "game1.h"
#include "piece.h"
#include "piece1.h"
#include "math.h" // Vérifier si nécessaire

/**
 * @brief function allowing the reading of pieces features from an annexed file
 */
piece * lecture(piece * pieces_test, int * n, FILE * entree) {
	/* variables utilisées pour la lecture du fichier */

	int number_pieces;
	int c_x;	   // x-coor
	int c_y;	   // y-coor
	int m_x;	   // move_x
	int m_y;	   // move_y
	int w;		   // width
	int h;		   // height

	if( entree == NULL )
	{
		printf("error when opening the file\n");
		exit(EXIT_FAILURE);
	}  
	fscanf(entree, "%d", &number_pieces);
	pieces_test = allocation_piece_tab(number_pieces, "main"); /* on cree un tableau qui contient les pieces */
	for(int i=0; i<number_pieces; i++)
	{
		fscanf(entree, "%d %d %d %d %d %d", &c_x, &c_y, &m_x, &m_y, &w, &h);
		pieces_test[i] = new_piece(c_x, c_y, w, h, m_x, m_y);
	}
	*n = number_pieces;
	return pieces_test;
}

/**
 * @brief Allocates a char matrix
 */
char ** allocation_char_matrix(int width, int height){
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
 * @brief Deletes a char matrix
 */
void delete_char_matrix(char ** grid, int height){
	for(int i=0 ; i<height ; i++)
		free(grid[i]);
	free(grid);
}

/**
 * @brief function displaying game in terminal
 * 
 */
void display_game(cgame g) {
	/* on crée un tableau à deux dimensions qui représente notre plateau de jeu */
	char ** grid = allocation_char_matrix(game_width(g), game_height(g)); 
	/* initialisation de toutes les cases du tableau precedement creer avec des '.' */
	for (int i = 0; i < game_width(g); i++) {
		for (int j = 0; j < game_height(g); j++) {
			grid[i][j] ='.';
		}
	}
	/* Remplissage du tableau avec les pieces de g */
	for (int i = 0; i < game_nb_pieces(g); i++){

		int xCoordDisplay = get_x(game_piece(g,i));
		int yCoordDisplay = (game_height(g)-1)-get_y(game_piece(g,i));

		grid[xCoordDisplay][yCoordDisplay] = i + '0';
		if (!is_horizontal(game_piece(g,i))) {
			grid[xCoordDisplay][yCoordDisplay -1] = i + '0';
			if (!is_small(game_piece(g, i)))
				grid[xCoordDisplay][yCoordDisplay - 2] = i + '0';
		}
		else {
			grid[xCoordDisplay + 1][yCoordDisplay] = i + '0';
			if (!is_small(game_piece(g, i)))
				grid[xCoordDisplay + 2][yCoordDisplay] = i + '0';	
		}
	}
	
	/* affichage du tableau rempli */
	for (int x = 0; x<game_width(g); x++) {
		for (int y = 0; y<game_height(g); y++) {
			printf("%c ", grid[y][x]);
		}
		printf("\n");
	}
	printf("\n");
	delete_char_matrix(grid, game_height(g));
}

/**
 * @brief fonction testant si le mouvement choisi par l'utilisateur est possible ou non et 
 * l'executant dans le cas s'il est valide.
 * @param number_piece index dans le jeu de la piece que l'on souhaite bouger.
 * @param distance nombre de case dont on souhaite se deplacer.
 * @param d direction dans laquelle on souhaite se deplacer.
 */

void display_success_movement(game g, int number_piece, int distance, dir d){
	if(play_move(g, number_piece, d, abs(distance))){
		printf("Vous avez bouge la piece %d de %d cases vers ", number_piece, abs(distance));
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

/**
 * @brief fonction permettant de bouger la piece dans la direction et la distance choisies.
 * @param number_piece index dans le jeu de la piece que l'on va bouger.
 * @param distance direction dans laquelle on va bouger la piece.
 */

void move_rh(game g, int number_piece, int distance)
{
	if(distance>0){
		if(is_horizontal(game_piece(g, number_piece)))
			display_success_movement(g, number_piece, distance, RIGHT);
		else
			display_success_movement(g, number_piece, distance, UP);
	}else{
		if(is_horizontal(game_piece(g, number_piece)))
			display_success_movement(g, number_piece, distance, LEFT);
		else
			display_success_movement(g, number_piece, distance, DOWN);
	}
}

void move_ar(game g, int number_piece, int distance, dir direction){// A coder

}

/**
 * @brief demande a l'utilisateur de saisir une chaine de caractere.
 * @param buffer chaine de caractere dans laquelle on stocke la valeur saisie par l'utilisateur.
 * @param size taille de la chaine de caractere buffer.
 * @return chaine de caractere saisie
 */

char * scan(char * buffer , int size) {
	char * result = fgets(buffer, size, stdin);
	/* on cherche dans la chaine de caractere saisie le caractere d'echappement pour le remplacer par un 
	 caractere de fin de fichier. */
	if ( result != NULL) {
		char * lresult = strchr(buffer, '\n');
		if (lresult != NULL)
			*lresult = '\0';
	}
	rewind(stdin); /* on se place au debut du flux d'entree */
	return result;
}

/**
 * @brief Cette fonction permet le choice de la configuration de jeux rush-hour parmi une liste donnée
 *
 */
game choice_config_rh(piece * pieces_test, int * n, int choice)
{
	FILE *entree = NULL;
	switch(choice){
		case 1:
			entree = fopen("config/easy_rh_1.txt", "r+");
			break;
		case 2:
			entree = fopen("config/easy_rh_2.txt", "r+");
			break;
		case 3:
			entree = fopen("config/normal_rh_1.txt", "r+");
			break;
		case 4:
			entree = fopen("config/normal_rh_2.txt", "r+");
			break;
		case 5:
			entree = fopen("config/difficult_rh_1.txt", "r+");
			break;
		case 6:
			entree = fopen("config/difficult_rh_2.txt", "r+");
			break;
		default:
			printf("choice_config : choice invalid\n");
			break;
	}
	pieces_test = lecture(pieces_test, n, entree);
	game g = new_game(6,6,*n, pieces_test); // La taille du tableau est unique au Rush-Hour
	fclose(entree);
	delete_pieces(*n, pieces_test);
	return g;
}

void rush_hour(char * answer, int size, game g){
	/* teste si la position des pieces est conforme */
	if(!game_valid(g)){
		fprintf(stderr, "rush_hour : game invalid\n");
		exit(EXIT_FAILURE);
	}

	/* affichage des regles du jeu */
	printf("Ce jeu a ete code par Lucas, Lisa et Clement. \n"
		"Le but de ce jeu est d'amener la voiture 0 toucher le cote droit du plateau.\n"
		"Vous ne pouvez bouger les pieces horizontales que de gauche a droite, "
		"et les verticales que de haut en bas. \n"
		"Un nombre negatif fera bouger une voiture horizontale a gauche, "
		"un nombre positif la fera bouger a droite.\n"
		"Un nombre negatif fera bouger une voiture verticale vers le bas, "
		"et un nombre positif la fera bouger vers le haut.\n"
		"Essayez de resoudre ce puzzle en un minimum de coups possible !\n\n");

	while(!game_over_hr(g)){ /* tant que le jeu n'est pas fini, on demande a l'utilisateur ce qu'il veut jouer */
		display_game(g);
		int number_piece = -1;
		bool condition = true;
		while(condition){
			printf("Quelle piece voulez-vous jouer ? Rentrez son numero.\n");
			number_piece = atoi(scan(answer, size));
			condition = (number_piece<0 || number_piece>game_nb_pieces(g));
			if(condition)
				printf("Veuillez rentrer un numero de piece existant. (0 a %d)\n", game_nb_pieces(g));
		}
		printf("Vous avez choisi la piece %d. De combien de cases voulez-vous la bouger ?\n"
			, number_piece);
		int distance = game_height(g);
		condition = true;
		while(condition){
			distance = atoi(scan(answer, size));
			condition = (abs(distance)>=(game_height(g)-1) || abs(distance)>=(game_width(g)-1));
			if(condition)
				printf("Veuillez rentrer une distance valide.\n");
		}
		move_rh(g, number_piece, distance);
	}

	display_game(g);
	printf("\nFelicitations : vous avez battu le jeu en %d coups !\n", g->moves);
	
	delete_game(g);
}

game choice_config_ar(piece * pieces_test, int * n, int choice){
	FILE *entree = NULL;
	switch(choice){
		case 1:
			entree = fopen("config/easy_ar_1.txt", "r+");
			break;
	}
	pieces_test = lecture(pieces_test, n, entree);
	game g = new_game(4,5,*n, pieces_test); // La taille du tableau est unique à l'Âne Rouge
	fclose(entree);
	delete_pieces(*n, pieces_test);
	return g;
}

void ane_rouge(char * answer, int size){
	/* teste si la position des pieces est conforme */
	if(!game_valid(g)){
		fprintf(stderr, "ane_rouge : game invalid\n");
		exit(EXIT_FAILURE);
	}

	/* affichage des regles du jeu */
	printf("Ce jeu a ete code par Lucas, Lisa et Clement. \n"
		"Le but de ce jeu est d'amener la piece 0 en bas du plateau.\n"
		"Vous pouvez bouger les pieces horizontalement et verticalement.\n"
		"Essayez de resoudre ce puzzle en un minimum de coups possible !\n\n");

	while(!game_over_hr(g)){ /* tant que le jeu n'est pas fini, on demande a l'utilisateur ce qu'il veut jouer */
		display_game(g);
		int number_piece = -1;
		bool condition = true;
		while(condition){
			printf("Quelle piece voulez-vous jouer ? Rentrez son numero.\n");
			number_piece = atoi(scan(answer, size));
			condition = (number_piece<0 || number_piece>game_nb_pieces(g));
			if(condition)
				printf("Veuillez rentrer un numero de piece existant. (0 a %d)\n", game_nb_pieces(g));
		}
		printf("Vous avez choisi la piece %d. De combien de cases voulez-vous la bouger ?\n"
			, number_piece);
		int distance = game_height(g);
		condition = true;
		while(condition){
			distance = atoi(scan(answer, size));
			condition = (abs(distance)>=(game_height(g)-1) || abs(distance)>=(game_width(g)-1));
			if(condition)
				printf("Veuillez rentrer une distance valide.\n");
		}
		//Coder pour prendre en compte la direction
		move_ar(g, number_piece, distance, direction);
	}

	display_game(g);
	printf("\nFelicitations : vous avez battu le jeu en %d coups !\n", g->moves);
	
	delete_game(g);
}

// Chercher comment factoriser au mieux le main
int main(){
	int size = 30;
	int n = 0;
	piece * pieces_test = NULL;

	char * answer = malloc(sizeof(char)*size);
	printf("A quel jeu souhaitez-vous jouer ?\n1. Rush-hour\n2. Ane rouge\n");

	int choice = -1;
	bool condition = true;
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
			"\nEntrez le numero de la configuration que vous souhaitez utiliser.\n");
		choice = 0;
		condition = true;
		while(condition){
			choice = atoi(scan(answer, size));
			condition = (choice<1 || choice>6);
			if(condition)
				printf("Veuillez selectionner un numero de configuration correcte.\n");
		}
		game g = choice_config_hr(pieces_test, &n, choice); // initialisation du jeu
		rush_hour(answer, size, g);
	}
	else{
		printf("La liste des configurations disponibles est : \n"
			"	1. easy_ar_1.txt\n"
			"\nEntrez le numero de la configuration que vous souhaitez utiliser.\n");
		choice = 0;
		condition = true;
		while(condition){
			choice = atoi(scan(answer, size));
			condition = (choice<1 || choice>1);
			if(condition)
				printf("Veuillez selectionner un numero de configuration correcte.\n");
		}
		game g = choice_config_ar(pieces_test, &n, choice); // initialisation du jeu
		ane_rouge(answer, size);
	}
	free(answer);
	return EXIT_SUCCESS;
}