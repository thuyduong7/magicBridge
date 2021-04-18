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

void Spike::move()
{
    posY += velY;
}

bool Spike::checkCollision(Yolk* yolk)
{
    collider.w = (SPIKE_WIDTH*2)/5;
    collider.h = (SPIKE_HEIGHT*2)/5;
    collider.x = posX + (collider.w/2);
    collider.y = posY + (collider.h/2);
    Enemy::checkCollision(yolk);
}

void Spike::render(SDL_Renderer* renderer, bool& quit)
{
    srcRect = enemyMat.getSprite(SPIKE, RUN, frame/FRAME_VALUE);
    dstRect = {posX, posY, width, height};
    // If Spike cling on the right wall, its texture will be flipped
    if (posX == MAX_POS_X - SPIKE_WIDTH)
        enemyMat.render(renderer, texture, srcRect, dstRect, SDL_FLIP_HORIZONTAL);
    else enemyMat.render(renderer, texture, srcRect, dstRect);
    if (!quit) frame++;
    if (frame/FRAME_VALUE >= TOTAL_SPIKE_SPRITE) frame = 0;
}

void Spike::free()
{
    Enemy::free();
}

