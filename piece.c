#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "piece.h"

piece new_piece_rh (int x, int y, bool small, bool horizontal){
	if(x<0 || y<0 || x>5 || y>5)
		exit(EXIT_FAILURE);
	if((x==5 && !horizontal) || (y=5 && horizontal) || (x>=4 && !horizontal && !small) || (y>=4 && horizontal && !small))
		exit(EXIT_FAILURE);
	piece p = malloc(sizeof(struct piece_s));
	if(p==NULL){
		fprintf(stderr, "p non alloue\n");
		exit(EXIT_FAILURE);
	}
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
		case RIGHT:
			p->y+=distance;
			break;
		case LEFT:
			p->y-=distance;
			break;
		case UP:
			p->x+=distance;
			break;
		case DOWN:
			p->x-=distance;
			break;
	}
}

bool intersect(cpiece p1, cpiece p2){
if (p1==NULL || p2==NULL)
		exit(EXIT_FAILURE);

	bool tmp[6][6];
	tmp[p1->x][p1->y]=true;

	if(p1->horizontal){
		tmp[(p1->x)+1][p1->y]=true;
		if(!p1->small)
			tmp[(p1->x)+2][p1->y]=true;
	}else{
		tmp[p1->x][(p1->y)+1]=true;
		if(!p1->small)
			tmp[p1->x][(p1->y)+2]=true;
	}

	if (p2->horizontal) {
		if (tmp[p2->x][p2->y] || tmp[(p2->x) + 1][p2->y]) { return true; }
		if (!p2->small)
			if (tmp[(p1->x) + 2][p1->y]) { return true; }
	}
	else {
		if (tmp[p2->x][p2->y] || tmp[p2->x][(p2->y)+1]) { return true; }
		if (!p2->small)
			if (tmp[p1->x][(p1->y)+2]) { return true; }
	}
	return false;
}

int get_x(cpiece p)
{
	return p->x;
}


int get_y(cpiece p)
{
	return p->y;
}


int get_height(cpiece p)
{
	if (p->horizontal)
		return 1;
	else 
	{
		if (p->small)
			return 2;
		return 3;
	}
}

int get_width(cpiece p){
	if(!p->horizontal)
		return 1;
	if(p->small)
		return 2;
	return 3;
}

bool is_horizontal(cpiece p){
	return p->horizontal;
}

bool is_in_board(cpiece p){
	if(p->y<0 || p->x<0)
		return false;
	int size = 1;
	if(!p->small)
		size = 2;

	if(p->horizontal){
		if(p->y+size>5)
			return false;
	}else{
		if(p->x+size>5)
			return false;
	}
}
