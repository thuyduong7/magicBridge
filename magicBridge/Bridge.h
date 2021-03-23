#ifndef BRIDGE_H
#define BRIDGE_H

#include <SDL.h>
#include <SDL_image.h>

const int NUM_OF_DOTS = 11;

enum DIRECTION
{
    LEFT,
    RIGHT,
    TOTAL_OF_DIRECTION
};

//The height and width of dots instituting the bridge
const int DOT_HEIGHT = 40;
const int DOT_WIDTH = 40;


//The max y that bridge can fall down to
const int MAX_POS_Y = 740;

struct Bridge
{
    Bridge();
    ~Bridge();

    void setDir(DIRECTION _dir);
    void update();
    void render();

    int width, height;
    int posX, posY;
    DIRECTION dir;
    SDL_Texture* texture;
    SDL_Rect srcRect, dstRect;
};

#endif // BRIDGE_H
