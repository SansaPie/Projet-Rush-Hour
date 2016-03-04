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
	// piece test0 = new_piece_rh(5,5,true,false); /* affiche qu'il y a un bout de la pièce qui dépasse */
	piece test = new_piece_rh(1,2,true,false); /* on créé une première pièce test */
	piece test2 = new_piece_rh(2,2,false, false); /* on créé une seconde pièce test2 */
	display_piece(test); /* on affiche la première pièce*/
	display_piece(test2); /* on affiche la seconde pièce. Les deux pièces ont bien été créées. */
	piece test3 = new_piece_rh(0,0,true,true);
	copy_piece(test, test3); /* on teste la fonction copy, censée copier test dans test3 */
	display_piece(test3); /* on affiche test3, afin de vérifier que test3 est désormais 
				égal à test. C'est le cas ! */
	delete_piece(test);
	//printf("x : %d \ny : %d \nsmall : %d \nhorizontal : %d\n", get_x(test), get_y(test), get_height(test), get_width(test)); /* n'affiche rien car test a été supprimée */
	printf("\nx : %d \ny : %d \nhauteur : %d \nlongueur : %d\n", get_x(test2), get_y(test2), get_height(test2), get_width(test2)); /* On teste les fonctions get */
	printf("\nhorizontal : %d \n", is_horizontal(test2)); /* on teste la fonction is_horizontal */
	printf("\nin board : %d \n", is_in_board(test2)); /* on teste la fonction is_in_board */
	delete_piece(test2);
	delete_piece(test3);
	return EXIT_SUCCESS;
}

void display_piece(piece p)
{
	printf("x : %d \n", p->x);
	printf("y : %d \n", p->y);
	printf("small : %d \n", p->small);
	printf("horizontal : %d \n", p->horizontal);
	printf("\n");
}

void test_move_piece(void)
{
	piece test = new_piece_rh(1,2,true,false);
	delete_piece(test);
	/* move_piece(test, LEFT, 1); fais un exit_failure car test a été free. On en déduit 
				     par la même occasion que delete_piece fonctionne. */
	piece test2 = new_piece_rh(1,2,true,false);
	// move_piece(test2, UP, -2); /* exit_failure car distance < 0 */
	move_piece(test2, UP, 2); /* bouge la pièce de 2 vers le haut */
	display_piece(test2); /* affiche la pièce test pour vérifier que le mouvement s'est bien fait */
	move_piece(test2, LEFT, 2); /* ne bouge pas la pièce car la direction de la pièce
				   n'est pas compatible avec la direction donnée */
	move_piece (test2, UP, 3); /* ne bouge pas la pièce car sinon elle sortirait du jeu */
	display_piece(test2); /* afficher la pièce test pour vérifier que le 
				mouvement ne s'est pas fait */
	delete_piece(test2);
}

void test_intersection(void)
{
	piece test = new_piece_rh(1,2,true,false);
	// intersect(test, test2); /* exit_failure car test == NULL */
	piece test2 = new_piece_rh(1,2,true,false);
	intersect(test, test2);
	printf("%d \n", intersect(test, test2)); /* affiche true car les deux pièces se croisent */
	piece test3 = new_piece_rh(3,3,true,false);
	printf("%d \n", intersect(test2, test3)); /* affiche false car les deux pièces 
						   ne se croisent pas */
	delete_piece(test);
	delete_piece(test2);
	delete_piece(test3);
}


















