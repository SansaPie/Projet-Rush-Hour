#ifndef _RUSH_HOUR_H_
#define _RUSH_HOUR_H_
#include "game.h"
#include "piece.h"

void move_rh(game g, int piece_played, int distance);
game choice_config_rh(piece * pieces_test, int * n, int choice, char * answer, int size);
void rush_hour(char * answer, int size, game g);

#endif