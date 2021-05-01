#ifndef BUTTON_H
#define BUTTON_H

#include "Materials.h"

const int START_BUTTON_WIDTH = 326;
const int START_BUTTON_HEIGHT = 135;

const int HELP_BUTTON_WIDTH = 34;
const int HELP_BUTTON_HEIGHT = 32;

const int SETTINGS_BUTTON_WIDTH = 32;
const int SETTINGS_BUTTON_HEIGHT = 32;

const int TICK_BUTTON_WIDTH = 60;
const int TICK_BUTTON_HEIGHT = 60;

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
    Button(MAT_TYPE _type);
    void setPosition(const int& x, const int& y);
    void handleEvent(const SDL_Event& e);
    void render(SDL_Renderer* renderer);

    SDL_Rect position;
    BUTTONSPRITE currentSprite;
    MAT_TYPE type;
    Materials buttonMat;
    SDL_Texture* texture;
    bool click;
};
#endif // BUTTON_H
