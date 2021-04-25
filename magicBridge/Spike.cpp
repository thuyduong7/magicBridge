#include "Spike.h"

Spike::Spike() : Enemy(SPIKE)
{
    posY = -SPIKE_HEIGHT;
    velY = SPIKE_VEL_Y;
}

Spike::~Spike()
{

}

void Spike::setPos()
{
    //Set the side of the wall for Spike to move on
    dir = DIRECTION(rand() % 2);
    //randDir = rand() % 2;
    if (dir == LEFT){
        //dir = LEFT;
        posX = MIN_POS_X;
    }
    else {
        //dir = RIGHT;
        posX = MAX_POS_X - SPIKE_WIDTH;
    }
}

void Spike::move(double mul)
{
    posY += (velY * mul);
}

bool Spike::checkCollision(Yolk* yolk)
{
    if (yolk->state == PAUSE_1) return false;
    collider.w = (SPIKE_WIDTH*1)/2;
    collider.h = (SPIKE_HEIGHT*1)/2;
    collider.x = posX + (SPIKE_WIDTH/4);
    collider.y = posY + (SPIKE_HEIGHT/4);
    Enemy::checkCollision(yolk);
}

void Spike::render(SDL_Renderer* renderer, STATE state)
{
    srcRect = enemyMat.getSprite(SPIKE, RUN, frame/FRAME_VALUE);
    dstRect = {posX, posY, width, height};
    // If Spike cling on the right wall, its texture will be flipped
    if (posX == MAX_POS_X - SPIKE_WIDTH)
        enemyMat.render(renderer, texture, srcRect, dstRect, SDL_FLIP_HORIZONTAL);
    else enemyMat.render(renderer, texture, srcRect, dstRect);
    if (state != HIT_2) frame++;
    if (frame/FRAME_VALUE >= TOTAL_SPIKE_SPRITE) frame = 0;
}

void Spike::free()
{
    Enemy::free();
}

