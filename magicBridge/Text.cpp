#include "Text.h"

TTF_Font* font = NULL;

Text::Text()
{
    texture = NULL;
    width = 0;
    height = 0;
}

Text::~Text()
{

}

bool Text::loadText(SDL_Renderer* renderer, string text, int size, SDL_Color textColor)
{
    bool success = true;

    font = TTF_OpenFont("Font/04B_30__.TTF", size);
    if (font == NULL){
        cout << "Fail to load font! SDL_ttf Error: " << TTF_GetError();
        success = false;
    } else {
        if (!loadFromRenderedText(renderer, text, textColor)){
            cout << "Fail to render text texture!";
            success = false;
        }
    }
    return success;
}

bool Text::loadFromRenderedText(SDL_Renderer* renderer, string textureText, SDL_Color textColor)
{
    free();
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    if (textSurface == NULL){
        cout << "Unable to render text surface! TTF_Error: " << TTF_GetError();
    }
    else{
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (texture == NULL){
            cout << "Unable to create texture from rendered text! SDL_Error: " << SDL_GetError();
        }
        else{
            width = textSurface->w;
            height = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
    return texture != NULL;
}

void Text::render(SDL_Renderer* renderer, int x, int y)
{
    SDL_Rect dstRect = {x,y,width,height};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
}

void Text::free()
{
    if (texture != NULL){
        SDL_DestroyTexture(texture);
        width = 0;
        height = 0;
    }
}
