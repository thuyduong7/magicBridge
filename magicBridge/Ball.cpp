#include "Ball.h"

Ball::Ball() : Enemy(SPIKEBALL)
{
    setBall = false;
}

Ball::~Ball()
{

}

void Ball::render(SDL_Renderer* renderer, STATE state)
{
    dstRect = {posX, posY, width, height};
    enemyMat.render(renderer, texture, srcRect, dstRect);
}

void Ball::free()
{
    Enemy::free();
}
