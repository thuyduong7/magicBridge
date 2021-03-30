#include "Enemy.h"
#include "Core.h"

Enemy::Enemy(MAT_TYPE _type)
{
    type = _type;
    texture = enemyMat.getTexture(type);
    switch (type)
    {
        case RADISH:
            width = RADISH_WIDTH;
            height = RADISH_HEIGHT;
            totalSprite = TOTAL_RADISH_SPRITE;
            break;
        case SPIKE:
            width = SPIKE_WIDTH;
            height = SPIKE_HEIGHT;
            totalSprite = TOTAL_SPIKE_SPRITE;
    }
    posX = 0;
    posY = 0;
    srcRect = {0,0,width,height};
    frame = 0;
}

SDL_Texture* Enemy::getTexture()
{
    return enemyMat.getTexture(type);
}

void Enemy::setPos(MAT_TYPE _type)
{
    switch(type)
    {
        case RADISH:
            posX = rand()%(SCREEN_WIDTH-RADISH_WIDTH);
            break;
        case SPIKE:
            //Set the side of the wall for Spike to move on
            // dir = 0: LEFT
            // dir = 1: RIGHT
            int dir = rand() % 2;
            if (dir == 0) posX = 0;
            else posX = SCREEN_WIDTH - SPIKE_WIDTH;
    }
}

void Enemy::render(SDL_Renderer* renderer)
{
    srcRect = enemyMat.getSprite(type, RUN, frame/FRAME_VALUE);
    dstRect = {posX, posY, width, height};
    // If Spike cling on the right wall, its texture will be flipped
    if (type == SPIKE && posX == SCREEN_WIDTH - SPIKE_WIDTH)
        enemyMat.render(renderer, texture, srcRect, dstRect, SDL_FLIP_HORIZONTAL);
    else enemyMat.render(renderer, texture, srcRect, dstRect);
    frame++;
    posY++;
    if (frame/FRAME_VALUE >= totalSprite) frame = 0;
}
