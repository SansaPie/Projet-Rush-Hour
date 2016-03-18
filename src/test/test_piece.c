#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "piece.h" 

void display_piece(piece p);
void test_move_piece(void);
void test_intersection(void);

int main()
{
	test_intersection();
	/**
	 * creation of 3 pieces
	 */
	piece test = new_piece_rh(1,2,true,false); 
	piece test2 = new_piece_rh(2,2,false, false);
	piece test3 = new_piece_rh(0,0,true,true);
	display_piece(test);
	display_piece(test2); 
	/** 
	 * display the two first pieces
	 */
	copy_piece(test, test3); 
	/** 
	 * copy_piece is supposed to copy test in test3
	 */
	display_piece(test3); 
	/**
	 * display test3 in order to verify that it's the same as test. - OK 
	 */
	delete_piece(test);
	printf("\nx : %d \ny : %d \nhauteur : %d \nlongueur : %d\n", get_x(test2), get_y(test2), get_height(test2), get_width(test2)); 
	/** 
	 * test of the getters
	 */
	printf("\nhorizontal : %d \n", is_horizontal(test2)); 
	/**
	 * test is_horizontal
	 */
	printf("\nin board : %d \n", is_in_board(test2)); 
	/**
	 * test is_in_board
	 */
	delete_piece(test2);
	delete_piece(test3);
	return EXIT_SUCCESS;
}

void display_piece(piece p)
{
	printf("x : %d \n", p->x);
	printf("y : %d \n", p->y);
	printf("largeur : %d \n", p->width);
	printf("hauteur : %d \n", p->height);
	printf("move_x : %d \n", p->move_x);
	printf("move_y : %d \n", p->move_y);
	printf("\n");
}

void test_move_piece(void)
{
	piece test = new_piece_rh(1,2,true,false);
	delete_piece(test);
	/** 
	 * move_piece(test, LEFT, 1); 
	 * return an exit_failure : the delete_piece works !
	 */
	piece test2 = new_piece_rh(1,2,true,false);
	/**
	 * move_piece(test2, UP, -2); 
	 * exit_failure because distance<0 -> test error
	 */
	move_piece(test2, UP, 2); 
	display_piece(test2); 
	/**
	 * display the piec in order to verify that move_piece(test2, UP, 2) happened 
	 */
	move_piece(test2, LEFT, 2); 
	/**
	 * don't move the piece because the direction doesn't suit the piece
	 */
	move_piece (test2, UP, 3); 
	/**
	 * don't move the piece, otherwise it would go outside the board 
	 */
	display_piece(test2); 
	/* 
	 * display the piece in order to verify that the movement didn't occure
	 */
	delete_piece(test2);
}

void test_intersection(void)
{
	piece test = new_piece_rh(1,2,true,false);
	/**
	 * intersect(test, test2); 
	 * exit_failure because test == NULL
	 */
	piece test2 = new_piece_rh(1,2,true,false);
	intersect(test, test2);
	printf("%d \n", intersect(test, test2)); 
	/**
	 * display true because the two pieces are crossing each other
	 */
	piece test3 = new_piece_rh(3,3,true,false);
	printf("%d \n", intersect(test2, test3));
	delete_piece(test);
	delete_piece(test2);
	delete_piece(test3);
}