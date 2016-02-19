#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "piece.h" // Si on inclut les .h, pas besoin d'inclure les .c

int main()
{
	piece tableau[4];
	for (int i=0; i<3; i++)
	{
		piece p = NULL;
		new_piece_rh(i, i+2, true, true);
		tableau[i] = p;
	}
	game g = new_game_hr(3, tableau);
	int nb = g->nb_pieces;
	printf("%d", nb);
	return 1;
}


