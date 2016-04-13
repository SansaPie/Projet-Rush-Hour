#ifndef _ANE_ROUGE_H_
#define _ANE_ROUGE_H_
#include <stdbool.h>
#include "game.h"
#include "piece.h"

bool game_over_ar(cgame g);
game choice_config_ar(piece * pieces_test, int * n, int choice, char * answer, int size);
void ane_rouge(char * answer, int size, game g);

#endif