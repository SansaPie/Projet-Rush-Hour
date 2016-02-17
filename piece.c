#include <stdlib.h>
#include <stdio.h>
#include "piece.h"

typedef struct piece_s*{
	int x;
	int y;
	bool small;
	bool horizontal;
} piece;

typedef struct const struct piece_s*{
	piece cPiece;
} cpiece;

typedef enum dir_e {UP,LEFT,DOWN,RIGHT} dir;

piece new_piece_rh (int x, int y, bool small, bool horizontal){
	if(x<0 || y<0)
		exit(EXIT_FAILURE);
	piece p = malloc(sizeof(struct piece));
	p->x = x;
	p->y = y;
	p->small = small;
	p->horizontal = horizontal; 
	return p;
}

void delete_piece (piece p){
	if(p!=NULL)
		free(p);
}

void copy_piece (cpiece src, piece dst){
	if(src==NULL || dst==NULL)
		exit(EXIT_FAILURE);
	dst->x = src->x;
	dst->y = src->y;
	dst->small = src->small;
	dst->horizontal = src->horizontal;
}

void move_piece (piece p, dir d, int distance){
	if(p==NULL || distance<0)
		exit(EXIT_FAILURE);
	switch(d){
		case LEFT:
			if(y+distance<=6)
				y+=distance;
		case RIGHT:
			if(y-distance>=0)
				y-=distance;
		case TOP:
			if(x+distance<=6)
				x+=distance;
		case BOTTOM:
			if(x-distance>=0)
				x-=distance;
	}
}