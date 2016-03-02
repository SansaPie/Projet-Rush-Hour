#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "piece.h" 

void afficher_piece(piece p);

int main()
{
	piece test2 = new_piece_rh(5,5,true,false);
	piece test = new_piece_rh(6,6,false, true);
	afficher_piece(test);
	afficher_piece(test2);
	//copy_piece(test2, test);

	return EXIT_SUCCESS;
}

void afficher_piece(piece p)
{
	printf("x : %d \n", p->x);
	printf("y : %d \n", p->y);
	printf("small : %d \n", p->small);
	printf("horizontal : %d \n", p->horizontal);
}
