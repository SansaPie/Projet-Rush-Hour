#ifndef _INT_GRAPH_H_
#define _INT_GRAPH_H_
#include <stdbool.h>
#include "SDL.h"

/**
 * @brief Returns true if the game is over ; false elsewise.
 */
bool game_over(cgame g, char game_type);

/**
 * @brief Tests if nb matches the index of an existing piece in g. If so, *piece_selected take nb value.
 */
void is_a_piece(cgame g, int * piece_selected, int nb);

/**
 * @brief Displays the hovered piece.
 */
void display_piece_hovered(game g, SDL_Surface * screen, char game_type, int piece_hovered, SDL_Rect position_cursor);

/**
 * @brief Display the selected piece.
 */
void display_piece_selected(game g, SDL_Surface * screen, char game_type, int piece_selected);

/**
 * @brief Displays a "Ane Rouge" game.
 */
void display_game_ar(game g, SDL_Surface * screen);

/**
 * @brief Displays a "Rush hour" game.
 */
void display_game_rh(game g, SDL_Surface * screen);

/**
 * @brief Displays the game depending on his type.
 */
void display_game(game g, SDL_Surface * screen, char game_type);

/**
 * @brief Allows the player to move a piece until he presses "Enter" or "Escape".
 * @param piece_selected index of the selected piece.
 * @param position_cursor position of the cursor, used here to keep the cursor on the piece moved in order to get a good display of it upon releasing the piece.
 */
void playing_piece(game g, int piece_selected, SDL_Surface * screen, char game_type, SDL_Rect * position_cursor);

/**
 * @brief Initializes and allows a graphic game to be played depending on his type.
 */
void graphic_game(game g, char game_type);

#endif
