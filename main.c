#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "piece.h"

/*
* @brief fonction affichant le jeu dans le terminal
*
*/

void display_game(cgame g) {
	char grid[6][6]; /* on créé un tableau à deux dimensions qui représente notre plateau de jeu */
	/* initialisation de toutes les cases du tableau precedement creer avec des '.' */
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			grid[i][j] ='.';
		}
	}
	/* Replissage du tableau avec les pieces de g */
	for (int i = 0; i < game_nb_pieces(g); i++){

		int xCoordDisplay = get_x(game_piece(g,i));
		int yCoordDisplay = 5-get_y(game_piece(g,i));

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
	
	/* affichage du tableau remplit */
	for (int x = 0; x<6; x++) {
		for (int y = 0; y<6; y++) {
			printf("%c ", grid[y][x]);
		}
		printf("\n");
	}
}

/*
* @brief fonction testant si le mouvement choisi par l'utilisateur est possible ou non.
*
*/

void display_success_movement(game g, int number_piece, int distance, dir d){
	if(play_move(g, number_piece, d, distance)){
		printf("Vous avez bouge la piece %d de %d cases vers ", number_piece, distance);
		if(d==RIGHT)
			printf("la droite.\n");
		else if(d==LEFT)
			printf("la gauche.\n");
		else if(d==UP)
			printf("le haut.\n");
		else
			printf("le bas.\n");
	}else
		printf("Mouvement impossible.\n");
}

/*
* @brief fonction permettant de bouger la piece dans la direction et la distance choisie.
*
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


/*
* @brief demande a l'utilisateur de saisir une chaine de caractere et de confirmer en appuyant sur "ENTER"
* @return la chaine de caractere saisie
*/

char * scan(char * buffer , int size) {
	char * result = fgets(buffer, size, stdin);
	/* on cherche dans la chaine de caractere saisie le caractere d'echappement pour le remplacer par un 
	* caractere de fin de fichier. */
	if ( result != NULL) {
		char * lresult = strchr(buffer, '\n');
		if (lresult != NULL)
			*lresult = '\0';
	}
	rewind(stdin); // on se place au debut de stdin
	return result;
}


int main(){
	piece *pieces_test = malloc(sizeof(struct piece_s)*5); /* on créé un tableau qui contient les pièces */
	if(pieces_test==NULL){ /* on vérifie que ce tableau a bien été alloué */
		fprintf(stderr,"main : pieces_test non alloue\n");
		exit(EXIT_FAILURE);
	}
	/* creation des pieces */
	pieces_test[0] = new_piece_rh(0,3,true,true);
	pieces_test[1] = new_piece_rh(0,0,false,true);
	pieces_test[2] = new_piece_rh(1,1,false,true);
	pieces_test[3] = new_piece_rh(3,3,false,false);
	pieces_test[4] = new_piece_rh(4,4,true,false);
	game g = new_game_hr(5, pieces_test); /* initialisation d'un premier jeu */

	/* teste si la position des pieces est conforme */
	if(!game_valid(g)){
		fprintf(stderr, "main : game invalid\n");
		exit(EXIT_FAILURE);
	}else{
		printf("Le jeu est valide.\n");
	}

	while(!game_over_hr(g)){ /* tant que le jeu n'est pas fini, on demande à l'utilisateur ce qu'il veut jouer */
		display_game(g);
		int size = 6;
		char * answer = malloc(sizeof(char)*size) ;		
		printf("Quelle piece voulez-vous jouer ? Rentrez son numéro. \n");
		int number_piece = atoi(scan(answer, size));
		printf("Vous avez choisi la piece %d. De combien de cases voulez-vous la bouger ?" 
				"Entrez un nombre entre 0 et 4. \n", number_piece);
		int distance = atoi(scan(answer, size));
		printf("Vous voulez bouger la piece %d de %d cases.\n", number_piece, distance);
		move(g, number_piece, distance);
		free(answer);
	}
	
	delete_pieces(5, pieces_test);
	delete_game(g);

	return EXIT_SUCCESS;
}
