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
            break;
        case BIRD:
            width = BIRD_WIDTH;
            height = BIRD_HEIGHT;
            totalSprite = TOTAL_BIRD_SPRITE;
    }
    posX = 0;
    posY = 0;
    srcRect = {0,0,width,height};
    frame = 0;
}

/**
SDL_Texture* Enemy::getTexture()
{
    return enemyMat.getTexture(type);
}


void Enemy::setPos()
{
    //int randDir;
    switch(type)
    {
        case RADISH:
            posX = rand()%(SCREEN_WIDTH - RADISH_WIDTH);
            break;
        case SPIKE:
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
            break;
        case BIRD:
            dir = DIRECTION(rand() % 2);
            if (dir == LEFT) {
                    //dir = LEFT;
                    posX = rand()%(SCREEN_WIDTH*2/3 - RADISH_WIDTH);
            }
            else {
                    //dir = RIGHT;
                    posX = rand()%(SCREEN_WIDTH*2/3 - RADISH_WIDTH) + SCREEN_WIDTH*1/3;
            }
    }
}

void Enemy::move()
{
    switch(type)
    {
        case RADISH:

            posY++;
            break;
        case SPIKE:
            posY++;
            break;
        case BIRD:
            posY++;
            if (dir == LEFT)
            break;
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
    //posY++;
    move();
    if (frame/FRAME_VALUE >= totalSprite) frame = 0;
}
*/
