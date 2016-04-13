#ifndef _INPUT_H_
#define _INPUT_H_
#include "piece.h"

piece * lecture(piece * pieces_test, int * n, FILE * entree);
char * scan(char * buffer , int size);
char ** allocation_char_matrix(int width, int height);
void delete_char_matrix(char ** grid, int width);
char * input_config_user(char * answer, int size);
int input_piece_played(char * answer, int size, cgame g);
int input_distance(char * answer, int size, cgame g);
dir input_direction(char * direction, int size);
void display_success_movement(game g, int piece_played, int distance, dir d);
void display_game(cgame g);

#endif