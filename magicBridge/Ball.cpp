#include "Ball.h"

Ball::Ball() : Enemy(SPIKEBALL)
{
}

void Ball::render(SDL_Renderer* renderer)
{
    dstRect = {posX, posY, width, height};
    enemyMat.render(renderer, texture, srcRect, dstRect);
}
