#include "Button.h"

Button::Button(MAT_TYPE _type)
{
	position.x = 0;
	position.y = 0;
	type = _type;
	texture = buttonMat.getTexture(type);
	switch (type)
	{
        case START_BUTTON:
            position.w = START_BUTTON_WIDTH;
            position.h = START_BUTTON_HEIGHT;
            break;

        case HELP_BUTTON:
            position.w = HELP_BUTTON_WIDTH;
            position.h = HELP_BUTTON_HEIGHT;
            break;

        case PAUSE_BUTTON:
            position.w = PAUSE_BUTTON_WIDTH;
            position.h = PAUSE_BUTTON_HEIGHT;
            break;

        case CONTINUE_BUTTON:
            position.w = CONTINUE_BUTTON_WIDTH;
            position.h = CONTINUE_BUTTON_HEIGHT;
            break;

        case QUIT_BUTTON:
            position.w = QUIT_BUTTON_WIDTH;
            position.h = QUIT_BUTTON_HEIGHT;
            break;
	}
	click = false;
	currentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void Button::setPosition(const int& x, const int& y)
{
	position.x = x;
	position.y = y;
}

void Button::handleEvent(const SDL_Event& e)
{
	if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = true;
		click = false;

		if(x < position.x) inside = false;
		else if(x > position.x + position.w) inside = false;
		else if(y < position.y) inside = false;
		else if(y > position.y + position.h) inside = false;

		if(!inside) currentSprite = BUTTON_SPRITE_MOUSE_OUT;
		else{
            currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
            if (e.type == SDL_MOUSEBUTTONDOWN) click = true;
		}
	}
}

void Button::render(SDL_Renderer* renderer)
{
	buttonMat.render(renderer, texture, buttonMat.getSprite(type, IDLE, currentSprite) , position);
}

