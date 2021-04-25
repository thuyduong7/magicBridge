#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL.h>

#include "Materials.h"

struct Background
{
    Background(MAT_TYPE _type);
    ~Background();

    void render(SDL_Renderer* renderer);
    void renderOffset(SDL_Renderer* renderer);

    SDL_Texture* texture;
    Materials backgroundMat;
    SDL_Rect srcRect, dstRect;
    int posX, posY;
    int width, height;
    double offset;
};

#endif // BACKGROUND_H

