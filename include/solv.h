#ifndef _SOLV_H_
#define _SOLV_H_
#include <stdbool.h>

/**
 * @struct Maillon.
 * @brief A Maillon represents a component of queue.
 */

typedef struct Maillon{
	game gameG;
	struct Maillon *next;
}*maillon;

/**
 * @struct File.
 * @brief A File represents a queue of game.
 */

typedef struct File{
	maillon premier;
}*file;

/**
 * @struct Tas.
 * @brief A Tas represents a heap of game.
 */

typedef struct Tas{
	int capacite;
	int index;
	game *tab;
}*tas;

/**
 *  @brief function that throws an error message.
 */
 
void usage(char * commande);

/**
 * @brief function allowing the reading of pieces features from an annexed file.
 */
 
piece * lecture(piece * pieces_test, int * n, int * width, int * height, FILE * entree);


/**
 * @brief function to create heaps.
 */

tas new_tas(int capacite);

/**
 * @brief function free heaps.
 */

void free_tas(tas t);

/**
 * @brief function rezise heaps.
 */

void resize_tas(tas t);

/**
 * @brief function push a game in heaps.
 */

void push(tas t, game g);

/**
 * @brief function copy heap into a other heap.
 */

tas copy_tas(tas src, tas dst);

/**
 * @brief function create queues.
 */

file new_file();

/**
 * @brief function add a game at the end of the queue.
 */

void enfiler(file f, game g);

/**
 * @brief function remove a game at the begining of the queue.
 */

void defiler(file f);

/**
 * @brief function free queues.
 */

void free_file(file f);

/**
 * @brief function compare to game and see if there are identical.
 */

bool equals(cgame g, cgame g1);

bool is_config(cgame g, tas t);

bool game_over(char game_type, file f);

int solv(game g, char game_type);

#endif