#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "piece.c"
#include "game.c"
#define NB_PIECE_TEST_RH 25  // nombre maximum de pièces dans le jeu


void lecture(piece pieces_test[], int * n, FILE * entree);

int number_pieces; // nombre de pièces
int c_x;	   // coordonnée x
int c_y;	   // coordonnée y
int m_x;	   // bool move_x
int m_y;	   // bool move_y
int w;		   // int largeur
int h;		   // int hauteur


// Fonction lecture de fichier pour une configuration de n'importe quel type 
// coordonnée x / coordonnée y / bool move_x / bool move_y / largeur / hauteur

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


void choix_config(piece pieces_test[], int * n, char * answer)
{
	printf("La liste des configurations disponibles est : \n"
		"	srgrgq.txt\n	sfnsdfi.txt\n	irnqgirgn.txt\n \nVeuillez recopier le nom du fichier que vous souhaitez utiliser. \n");
	scan(answer, 30);
	if (answer != NULL) 
	{ 
    		char * p = strchr(answer, '\n'); 
  
    		if (p != NULL) 
        	*p = 0; 
	}
	if (strcmp(answer, "easy_rh_1.txt") == 0)
	{
		FILE *entree = fopen("easy_rh_1.txt", "r+");
		lecture(pieces_test, n, entree);
	}
}


int main(void)
{
	int size = 30;
	char * answer = malloc(sizeof(char)*size);
	piece * pieces_test = NULL;
	pieces_test = allocation_piece_tab(NB_PIECE_TEST_RH, "main"); /* on cree un tableau qui contient les pieces */
	int n = 0;
	printf("La liste des configurations disponibles est : \n"
		"	srgrgq.txt\n	sfnsdfi.txt\n	irnqgirgn.txt\n \nVeuillez recopier le nom du fichier que vous souhaitez utiliser. \n");
	scan(answer, size);
	if (answer != NULL) 
	{ 
    		char * p = strchr(answer, '\n'); 
  
    		if (p != NULL) 
        	*p = 0; 
	}
	choix_config(pieces_test, &n, answer);
	// lecture(pieces_test, &n);
	for (int x=0; x<n; x++)
	{
		printf("%d %d %d %d %d %d \n", pieces_test[x]->x,  pieces_test[x]->y,  pieces_test[x]->move_x,  pieces_test[x]->move_y,  pieces_test[x]->width,  pieces_test[x]-> height);
	}
	return EXIT_SUCCESS;
}



void lecture(piece pieces_test[], int * n, FILE * entree) 
{
	if( entree == NULL )
	{
		printf("error when opening configurations.txt\n");
		exit(EXIT_FAILURE);
	}  
	fscanf(entree, "%d", &number_pieces);
	for(int i=0; i<number_pieces; i++)
	{
		fscanf(entree, "%d %d %d %d %d %d", &c_x, &c_y, &m_x, &m_y, &w, &h);
		pieces_test[i] = new_piece(c_x, c_y, w, h, m_x, m_y);
	}
	*n = number_pieces;
	fclose(entree);
}







