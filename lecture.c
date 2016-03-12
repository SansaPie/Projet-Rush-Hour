#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "piece.c"
#include "game.c"
#define NB_PIECE_TEST_RH 5

// Fonction lecture de fichier pour une configuration de n'importe quel type 
// coordonnée x / coordonnée y / bool move_x / bool move_y / largeur / hauteur

void lecture(piece pieces_test[], int * n);
void lecture_rh(piece pieces_test[], int * n);

int number_pieces; // nombre de pièces
int c_x;	   // coordonnée x
int c_y;	   // coordonnée y
int m_x;	   // bool move_x
int m_y;	   // bool move_y
int w;		   // int largeur
int h;		   // int hauteur

int main(void)
{
	piece * pieces_test = NULL;
	pieces_test = allocation_piece_tab(NB_PIECE_TEST_RH, "main"); /* on cree un tableau qui contient les pieces */
	int n = 0;
	lecture(pieces_test, &n);
	for (int x=0; x<n; x++)
	{
		printf("%d %d %d %d %d %d \n", pieces_test[x]->x,  pieces_test[x]->y,  pieces_test[x]->move_x,  pieces_test[x]->move_y,  pieces_test[x]->width,  pieces_test[x]-> height);
	}
	return EXIT_SUCCESS;
}

void lecture(piece pieces_test[], int * n) {
	FILE *entree;
	entree = fopen("configurations.txt", "r+");
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







