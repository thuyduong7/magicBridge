#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include <SDL_image.h>

#include "Materials.h"

const int START_BUTTON_WIDTH = 326;
const int START_BUTTON_HEIGHT = 135;

const int HELP_BUTTON_WIDTH = 34;
const int HELP_BUTTON_HEIGHT = 32;

const int PAUSE_BUTTON_WIDTH = 35;
const int PAUSE_BUTTON_HEIGHT = 32;

const int CONTINUE_BUTTON_WIDTH = 201;
const int CONTINUE_BUTTON_HEIGHT = 151;

const int QUIT_BUTTON_WIDTH = 34;
const int QUIT_BUTTON_HEIGHT = 32;

enum BUTTONSPRITE
{
	BUTTON_SPRITE_MOUSE_OUT,
	BUTTON_SPRITE_MOUSE_OVER_MOTION,
	BUTTON_SPRITE_TOTAL
};

struct Button
{
    //Initializes internal variables
    Button(MAT_TYPE _type);

    //Sets top left position
    void setPosition( int x, int y );

    //Handles mouse event
    void handleEvent( SDL_Event& e );

    //Shows button sprite
    void render(SDL_Renderer* renderer);

    //Top left position
    SDL_Rect position;

    //Currently used global sprite
    BUTTONSPRITE currentSprite;
    MAT_TYPE type;
    Materials buttonMat;
    SDL_Texture* texture;
    bool click;
};
#endif // BUTTON_H
