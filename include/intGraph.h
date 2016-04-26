#ifndef _INT_GRAPH_H_
#define _INT_GRAPH_H_
#include <stdbool.h>
#include "SDL.h"

bool game_over(cgame g, char game_type);
void is_a_piece(cgame g, int * piece_selected, int nb);
void display_piece_hovered(game g, SDL_Surface * screen, char game_type, int piece_hovered, SDL_Rect position_cursor);
void display_piece_selected(game g, SDL_Surface * screen, char game_type, int piece_selected);
void display_game_ar(game g, SDL_Surface * screen);
void display_game_rh(game g, SDL_Surface * screen);
void display_game(game g, SDL_Surface * screen, char game_type);
void playing_piece(game g, int piece_selected, SDL_Surface * screen, char game_type);
void graphic_game(game g, char game_type);

#endif