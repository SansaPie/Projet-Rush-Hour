#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "piece.h"

/*
* @brief fonction affichant le jeu dans le terminal
*
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
	/* Replissage du tableau avec */
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
	
	for (int x = 0; x<6; x++) {
		for (int y = 0; y<6; y++) {
			printf("%c ", grid[y][x]);
		}
		printf("\n");
	}
}

void move(char *tmp, game g, int number_piece, int distance)
{
		char down[] = "DOWN";
		char right[] = "RIGHT";
		char left[] = "LEFT";
		char up[] = "UP";
		if (strcmp(tmp, right) ==0)
		{
			printf("Vous avez bougé la piece %d de %d cases vers la droite. \n", number_piece, distance);
			play_move(g, number_piece, RIGHT, distance);
		}
		else if (strcmp(tmp, left) ==0)
		{
			printf("Vous avez bougé la piece %d de %d cases vers la gauche. \n", number_piece, distance);
			play_move(g, number_piece, LEFT, distance);
		}
		else if (strcmp(tmp, up) ==0)
		{
			printf("Vous avez bougé la piece %d de %d cases vers le haut. \n", number_piece, distance);
			play_move(g, number_piece, UP, distance);
		}
		else if (strcmp(tmp, down) ==0)
		{
			printf("Vous avez bougé la piece %d de %d cases vers le bas. \n", number_piece, distance);
			play_move(g, number_piece, DOWN, distance);
		}
		else
		{
			printf("Merci d'entrer une direction valide. UP, DOWN, RIGHT ou LEFT \n");
		}
}


/*
* @brief demande a l'utilisateur de saisir une chaine de caractere et de confirmer en appuyant sur "ENTER"
* @return la chaine de caractere saisie
*/

char * scan(char * buffer , int size) {
	char * result = fgets(buffer, size, stdin);
	
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
	pieces_test[0] = new_piece_rh(0,3,true,true);
	pieces_test[1] = new_piece_rh(0,0,false,true);
	pieces_test[2] = new_piece_rh(1,1,false,true);
	pieces_test[3] = new_piece_rh(3,3,false,false);
	pieces_test[4] = new_piece_rh(4,4,true,false);
	game g = new_game_hr(5, pieces_test); /* initialisation d'un premier jeu */

	while(!game_over_hr(g)){ /* tant que le jeu n'est pas fini, on demande à l'utilisateur ce qu'il veut jouer */
		display_game(g);
		int size = 6;
		char * answer = malloc(sizeof(char)*size) ;		
		printf("Quelle piece voulez-vous jouer ? Rentrez son numéro. \n");
		int number_piece = atoi(scan(answer, size));
		printf("Vous avez choisi la piece %d. De combien de cases voulez-vous la bouger ? Entrez un nombre entre 0 et 5. \n", number_piece);
		int distance = atoi(scan(answer, size));
		printf("Vous voulez bouger la piece %d de %d cases. Dans quelle direction voulez-vous la bouger ? UP, DOWN, LEFT ou RIGHT ? \n", number_piece, distance);
		answer = scan(answer, size);
		if (strcmp(answer, "RIGHT") == 0)
		{
			printf("Vous voulez bouger la piece %d de %d cases vers la droite. \n", number_piece, distance);
			play_move(g, number_piece, RIGHT, distance);
		}
		else if (strcmp(answer, "LEFT") == 0)
		{
			printf("Vous voulez bouger la piece %d de %d cases vers la gauche. \n", number_piece, distance);
			play_move(g, number_piece, LEFT, distance);
		}
		else if (strcmp(answer, "UP") == 0)
		{
			printf("Vous voulez bouger la piece %d de %d cases vers le haut. \n", number_piece, distance);
			play_move(g, number_piece, UP, distance);
		}
		else if (strcmp(answer, "DOWN") == 0)
		{
			printf("Vous voulez bouger la piece %d de %d cases vers le bas. \n", number_piece, distance);
			play_move(g, number_piece, DOWN, distance);
		}
		else
		{
			printf("Merci d'entrer une direction valide. UP, DOWN, RIGHT ou LEFT \n");
		}
		free(answer);
	}
	
	delete_pieces(5, pieces_test);
	delete_game(g);

	return EXIT_SUCCESS;
}
