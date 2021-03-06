#include "Bridge.h"
#include "Core.h"

Bridge::Bridge()
{
    width = DOT_WIDTH;
    height = DOT_HEIGHT;
    posX = 0;
    posY = 0;
    dir = TOTAL_OF_DIRECTION;
    srcRect = {posX, posY, width, height};
    texture = bridgeMat.getTexture(BRIDGE);
}

Bridge::~Bridge()
{

}

void Bridge::getTexture(MAT_TYPE _type)
{
    texture = bridgeMat.getTexture(_type);
}

bool Bridge::move(Bridge* bridge)
{
    bool moved = false;
    if (bridge->dir == LEFT){
        moved = true;
        if (bridge[0].posY < MAX_POS_Y){
            //move = true;
            for (int i = 0; i < NUM_OF_DOTS; i++){
                // (i-NUM_OF_DOTS/2) to return a symmetry  ( -5 -4 -3 -2 -1 0 1 2 3 4 5 )
                // *3 to increase the speed of the bridge coming up and down
                // The dot in the middle remains the same
                bridge[i].posY -= (i - NUM_OF_DOTS/2);
            }
        }
    }
    if (bridge->dir == RIGHT){
        //move = true;
        if (bridge[NUM_OF_DOTS-1].posY < MAX_POS_Y){
            moved = true;
            for (int i = 0; i < NUM_OF_DOTS; i++){
                // (i-NUM_OF_DOTS/2) to return a symmetry  ( -5 -4 -3 -2 -1 0 1 2 3 4 5 )
                // *3 to increase the speed of the bridge coming up and down
                // The dot in the middle remains the same
                bridge[i].posY += (i - NUM_OF_DOTS/2);
            }
        }
    }
    return moved;
}

void Bridge::render(SDL_Renderer* renderer)
{
    dstRect = {posX, posY, width, height};
    bridgeMat.render(renderer, texture, srcRect, dstRect);
}
