#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "piece.h"
#include "piece1.h"

piece new_piece_rh (int x, int y, bool small, bool horizontal){ 
	piece p = new_piece(x, y, 1, 1, horizontal, !horizontal);
	if(horizontal){
		p->width ++;
		if(!small)
			p->width ++;
	}else{
		p->height ++;
		if(!small)
			p->height ++;
	}
	return p;
}

piece new_piece (int x, int y, int width, int height, bool move_x, bool move_y){
	assert(!(width<0 || height<0 || x<0 || y<0));
	piece p = malloc(sizeof(struct piece_s));
	assert(p!=NULL);
	p->x = x;
	p->y = y;
	p->width = width;
	p->height = height;
	p->move_x = move_x;
	p->move_y = move_y;
	return p;
}

void delete_piece (piece p){
	assert(p!=NULL);
	free(p);
}

void copy_piece (cpiece src, piece dst){
	assert(!(src==NULL || dst==NULL));
	dst->x = src->x;
	dst->y = src->y;
	dst->width = src->width;
	dst->height = src->height;
	dst->move_x = src->move_x;
	dst->move_y = src->move_y;
}

void move_piece (piece p, dir d, int distance){
	assert(!(p==NULL || distance<0));
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
	assert(!(p1==NULL || p2==NULL));

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

int get_x(cpiece p){
	assert(p!=NULL);
	return p->x;
}


int get_y(cpiece p){
	assert(p!=NULL);
	return p->y;
}

int get_height(cpiece p){
	assert(p!=NULL);
	return p->height;
}

int get_width(cpiece p){
	assert(p!=NULL);
	return p->width;
}

bool is_horizontal(cpiece p){
	assert(p!=NULL);
	return get_height(p)<get_width(p);
}

bool is_small(cpiece p){
	assert(p!=NULL);
	if(get_width(p)>get_height(p))
		return get_width(p)==2;
	else
		return get_height(p)==2;
}

bool is_in_board(cpiece p, int width, int height){
	assert(p!=NULL);
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

bool can_move_x(cpiece p){
	assert(p!=NULL);
	return p->move_x;
}

bool can_move_y(cpiece p){
	assert(p!=NULL);
	return p->move_y;
}
