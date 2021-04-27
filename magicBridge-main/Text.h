#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

struct Text
{
    Text();
    ~Text();
    bool loadText(SDL_Renderer* renderer, string text, int size, SDL_Color textColor);
    bool loadFromRenderedText(SDL_Renderer* renderer, string textureText, SDL_Color textColor);
    void render(SDL_Renderer* renderer, int x, int y);
    void free();

    SDL_Texture* texture;
    int width, height;
};

#endif // TEXT_H
