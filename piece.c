#include <stdlib.h>
#include <stdio.h>
#include "piece.h"

int main()
{
	return 1;
}

piece new_piece_rh (int x, int y, bool small, bool horizontal){
	if(x<0 || y<0 || x>5 || y>5)
		exit(EXIT_FAILURE);
	piece p = malloc(sizeof(struct piece_s));
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
	dst->x = src->cPiece->x;
	dst->y = src->cPiece->y;
	dst->small = src->cPiece->small;
	dst->horizontal = src->cPiece->horizontal;
}

void move_piece (piece p, dir d, int distance){
	if(p==NULL || distance<0)
		exit(EXIT_FAILURE);
	switch(d){
		case LEFT:
			if(p->y+distance<=5 && p->horizontal)
				p->y+=distance;
		case RIGHT:
			if(p->y-distance>=0 && p->horizontal)
				p->y-=distance;
		case UP:
			if(p->x+distance<=5 && !p->horizontal)
				p->x+=distance;
		case DOWN:
			if(p->x-distance>=0 && !p->horizontal)
				p->x-=distance;
	}
}

bool intersect(cpiece p1, cpiece p2){
	if (p1==NULL || p2==NULL)
		exit(EXIT_FAILURE);

	bool tmp[6][6];
	tmp[p1->cPiece->x][p1->cPiece->y]=true;

	if(p1->cPiece->horizontal){
		tmp[(p1->cPiece->x)+1][p1->cPiece->y]=true;
		if(!p1->cPiece->small)
			tmp[(p1->cPiece->x)+2][p1->cPiece->y]=true;
	}else{
		tmp[p1->cPiece->x][(p1->cPiece->y)+1]=true;
		if(!p1->cPiece->small)
			tmp[p1->cPiece->x][(p1->cPiece->y)+2]=true;
	}

	if(p2->cPiece->horizontal){
		if(tmp[p2->cPiece->x][p2->cPiece->y] || tmp[(p2->cPiece->x)+1][p2->cPiece->y]){return true;}
		if(!p2->cPiece->small)
			if(tmp[(p1->cPiece->x)+2][p1->cPiece->y]){return true;}
	}
	return false;
}

int get_x(cpiece p)
{
	return p->cPiece->x;
}


int get_y(cpiece p)
{
	return p->cPiece->y;
}


int get_height(cpiece p)
{
	if (p->cPiece->horizontal)
		return 1;
	else 
	{
		if (p->cPiece->small)
			return 2;
		return 3;
	}
}

int get_width(cpiece p){
	if(!p->cPiece->horizontal)
		return 1;
	if(p->cPiece->small)
		return 2;
	return 3;
}

bool is_horizontal(cpiece p){
	return p->cPiece->horizontal;
}
