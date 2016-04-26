#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SDL.h" // A modifier avec le makefile
#include "SDL_image.h" // Pour IMG_Load
#include "game.h"
#include "game1.h"
#include "piece.h"
#include "piece1.h"

#define BLOC_SIZE 75

bool game_over(cgame g, char game_type){
	if(g==NULL || (game_type!='a' && game_type!='r')){
		fprintf(stderr, "game_over : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	if(game_type=='r')
		return game_over_hr(g);
	return game_over_ar(g);
}

void is_a_piece(cgame g, int * piece_selected, int nb){
	if(g==NULL || piece_selected==NULL || nb<0){
		fprintf(stderr, "is_a_piece : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	if(nb<game_nb_pieces(g))
		*piece_selected = nb;
}

void display_piece_hovered(cgame g, SDL_Surface * screen, char game_type, int piece_hovered, SDL_Rect * position_cursor){
	SDL_Surface *smallPieceHovered = NULL;
	smallPieceHovered = IMG_Load("../img/smallPieceHovered.png");
	if(piece_hovered==-1){
		position_cursor->x *= BLOC_SIZE;
		position_cursor->y = (game_height(g)-1-position_cursor->y) * BLOC_SIZE;
		SDL_BlitSurface(smallPieceHovered, NULL, screen, position_cursor);
		position_cursor->x /= BLOC_SIZE;
		position_cursor->y = game_height(g)-1-(position_cursor->y/BLOC_SIZE);
	}
	else{
		SDL_Rect position_piece_hovered;
		position_piece_hovered.x = get_x(game_piece(g, piece_hovered)) * BLOC_SIZE;
		position_piece_hovered.y = (game_height(g)-get_height(game_piece(g, piece_hovered))-get_y(game_piece(g, piece_hovered))) * BLOC_SIZE;
		
		SDL_Surface *verticalPieceHovered = NULL, *horizontalPieceHovered = NULL;
		verticalPieceHovered = IMG_Load("../img/verticalPieceHovered.png");
		horizontalPieceHovered = IMG_Load("../img/horizontalPieceHovered.png");
		if(game_type=='a'){
			SDL_Surface *squareHovered = NULL;
			squareHovered = IMG_Load("../img/squareHovered.png");

			if(piece_hovered==0)
				SDL_BlitSurface(squareHovered, NULL, screen, &position_piece_hovered);
			else
				if(get_width(game_piece(g, piece_hovered))==1 && get_height(game_piece(g, piece_hovered))==1)
					SDL_BlitSurface(smallPieceHovered, NULL, screen, &position_piece_hovered);
		}else{
			SDL_Surface *verticalTruckHovered = NULL, *horizontalTruckHovered = NULL;
			verticalTruckHovered = IMG_Load("../img/verticalTruckHovered.png");
			horizontalTruckHovered = IMG_Load("../img/horizontalTruckHovered.png");

			if(!is_small(game_piece(g, piece_hovered))){
				if(is_horizontal(game_piece(g, piece_hovered)))
					SDL_BlitSurface(horizontalTruckHovered, NULL, screen, &position_piece_hovered);
				else
					SDL_BlitSurface(verticalTruckHovered, NULL, screen, &position_piece_hovered);
			}
		}
		if(is_small(game_piece(g, piece_hovered)) && get_width(game_piece(g, piece_hovered))!=get_height(game_piece(g, piece_hovered))){
			if(is_horizontal(game_piece(g, piece_hovered)))
				SDL_BlitSurface(horizontalPieceHovered, NULL, screen, &position_piece_hovered);
			else
				SDL_BlitSurface(verticalPieceHovered, NULL, screen, &position_piece_hovered);
		}
		position_cursor->x = get_x(game_piece(g, piece_hovered));
		position_cursor->y = get_y(game_piece(g, piece_hovered));
	}
}

void display_piece_selected(cgame g, SDL_Surface * screen, char game_type, int piece_selected, SDL_Rect * position_cursor){
	SDL_Rect position_piece_selected;
	position_piece_selected.x = get_x(game_piece(g, piece_selected)) * BLOC_SIZE;
	position_piece_selected.y = (game_height(g)-get_height(game_piece(g, piece_selected))-get_y(game_piece(g, piece_selected))) * BLOC_SIZE;
	
	SDL_Surface *verticalPieceSelected = NULL, *horizontalPieceSelected = NULL;
	verticalPieceSelected = IMG_Load("../img/verticalPieceSelected.png");
	horizontalPieceSelected = IMG_Load("../img/horizontalPieceSelected.png");

	if(game_type=='a'){
		SDL_Surface *squareSelected = NULL, *smallPieceSelected = NULL;
		squareSelected = IMG_Load("../img/squareSelected.png");
		smallPieceSelected = IMG_Load("../img/smallPieceSelected.png");

		if(piece_selected==0)
			SDL_BlitSurface(squareSelected, NULL, screen, &position_piece_selected);
		else
			if(get_width(game_piece(g, piece_selected))==1 && get_height(game_piece(g, piece_selected))==1)
				SDL_BlitSurface(smallPieceSelected, NULL, screen, &position_piece_selected);
	}else{
		SDL_Surface *verticalTruckSelected = NULL, *horizontalTruckSelected = NULL;
		verticalTruckSelected = IMG_Load("../img/verticalTruckSelected.png");
		horizontalTruckSelected = IMG_Load("../img/horizontalTruckSelected.png");

		if(!is_small(game_piece(g, piece_selected))){
			if(is_horizontal(game_piece(g, piece_selected)))
				SDL_BlitSurface(horizontalTruckSelected, NULL, screen, &position_piece_selected);
			else
				SDL_BlitSurface(verticalTruckSelected, NULL, screen, &position_piece_selected);
		}
	}
	if(is_small(game_piece(g, piece_selected)) && get_width(game_piece(g, piece_selected))!=get_height(game_piece(g, piece_selected))){
		if(is_horizontal(game_piece(g, piece_selected)))
			SDL_BlitSurface(horizontalPieceSelected, NULL, screen, &position_piece_selected);
		else
			SDL_BlitSurface(verticalPieceSelected, NULL, screen, &position_piece_selected);
	}
	position_cursor->x = get_x(game_piece(g, piece_selected));
	position_cursor->y = get_y(game_piece(g, piece_selected));
}

void display_game_rh(cgame g, SDL_Surface * screen){
	if(g==NULL || screen==NULL){
		fprintf(stderr, "display_game_rh : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	SDL_Rect position;

	SDL_Surface *verticalCar = NULL, *horizontalCar = NULL, *verticalTruck = NULL, *horizontalTruck = NULL, *redCar = NULL, *redArrow = NULL;
	verticalCar = IMG_Load("../img/verticalCar.png");
	horizontalCar = IMG_Load("../img/horizontalCar.png");
	verticalTruck = IMG_Load("../img/verticalTruck.png");
	horizontalTruck = IMG_Load("../img/horizontalTruck.png");
	redCar = IMG_Load("../img/redCar.png");
	redArrow = IMG_Load("../img/redArrowRh.png");

	position.x = 5 * BLOC_SIZE;
	position.y = 2 * BLOC_SIZE;
	SDL_BlitSurface(redArrow, NULL, screen, &position);
	for(int i=0 ; i<game_nb_pieces(g) ; i++){
		position.x = get_x(game_piece(g, i)) * BLOC_SIZE;
		position.y = (game_height(g)-get_height(game_piece(g, i))-get_y(game_piece(g, i))) * BLOC_SIZE;
		
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
}

void display_game_ar(cgame g, SDL_Surface * screen){
	if(g==NULL || screen==NULL){
		fprintf(stderr, "display_game_ar : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	SDL_Rect position;

	SDL_Surface *square = NULL, *smallPiece = NULL, *largeHorizontalPiece = NULL, *largeVerticalPiece = NULL, *redArrow = NULL;
	square = IMG_Load("../img/square.png");
	smallPiece = IMG_Load("../img/smallPiece.png");
	largeHorizontalPiece = IMG_Load("../img/largeHorizontalPiece.png");
	largeVerticalPiece = IMG_Load("../img/largeVerticalPiece.png");
	redArrow = IMG_Load("../img/redArrowAr.png");

	position.x = BLOC_SIZE;
	position.y = game_height(g)*BLOC_SIZE;
	SDL_BlitSurface(redArrow, NULL, screen, &position);
	for(int i=0 ; i<game_nb_pieces(g) ; i++){
		position.x = get_x(game_piece(g, i)) * BLOC_SIZE;
		position.y = (game_height(g)-get_height(game_piece(g, i))-get_y(game_piece(g, i))) * BLOC_SIZE;
		
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
}

void display_game(cgame g, SDL_Surface * screen, char game_type){
	if(g==NULL || screen == NULL || (game_type!='a' && game_type!='r')){
		fprintf(stderr, "display_game : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255,255,255));
	if(game_type=='r')
		display_game_rh(g, screen);
	else
		display_game_ar(g, screen);
}

void playing_piece(game g, int piece_selected, SDL_Surface * screen, char game_type, SDL_Rect * position_cursor){
	if(g==NULL || piece_selected<0 || piece_selected>=game_nb_pieces(g) || screen==NULL || (game_type!='a' && game_type!='r')){
		fprintf(stderr, "playing_piece : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}

	bool piece_on = true;
	SDL_Event event;
	dir d = RIGHT;

	while(!game_over(g, game_type) && piece_on){
		SDL_WaitEvent(&event);
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
					case SDLK_RETURN: // enter key main keyboard
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
		display_piece_selected(g, screen, game_type, piece_selected, position_cursor);
		SDL_Flip(screen);
	}
}

void graphic_game(game g, char game_type){
	if(g==NULL || (game_type!='a' && game_type!='r')){
		fprintf(stderr, "graphic_game : parametres incorrects.\n");
		exit(EXIT_FAILURE);
	}

	SDL_Surface * screen = NULL;
	SDL_Event event;
	SDL_Rect position_cursor;
	bool game_on = true;
	int piece_selected = -1;

	position_cursor.x = 0;
	position_cursor.y = 0;

	char * name = malloc(10);
	if(game_type=='a')
		strcpy(name,"Ane Rouge");
	else
		strcpy(name,"Rush Hour");

	if(SDL_Init(SDL_INIT_VIDEO)==-1){
		fprintf(stderr, "graphic_game : erreur chargement SDL : %s.\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	screen = SDL_SetVideoMode(BLOC_SIZE*game_width(g), BLOC_SIZE*game_height(g), 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption(name, NULL);

	while(!game_over(g, game_type) && game_on){
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_QUIT:
                game_on = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        game_on = false;
                        break;
                    case SDLK_RIGHT:
                    	if(piece_selected==-1 && position_cursor.x+1<game_width(g))
                    		position_cursor.x ++;
                    	else if(piece_selected!=-1 && position_cursor.x+get_width(game_piece(g, piece_selected))<game_width(g))
                    		position_cursor.x += get_width(game_piece(g, piece_selected));
                    	break;
                    case SDLK_LEFT:
                    	if(position_cursor.x-1>=0)
                    		position_cursor.x --;
                        break;
                    case SDLK_UP:
                    	if(piece_selected==-1 && position_cursor.y+1<game_height(g))
                    		position_cursor.y ++;
                    	else if (piece_selected!=-1 && position_cursor.y+get_height(game_piece(g, piece_selected))<game_height(g))
                    		position_cursor.y += get_height(game_piece(g, piece_selected));
                    	break;
                  	case SDLK_DOWN:
                  		if(position_cursor.y-1>=0)
                  			position_cursor.y --;
                  		break;
                    case SDLK_KP0:
                    	piece_selected=0;
                    	break;
                  	case SDLK_KP1:
                  		is_a_piece(g, &piece_selected, 1);
                  		break;
                 	case SDLK_KP2:
                  		is_a_piece(g, &piece_selected, 2);
                  		break;
                  	case SDLK_KP3:
                  		is_a_piece(g, &piece_selected, 3);
                  		break;
                  	case SDLK_KP4:
                  		is_a_piece(g, &piece_selected, 4);
                  		break;
                  	case SDLK_KP5:
                  		is_a_piece(g, &piece_selected, 5);
                  		break;
                  	case SDLK_KP6:
                  		is_a_piece(g, &piece_selected, 6);
                  		break;
                  	case SDLK_KP7:
                  		is_a_piece(g, &piece_selected, 7);
                  		break;
                  	case SDLK_KP8:
                  		is_a_piece(g, &piece_selected, 8);
                  		break;
                  	case SDLK_KP9:
                  		is_a_piece(g, &piece_selected, 9);
                  		break;
                    case SDLK_RETURN: // enter key main keyboard
                    	if(piece_selected!=-1)
                    		playing_piece(g, piece_selected, screen, game_type, &position_cursor);
                    	break;
                    default:
                    	break;
                }
                break;
            default:
            	break;
		}
		piece_selected = game_square_piece(g, position_cursor.x, position_cursor.y);
		display_game(g, screen, game_type);
		display_piece_hovered(g, screen, game_type, piece_selected, &position_cursor);
		SDL_Flip(screen);
	}
	free(name);
	SDL_FreeSurface(screen);
	SDL_Quit();
}