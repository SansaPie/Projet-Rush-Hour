#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "piece.h"

int main()
{
	piece test2 = new_piece_rh(5,5,true,false);
	piece test = new_piece_rh(6,6,false, true);
	printf("%d %d %d %d \n", test->x, test->y, test->small, test->horizontal);
	copy_piece(test2, test);
	printf("%d %d %d %d \n", test->x, test->y, test->small, test->horizontal);
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
			if(p->y+distance<=5 && p->horizontal)
				p->y+=distance;
			break;
		case RIGHT:
			if(p->y-distance>=0 && p->horizontal)
				p->y-=distance;
			break;
		case UP:
			if(p->x+distance<=5 && !p->horizontal)
				p->x+=distance;
			break;
		case DOWN:
			if(p->x-distance>=0 && !p->horizontal)
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
