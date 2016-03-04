#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "piece.h"

void display_game(cgame g) { /* la fonction affiche le jeu dans le terminal */
	char grid[6][6]; /* on créé un tableau à deux dimensions qui représente notre plateau de jeu */
	
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			grid[i][j] ='.';
		}
	}

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

<<<<<<< HEAD
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


int main()
{
	piece *pieces_test = malloc(sizeof(struct piece_s)*4); /* on créé un tableau qui contient les pièces */
=======
/*
void lisa_prompt() {
	display_game(g);
	char tmp[6] = "";
	printf("Quelle piece voulez-vous jouer ? Rentrez son numéro. \n");
	int number_piece = atoi(fgets(tmp, sizeof(tmp), stdin));
	printf("Vous avez choisi la piece %d. De combien de cases voulez-vous la bouger ? Entrez un nombre entre 0 et 5. \n", number_piece);
	int distance = atoi(fgets(tmp, sizeof(tmp), stdin));
	printf("Vous voulez bouger la piece %d de %d cases. Dans quelle direction voulez-vous la bouger ? UP, DOWN, LEFT ou RIGHT ? \n", number_piece, distance);
	fgets(tmp, sizeof(tmp), stdin);
}
*/

/*
* @brief fonction permettant d'enlever la possible pollution du buffer lors de la saisie de caracteres.
*/

void clear_buffer() {
	int i;
	printf("Veuillez confirmer votre choix <ENTER>");//pas de vraie confirmation (juste pour combler le vide lors du nettoyage du buffer )
	while (i != '\n' && i != EOF) // il faut que l'utilisateur appuye sur ENTER.
		i = getchar();
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
	clear_buffer();
	return result;
}


int main(){
	piece *pieces_test = malloc(sizeof(struct piece_s)*5); /* on créé un tableau qui contient les pièces */
>>>>>>> 02bb8025da1f6dfc6f4c8e5b88ef364cd85dc69b
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
		int number_piece = 0;
		display_game(g);
		int size = 6;
		char * anwser = malloc(sizeof(char)*size) ;		
		printf("Quelle piece voulez-vous jouer ? Rentrez son numéro. \n");
<<<<<<< HEAD
		number_piece = atoi(fgets(tmp, sizeof(tmp), stdin));
		printf("Vous avez choisi la piece %d. De combien de cases voulez-vous la bouger ? Entrez un nombre entre 0 et 5. \n", number_piece);		
		int distance = atoi(fgets(tmp, sizeof(tmp), stdin));		
		printf("Vous voulez bouger la piece %d de %d cases. Dans quelle direction voulez-vous la bouger ? UP, DOWN, LEFT ou RIGHT ? \n", number_piece, distance);
		scanf("%s", tmp);
		move(tmp, g, number_piece, distance);
		for (int i=0;i<6;i++)
		{
			tmp[i]='\0';
=======
		int number_piece = atoi(scan(anwser, size));
		printf("Vous avez choisi la piece %d. De combien de cases voulez-vous la bouger ? Entrez un nombre entre 0 et 5. \n", number_piece);
		int distance = atoi(scan(anwser, size));
		printf("Vous voulez bouger la piece %d de %d cases. Dans quelle direction voulez-vous la bouger ? UP, DOWN, LEFT ou RIGHT ? \n", number_piece, distance);
		anwser = scan(anwser, size);
		if (strcmp(anwser, "RIGHT") == 0)
		{
			printf("Vous voulez bouger la piece %d de %d cases vers la droite. \n", number_piece, distance);
			play_move(g, number_piece, RIGHT, distance);
		}
		else if (strcmp(anwser, "LEFT") == 0)
		{
			printf("Vous voulez bouger la piece %d de %d cases vers la gauche. \n", number_piece, distance);
			play_move(g, number_piece, LEFT, distance);
		}
		else if (strcmp(anwser, "UP") == 0)
		{
			printf("Vous voulez bouger la piece %d de %d cases vers le haut. \n", number_piece, distance);
			play_move(g, number_piece, UP, distance);
		}
		else if (strcmp(anwser, "DOWN") == 0)
		{
			printf("Vous voulez bouger la piece %d de %d cases vers le bas. \n", number_piece, distance);
			play_move(g, number_piece, DOWN, distance);
		}
		else
		{
			printf("Merci d'entrer une direction valide. UP, DOWN, RIGHT ou LEFT \n");
>>>>>>> 02bb8025da1f6dfc6f4c8e5b88ef364cd85dc69b
		}
		free(anwser);
	}
	for (int i = 0; i < 5; i++)
		delete_piece(pieces_test[i]);
	delete_game(g);

	return EXIT_SUCCESS;
}
