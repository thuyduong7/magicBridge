#ifndef BRIDGE_H
#define BRIDGE_H

#include "Materials.h"

//Bridge includes 9 dots
const int NUM_OF_DOTS = 9;

enum DIRECTION
{
    LEFT,
    RIGHT,
    TOTAL_OF_DIRECTION
};

//The height and width of dots instituting the bridge
const int DOT_HEIGHT = 40;
const int DOT_WIDTH = 40;

struct Bridge
{
    Bridge();
    ~Bridge();

    void getTexture(MAT_TYPE _type);
    bool move(Bridge* bridge);
    void render(SDL_Renderer* renderer);

    int width, height;
    int posX, posY;
    DIRECTION dir;
    SDL_Rect srcRect, dstRect;
    SDL_Texture* texture;
    Materials bridgeMat;
};

#endif // BRIDGE_H
