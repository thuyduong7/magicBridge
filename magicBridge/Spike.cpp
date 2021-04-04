#include "Spike.h"

Spike::Spike() : Enemy(SPIKE)
{

}

void Spike::setPos()
{
    //Set the side of the wall for Spike to move on
    dir = DIRECTION(rand() % 2);
    //randDir = rand() % 2;
    if (dir == LEFT){
        //dir = LEFT;
        posX = 0;
    }
    else {
        //dir = RIGHT;
        posX = SCREEN_WIDTH - SPIKE_WIDTH;
    }
}

void Spike::move()
{
    posY++;
}

void Spike::render(SDL_Renderer* renderer)
{
    srcRect = enemyMat.getSprite(SPIKE, RUN, frame/FRAME_VALUE);
    dstRect = {posX, posY, width, height};
    // If Spike cling on the right wall, its texture will be flipped
    if (posX == SCREEN_WIDTH - SPIKE_WIDTH)
        enemyMat.render(renderer, texture, srcRect, dstRect, SDL_FLIP_HORIZONTAL);
    else enemyMat.render(renderer, texture, srcRect, dstRect);
    move();
    frame++;
    if (frame/FRAME_VALUE >= TOTAL_SPIKE_SPRITE) frame = 0;
}

