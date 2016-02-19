#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "piece.h"
#include "piece.c"
#include "game.c"

typedef struct game_s* game;

int main()
{
	piece tableau[4];
	for (int i=0; i<3; i++)
	{
		piece p;
		p->x = i;
		p->y = i+2;
		p->small = true;
		p->horizontal = true;
		tableau[i] = p;
	}
	game g = new_game_hr(3, tableau);
	int nb = g->nb_pieces;
	printf("%d", nb);
	exit(EXIT_SUCCESS);
}


