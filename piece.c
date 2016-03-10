#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "piece.h"

piece new_piece_rh (int x, int y, bool small, bool horizontal){
	if(x<0 || y<0 || y>H_RH || x>L_RH){
		fprintf(stderr, "new_piece_hr : hors tableau\n");
		exit(EXIT_FAILURE);
	}
	if((y==H_RH-1 && !horizontal) || (x==L_RH-1 && horizontal) || 
		(y>=H_RH-2 && !horizontal && !small) || (x>=L_RH-2 && horizontal && !small)){
		fprintf(stderr,"new_piece_hr : piece sortant en partie du tableau\n");
		exit(EXIT_FAILURE);
	}
	piece p = malloc(sizeof(struct piece_s));
	if(p==NULL){
		fprintf(stderr, "new_piece_hr : p non alloue\n");
		exit(EXIT_FAILURE);
	}
	p->x = x;
	p->y = y;
	if(horizontal)
	{
		p->move_x = true;
		p->move_y = false;
		p->height = 1;
		p->width = 2;
		if(!small)
			p->width ++;
	}
	else
	{
		p->move_x = false;
		p->move_y = true;
		p->width = 1;
		p->height = 2;
		if(!small)
			p->height ++;
	}
	return p;
}


void delete_piece (piece p){
	if(p!=NULL)
		free(p);
	else{
		fprintf(stderr, "delete_piece : p null\n");
		exit(EXIT_FAILURE);
	}
}


void copy_piece (cpiece src, piece dst){
	if(src==NULL || dst==NULL){
		fprintf(stderr, "copy_piece : pieces invalides\n");
		exit(EXIT_FAILURE);
	}
	dst->x = src->x;
	dst->y = src->y;
	dst->width = src->width;
	dst->height = src->height;
	dst->move_x = src->move_x;
	dst->move_y = src->move_y;
}

void move_piece (piece p, dir d, int distance){
	if(p==NULL){
		fprintf(stderr, "move_piece : parametres invalides\n");
		exit(EXIT_FAILURE);
	}
	switch(d){
		case RIGHT:
			if(is_horizontal(p))
				p->x+=distance;
			break;
		case LEFT:
			if(is_horizontal(p))
				p->x-=distance;
			break;
		case UP:
			if(!is_horizontal(p))
				p->y+=distance;
			break;
		case DOWN:
			if(!is_horizontal(p))
				p->y-=distance;
			break;
	}
}

bool intersect(cpiece p1, cpiece p2){
	if (p1==NULL || p2==NULL){
		fprintf(stderr, "intersect : pieces non valides\n");
		exit(EXIT_FAILURE);
	}

	bool tmp[L_RH][H_RH];
	for(int i=0;i<L_RH;i++){
		for(int j=0;j<H_RH;j++){
			tmp[i][j]=false;
		}
	}

	int xCoor1 = get_x(p1);
	int yCoor1 = get_y(p1);
	int xCoor2 = get_x(p2);
	int yCoor2 = get_y(p2);

	tmp[xCoor1][yCoor1]=true;

	if(is_horizontal(p1)){
		tmp[(xCoor1)+1][yCoor1]=true;
		if(!is_small(p1))
			tmp[(xCoor1)+2][yCoor1]=true;
	}else{
		tmp[xCoor1][(yCoor1)+1]=true;
		if(!is_small(p1))
			tmp[xCoor1][(yCoor1)+2]=true;
	}
	if (is_horizontal(p2)) {
		if (tmp[xCoor2][yCoor2] || tmp[(xCoor2) + 1][yCoor2]) { return true; }
		if (!is_small(p2))
			if (tmp[(xCoor2) + 2][yCoor2]) { return true; }
	}
	else {
		if (tmp[xCoor2][yCoor2] || tmp[xCoor2][(yCoor2)+1]) { return true; }
		if (!is_small(p2))
			if (tmp[xCoor2][(yCoor2)+2]) { return true; }
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
	return p->height;
}

int get_width(cpiece p){
	if(p==NULL){
		fprintf(stderr, "get_width : p invalide\n");
		exit(EXIT_FAILURE);
	}
	return p->width;
}

bool is_horizontal(cpiece p){
	if(p==NULL){
		fprintf(stderr, "is_horizontal : p invalide\n");
		exit(EXIT_FAILURE);
	}
	if(can_move_x(p) && can_move_y(p)){
		fprintf(stderr, "is_horizontal : p n'est pas une piece de rush hour\n");
		exit(EXIT_FAILURE);
	}
	return can_move_x(p);
}

bool is_small(cpiece p) {
	if (p == NULL) {
		fprintf(stderr, "is_small : p invalide\n");
		exit(EXIT_FAILURE);
	}
	if(get_width(p)>get_height(p))
		return get_width(p)==2;
	else
		return get_height(p)==2;
}

bool is_in_board(cpiece p){
	if(p==NULL){
		fprintf(stderr, "is_in_board : p invalide\n");
		exit(EXIT_FAILURE);
	}
	if(get_y(p) < 0 || get_x(p) <0)
		return false;

	if(is_horizontal(p)){
		if(get_x(p) + (get_width(p)-1) > (L_RH-1))
			return false;
	}else{
		if(get_y(p) + (get_height(p)-1) > (H_RH-1))
			return false;
	}
	return true;
}

bool can_move_x(cpiece p)
{
	return p->move_x;
}

bool can_move_y(cpiece p)
{
	return p->move_y;
}


piece new_piece (int x, int y, int width, int height, bool move_x, bool move_y)
{
	if(x<0 || y<0 || y>H_RH || x>L_RH){
		fprintf(stderr, "new_piece : hors tableau\n");
		exit(EXIT_FAILURE);
	}
	if(((height+y)>H_RH) || ((width+x)>L_RH))
	{
		fprintf(stderr,"new_piece : piece sortant en partie du tableau\n");
		exit(EXIT_FAILURE);
	}
	piece p = malloc(sizeof(struct piece_s));
	if(p==NULL){
		fprintf(stderr, "new_piece : p non alloue\n");
		exit(EXIT_FAILURE);
	}
	p->x = x;
	p->y = y;
	p->width = width;
	p->height = height;
	p->move_x = move_x;
	p->move_y = move_y;
	return p;
}











