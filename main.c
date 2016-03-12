//////////////////////////////////////////////////////////// Rajout de ASSERT a faire ////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "game.h"
#include "piece.h"
#include "math.h"

#define NB_PIECE_TEST_RH 5

/**
 * @brief fonction affichant le jeu dans le terminal
 * 
 */

void display_game(cgame g) {
	char grid[L_RH][H_RH]; /* on crée un tableau à deux dimensions qui représente notre plateau de jeu */
	/* initialisation de toutes les cases du tableau precedement creer avec des '.' */
	for (int i = 0; i < L_RH; i++) {
		for (int j = 0; j < H_RH; j++) {
			grid[i][j] ='.';
		}
	}
	/* Remplissage du tableau avec les pieces de g */
	for (int i = 0; i < game_nb_pieces(g); i++){

		int xCoordDisplay = get_x(game_piece(g,i));
		int yCoordDisplay = (H_RH-1)-get_y(game_piece(g,i));

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
	for (int x = 0; x<L_RH; x++) {
		for (int y = 0; y<H_RH; y++) {
			printf("%c ", grid[y][x]);
		}
		printf("\n");
	}
	printf("\n");
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

void move(game g, int number_piece, int distance)
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

void rush_hour(char * answer, int size){
	piece * pieces_test = NULL;
	pieces_test = allocation_piece_tab(NB_PIECE_TEST_RH, "rush_hour"); /* on cree un tableau qui contient les pieces */
	
	/* creation des pieces */
	pieces_test[0] = new_piece_rh(0,3,true,true);
	pieces_test[1] = new_piece_rh(0,0,true,true);
	pieces_test[2] = new_piece_rh(1,1,false,true);
	pieces_test[3] = new_piece_rh(3,3,false,false);
	pieces_test[4] = new_piece_rh(4,4,true,false);
	game g = new_game_hr(NB_PIECE_TEST_RH, pieces_test); /* initialisation d'un premier jeu */

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
		while(number_piece<0 || number_piece>game_nb_pieces(g)){
			printf("Quelle piece voulez-vous jouer ? Rentrez son numero.\n");
			number_piece = atoi(scan(answer, size));
			if(number_piece<0 || number_piece>game_nb_pieces(g))
				printf("Veuillez rentrer un numero de piece existant. (0 a %d)\n", game_nb_pieces(g));
		}
		printf("Vous avez choisi la piece %d. De combien de cases voulez-vous la bouger ?\n"
			, number_piece);
		int distance = H_RH;
		while(distance<-4 || distance>4){
			distance = atoi(scan(answer, size));
			if(distance<-4 || distance>4)
				printf("Veuillez rentrer une distance valide. (-4 a 4)\n");
		}
		move(g, number_piece, distance);
	}

	display_game(g);
	printf("\nFelicitations : vous avez battu le jeu en %d coups !\n", g->moves);
	
	delete_pieces(NB_PIECE_TEST_RH, pieces_test);
	delete_game(g);
}

void ane_rouge(char * answer, int size){
	piece * pieces_test = NULL;
	pieces_test = allocation_piece_tab(7, "ane_rouge");

	/*creation des pieces
	...
	*/
	game g = new_game(7, 7, 7, pieces_test);

	if(!game_valid(g)){
		fprintf(stderr, "ane_rouge : g non valide\n");
		exit(EXIT_FAILURE);
	}

	delete_game(g);
	delete_pieces(7, pieces_test);
}

// Chercher comment factoriser au mieux le main
int main(){
	int size = 6;
	char * answer = malloc(sizeof(char)*size);
	printf("A quel jeu souhaitez-vous jouer ?\n1. Rush-hour\n2. Ane rouge\n");

	int choix = -1;
	while(choix!=1 && choix!=2){
		choix = atoi(scan(answer, size));
		if(choix!=1&&choix!=2)
			printf("Veuillez selectionner un numero de jeu correct.\n");
	}
	if(choix == 1)
		rush_hour(answer, size);
	else
		ane_rouge(answer, size);

	free(answer);
	return EXIT_SUCCESS;
}