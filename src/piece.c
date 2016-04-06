#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "piece.h"
#include "piece1.h"

piece new_piece_rh (int x, int y, bool small, bool horizontal){ 
	if(x<0 || y<0){
		fprintf(stderr, "new_piece_hr : hors tableau\n");
		exit(EXIT_FAILURE);
	}
	piece p = malloc(sizeof(struct piece_s));
	if(p==NULL){
		fprintf(stderr, "new_piece_hr : p non alloue\n");
		exit(EXIT_FAILURE);
	}
	p->x = x;
	p->y = y;
	if(horizontal){
		p->move_x = true;
		p->move_y = false;
		p->height = 1;
		p->width = 2;
		if(!small)
			p->width ++;
	}else{
		p->move_x = false;
		p->move_y = true;
		p->width = 1;
		p->height = 2;
		if(!small)
			p->height ++;
	}
	return p;
}

piece new_piece (int x, int y, int width, int height, bool move_x, bool move_y){
	if(width<0 || height<0){
		fprintf(stderr, "new_piece : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	if(x<0 || y<0){
		fprintf(stderr, "new_piece : hors tableau\n");
		exit(EXIT_FAILURE);
	}
	piece p = NULL;
	if(!move_x || !move_y)
		p = new_piece_rh(x, y, ((height==1&&width==2)||(height==2&&width==1)), (height==1));
	else{
		p = malloc(sizeof(struct piece_s));
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
	if(p==NULL || distance<0){
		fprintf(stderr, "move_piece : parametres invalides\n");
		exit(EXIT_FAILURE);
	}
	switch(d){
		case RIGHT:
			if(can_move_x(p))
				p->x+=distance;
			break;
		case LEFT:
			if(can_move_x(p))
				p->x-=distance;
			break;
		case UP:
			if(can_move_y(p))
				p->y+=distance;
			break;
		case DOWN:
			if(can_move_y(p))
				p->y-=distance;
			break;
	}
}

bool intersect(cpiece p1, cpiece p2){
	if (p1==NULL || p2==NULL){
		fprintf(stderr, "intersect : pieces non valides\n");
		exit(EXIT_FAILURE);
	}

	for(int i=get_x(p1) ; i<get_x(p1)+get_width(p1) ; i++){
		for(int j=get_y(p1) ; j<get_y(p1)+get_height(p1) ; j++){
			for(int k=get_x(p2) ; k<get_x(p2)+get_width(p2) ; k++){
				for(int l=get_y(p2) ; l<get_y(p2)+get_height(p2) ; l++){
					if(i==k && j==l)
						return true;
				}
			}
		}
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
	if (p == NULL) {
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

bool is_in_board(cpiece p, int width, int height){
	if(p==NULL){
		fprintf(stderr, "is_in_board : p invalide\n");
		exit(EXIT_FAILURE);
	}
	if(get_y(p) < 0 || get_x(p) <0)
		return false;

	if(can_move_x(p)){
		if(get_x(p) + (get_width(p)-1) > (width-1))
			return false;
	}
	if(can_move_y(p)){
		if(get_y(p) + (get_height(p)-1) > (height-1))
			return false;
	}
	return true;
}

bool can_move_x(cpiece p)
{
	if(p==NULL){
		fprintf(stderr, "can_move_x : p invalide\n");
		exit(EXIT_FAILURE);
	}
	return p->move_x;
}

bool can_move_y(cpiece p)
{
	if(p==NULL){
		fprintf(stderr, "can_move_y : p invalide\n");
		exit(EXIT_FAILURE);
	}
	return p->move_y;
}