#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "piece.h"

#define L 6 //Longueur de la grille
#define H 6 //Hauteur de la grille

piece new_piece_rh (int x, int y, bool small, bool horizontal){
	if(x<0 || y<0 || x>H || y>L){
		fprintf(stderr, "new_piece_hr : hors board\n");
		exit(EXIT_FAILURE);
	}
	if((x==H && !horizontal) || (y==L && horizontal) || 
		(x>=H-1 && !horizontal && !small) || (y>=L-1 && horizontal && !small)){
		fprintf(stderr,"new_piece_hr : il y a un bout qui depasse\n");
		exit(EXIT_FAILURE);
	}
	piece p = malloc(sizeof(struct piece_s));
	if(p==NULL){
		fprintf(stderr, "new_piece_hr : p non alloue\n");
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
	if(src==NULL || dst==NULL){
		fprintf(stderr, "copy_piece : pieces invalides\n");
		exit(EXIT_FAILURE);
	}
	dst->x = src->x;
	dst->y = src->y;
	dst->small = src->small;
	dst->horizontal = src->horizontal;
}

void move_piece (piece p, dir d, int distance){
	if(p==NULL || distance<0){
		fprintf(stderr, "move_piece : parametres invalides\n");
		exit(EXIT_FAILURE);
	}
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
	if (p1==NULL || p2==NULL){
		fprintf(stderr, "intersect : pieces non valides\n");
		exit(EXIT_FAILURE);
	}

	bool tmp[H][L];
	for(int i=0;i<H;i++){
		for(int j=0;j<L;j++){
			tmp[i][j]=false;
		}
	}
	tmp[p1->x][p1->y]=true;

	if(is_horizontal(p1)){
		tmp[(p1->x)+1][p1->y]=true;
		if(!is_small(p1))
			tmp[(p1->x)+2][p1->y]=true;
	}else{
		tmp[p1->x][(p1->y)+1]=true;
		if(!is_small(p1))
			tmp[p1->x][(p1->y)+2]=true;
	}

	if (is_horizontal(p2)) {
		if (tmp[p2->x][p2->y] || tmp[(p2->x) + 1][p2->y]) { return true; }
		if (!is_small(p2))
			if (tmp[(p1->x) + 2][p1->y]) { return true; }
	}
	else {
		if (tmp[p2->x][p2->y] || tmp[p2->x][(p2->y)+1]) { return true; }
		if (!is_small(p2))
			if (tmp[p1->x][(p1->y)+2]) { return true; }
	}
	return false;
}

int get_x(cpiece p)
{
	if(p==NULL){
		fprintf(stderr, "get_x : p invalide\n");
		exit(EXIT_FAILURE);
	}
	return p->x;
}


int get_y(cpiece p)
{
	if(p==NULL){
		fprintf(stderr, "get_y : p invalide\n");
		exit(EXIT_FAILURE);
	}
	return p->y;
}


int get_height(cpiece p)
{
	if(p==NULL){
		fprintf(stderr, "get_height : p invalide\n");
		exit(EXIT_FAILURE);
	}
	if (is_horizontal(p))
		return 1;
	else 
	{
		if (is_small(p))
			return 2;
		return 3;
	}
}

int get_width(cpiece p){
	if(p==NULL){
		fprintf(stderr, "get_width : p invalide\n");
		exit(EXIT_FAILURE);
	}
	if(!is_horizontal(p))
		return 1;
	if(is_small(p))
		return 2;
	return 3;
}

bool is_horizontal(cpiece p){
	if(p==NULL){
		fprintf(stderr, "is_horizontal : p invalide\n");
		exit(EXIT_FAILURE);
	}
	return p->horizontal;
}

bool is_small(cpiece p) {
	if (p == NULL) {
		fprintf(stderr, "is_small : p invalide\n");
		exit(EXIT_FAILURE);
	}
	return p->small;
}

bool is_in_board(cpiece p){
	if(p==NULL){
		fprintf(stderr, "is_in_board : p invalide\n");
		exit(EXIT_FAILURE);
	}
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
	return true;
}
