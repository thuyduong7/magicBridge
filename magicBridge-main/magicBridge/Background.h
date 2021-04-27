#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL.h>

#include "Materials.h"

const double BACKGROUND_VEL = 2;
const double BACKGROUND_LAYER_VEL = 1.5;
const int INTRO_FRAME_VALUE = 10;

struct Background
{
    Background(MAT_TYPE _type);
    ~Background();

    void move(const double mul);
    void render(SDL_Renderer* renderer);
    void renderOffset(SDL_Renderer* renderer);
    void renderIntro(SDL_Renderer* renderer);

    SDL_Texture* texture;
    Materials backgroundMat;
    SDL_Rect srcRect, dstRect;
    int posX, posY;
    int width, height;
    double vel,offset;
    int frame;
};


#endif // BACKGROUND_H

