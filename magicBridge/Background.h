#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL.h>

struct Background
{
    Background();
    ~Background();

    void load();
    void render();

    SDL_Texture* texture;
    SDL_Rect srcRect, dstRect;
    int posX, posY;
    int width, height;
};

#endif // BACKGROUND_H

