#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "piece.h" 

void afficher_piece(piece p);

int main()
{
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
}

void test_move_piece(piece p)
{
	
}



















