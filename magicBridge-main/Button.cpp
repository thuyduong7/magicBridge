#include "Button.h"


//Mouse button sprites
SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];
//LTexture gButtonSpriteSheetTexture;

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

void Button::setPosition( int x, int y )
{
	position.x = x;
	position.y = y;
}

void Button::handleEvent( SDL_Event& e )
{
	//If mouse event happened
	if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;
		click = false;

		//Mouse is left of the button
		if( x < position.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > position.x + position.w )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < position.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > position.y + position.h )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			currentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
            currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
            if (e.type == SDL_MOUSEBUTTONDOWN) click = true;
		}
	}
}

void Button::render(SDL_Renderer* renderer)
{
	//Show current button sprite
	buttonMat.render(renderer, texture, buttonMat.getSprite(type, IDLE, currentSprite) , position);
}

