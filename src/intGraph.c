#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h> // A modifier avec le makefile
#include <SDL/SDL_image.h> // Pour IMG_Load
#include "game.h"
#include "game1.h"

#define BLOC_SIZE 50// Constante à placer dans un header

// Header à faire

bool game_over(cgame g, char game_type){
	if(g==NULL || game_type!='a' || game_type!='r'){
		fprintf(stderr, "game_over : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	if(game_type=='r')
		return game_over_hr(g);
	return game_over_ar(g);
}

int is_a_piece(cgame g, int nb){
	if(g==NULL || nb<0){
		fprintf(stderr, "is_a_piece : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	if(nb<game_nb_pieces(g))
		return nb;
	return 0;
}

void display_game(cgame g, SDL_Surface * screen, char game_type){
	if(g==NULL || screen == NULL || game_type!='a' || game_type!='r'){
		fprintf(stderr, "display_game : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	SDL_FillRect(screen, NULL, SDL_MapRGB(ecran->format, 255,255,255));
	if(game_type=='r')
		display_game_rh(g, screen);
	else
		display_game_ar(g, screen);
}

void display_game_rh(cgame g, SDL_Surface * screen){
	if(g==NULL || screen==NULL){
		fprintf(stderr, "display_game_rh : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	SDL_Rect position = NULL;

	SDL_Surface *verticalCar = NULL, *horizontalCar = NULL, *verticalTruck = NULL, *horizontalTruck = NULL, *redCar = NULL, *redArrow = NULL;
	verticalCar = IMG_Load("../img/verticalCar.png");
	horizontalCar = IMG_Load("../img/horizontalCar.png");
	verticalTruck = IMG_Load("../img/verticalTruck.png");
	horizontalTruck = IMG_Load("../img/horizontalTruck.png");
	redCar = IMG_Load("../img/redCar.png");
	redArrow = IMG_Load("../img/redArrowRh.png");

	for(int i=0 ; i<game_nb_pieces(g) ; i++){
		position.x = get_x(game_piece(g, i)) * BLOC_SIZE;
		position.y = get_y(game_piece(g, i)) * BLOC_SIZE;
		
		if(i==0)
			SDL_BlitSurface(redCar, NULL, screen, &position);
		else{
			if(is_small(game_piece(g, i))){
				if(is_horizontal(game_piece(g, i)))
					SDL_BlitSurface(horizontalCar, NULL, screen, &position);
				else
					SDL_BlitSurface(verticalCar, NULL, screen, &position);
			}else{
				if(is_horizontal(game_piece(g, i)))
					SDL_BlitSurface(horizontalTruck, NULL, screen, &position);
				else
					SDL_BlitSurface(verticalTruck, NULL, screen, &position);
			}
		}
	}
	position.x = 4 * BLOC_SIZE;
	position.y = 3 * BLOC_SIZE;
	SDL_BlitSurface(redArrow, NULL, screen, &position);
}

void display_game_ar(cgame g, SDL_Surface * screen){
	if(g==NULL || screen==NULL){
		fprintf(stderr, "display_game_ar : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	SDL_Rect position = NULL;

	SDL_Surface *square = NULL, *smallPiece = NULL, *largeHorizontalPiece = NULL, *largeVerticalPiece = NULL, *redArrow = NULL;
	square = IMG_Load("../img/square.png");
	smallPiece = IMG_Load("../img/smallPiece.png");
	largeHorizontalPiece = IMG_Load("../img/largeHorizontalPiece.png");
	largeVerticalPiece = IMG_Load("../img/largeVerticalPiece.png");
	redArrow = IMG_Load("../img/redArrowAr.png");

	for(int i=0 ; i<game_nb_pieces(g) ; i++){
		position.x = get_x(game_piece(g, i)) * BLOC_SIZE;
		position.y = get_y(game_piece(g, i)) * BLOC_SIZE;
		
		if(i==0)
			SDL_BlitSurface(square, NULL, screen, &position);
		else{
			if(get_width(game_piece(g, i))==1 && get_height(game_piece(g, i))==1)
				SDL_BlitSurface(smallPiece, NULL, screen, &position);
			else{
				if(is_horizontal(game_piece(g, i)))
					SDL_BlitSurface(largeHorizontalPiece, NULL, screen, &position);
				else
					SDL_BlitSurface(largeVerticalPiece, NULL, screen, &position);
			}
		}
	}
	position.x = BLOC_SIZE;
	position.y = 0;
	SDL_BlitSurface(redArrow, NULL, screen, &position);
}

void playing_piece(game g, int piece_selected, SDL_Surface * screen, char game_type){
	if(g==NULL || piece_selected<0 || piece_selected>=game_nb_pieces(g) || screen==NULL || game_type!='a' || game_type!='r'){
		fprintf(stderr, "playing_piece : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}

	bool piece_on = true;
	SDL_Event event = NULL;
	dir d = RIGHT;

	while(!game_over(g, game_type) && piece_on){
		SDL_WaitEvent()
		switch(event.type){
			case SDL_QUIT:
				piece_on = false;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
						piece_on = false; // Peut-être une fonctionnalité permettant d'annuler son coup ? Copie de game, lorsqu'on presse échap, on retrouve celle-ci
						break;
					case SDLK_RIGHT:
						d = RIGHT;
						break;
					case SDLK_LEFT:
						d = LEFT;
						break;
					case SDLK_UP:
						d = UP;
						break;
					case SDLK_DOWN:
						d = DOWN;
						break;
					case SDLK_ENTER:
						piece_on = false;
						break;
					default:
						break;
				}
				if(piece_on)
					play_move(g, piece_selected, d, 1);
				break;
			default:
				break;
		}
		display_game(g, screen, game_type);
		// Faire suivre contour de la piece sélectionnée. Problème de chargement d'image ?
		SDL_Flip(screen);
	}
}

void graphic_game(game g, char * name){
	if(g==NULL || name == NULL){
		fprintf(stderr, "graphic_game : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}

	SDL_Surface * screen = NULL;
	SDL_Event event = NULL;
	bool game_on = true;
	int piece_selected = 0;

	// position piece_selected : rectangle non rempli entourant voiture selectionnée (- quelques pixels sur x et y pour faire apparaître)
	// Différents rectangles possibles ...
	// Faire apparaître / disparaître rectangle ? Changement couleur ?

	char game_type = 'a';
	if(game_width(g)==6)
		game_type = 'r';

	if(SDL_Init(SDL_INIT_VIDEO)==-1){
		fprintf(stderr, "graphic_game : erreur chargement SDL : %s.\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	screen = SDL_SetVideoMode(BLOC_SIZE*game_width(g), BLOC_SIZE*game_height(g), 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_SetCaption(name, NULL);

	while(!game_over(g, game_type) && game_on){
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_QUIT:
                game_on = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        game_on = false;
                        break;
                    case SDLK_RIGHT:
                    	piece_selected = is_a_piece(g, ++piece_selected);
                        break;
                    case SDLK_LEFT:
                    	piece_selected--;
                    	if(piece_selected<0)
                    		piece_selected = game_nb_pieces(g)-1;
                        break;
                    case SDLK_KP0:
                    	piece_selected=0;
                    	break;
                  	case SDLK_KP1:
                  		piece_selected = is_a_piece(g, 1);
                  		break;
                 	case SDLK_KP2:
                  		piece_selected = is_a_piece(g, 2);
                  		break;
                  	case SDLK_KP3:
                  		piece_selected = is_a_piece(g, 3);
                  		break;
                  	case SDLK_KP4:
                  		piece_selected = is_a_piece(g, 4);
                  		break;
                  	case SDLK_KP5:
                  		piece_selected = is_a_piece(g, 5);
                  		break;
                  	case SDLK_KP6:
                  		piece_selected = is_a_piece(g, 6);
                  		break;
                  	case SDLK_KP7:
                  		piece_selected = is_a_piece(g, 7);
                  		break;
                  	case SDLK_KP8:
                  		piece_selected = is_a_piece(g, 8);
                  		break;
                  	case SDLK_KP9:
                  		piece_selected = is_a_piece(g, 9);
                  		break;
                    case SDLK_ENTER:
                    	playing_piece(g, piece_selected, screen, game_type);
                    	break;
                    default:
                    	break;
                }
                break;
            default:
            	break;
		}
		display_game(g, screen, game_type);
		// Blit contour piece_selected
		SDL_Flip(screen);
	}
	SDL_FreeSurface(screen);
	SDL_Quit();
}