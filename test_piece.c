#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "piece.h" 

void afficher_piece(piece p);
void test_move_piece(void);
void test_intersection(void);

int main()
{
	test_intersection();
	piece test = new_piece_rh(5,5,true,false); /* on créé une première pièce test */
	piece test2 = new_piece_rh(2,2,false, false); /* on créé une seconde pièce test2 */
	afficher_piece(test); /* on affiche la première pièce*/
	afficher_piece(test2); /* on affiche la seconde pièce. Les deux pièces ont bien été créées. */
	copy_piece(test, test2); /* on teste la fonction copy, censée copier test dans test2 */
	afficher_piece(test2); /* on affiche test2, afin de vérifier que test2 est désormais 
				égal à test. C'est le cas ! */
	return EXIT_SUCCESS;
}

void afficher_piece(piece p)
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
	afficher_piece(test2); /* affiche la pièce test pour vérifier que le mouvement s'est bien fait */
	move_piece(test2, LEFT, 2); /* ne bouge pas la pièce car la direction de la pièce
				   n'est pas compatible avec la direction donnée */
	move_piece (test2, UP, 3); /* ne bouge pas la pièce car sinon elle sortirait du jeu */
	afficher_piece(test2); /* afficher la pièce test pour vérifier que le 
				mouvement ne s'est pas fait */
}

void test_intersection(void)
{
	piece test = new_piece_rh(1,2,true,false);
	piece test2 = new_piece_rh(2,2,true,false);
	delete_piece(test);
	intersect(test, test2); /* exit_failure car test == NULL */
	piece test3 = new_piece_rh(1,2,true,false);
	intersect(test2, test3);
	printf("%d \n", intersect(test2, test3)); /* affiche true car les deux pièces se croisent */
	piece test4 = new_piece_rh(3,3,true,false);
	printf("%d \n", intersect(test3, test4)); /* affiche false car les deux pièces 
						   ne se croisent pas */
}


















