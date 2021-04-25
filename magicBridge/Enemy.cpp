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
            break;
        case SPIKEBALL:
            width = SPIKEBALL_WIDTH;
            height = SPIKEBALL_HEIGHT;
            break;
        case COIN:
            width = COIN_WIDTH;
            height = COIN_HEIGHT;
            totalSprite = TOTAL_COIN_SPRITE;
    }
    posX = 0;
    posY = 0;
    velY = VEL_Y;
    srcRect = {0,0,width,height};
    frame = 0;
    multiple = 1;
}

bool Enemy::checkCollision(Yolk* yolk)
{
    double leftYolk, leftEnemy;
    double rightYolk, rightEnemy;
    double topYolk, topEnemy;
    double bottomYolk, bottomEnemy;

    leftEnemy = posX + double(width/3);
    rightEnemy = leftEnemy + double(width/3);
    topEnemy = posY + double(height/3);
    bottomEnemy = topEnemy + double(height/3);

    //cout << leftEnemy << ' ' << rightEnemy << ' ' << topEnemy << ' ' << bottomEnemy << endl;
    //cout << yolk->posX << ' ' << yolk->posX + yolk->width << ' ' << yolk->posY << ' ' << yolk->posY + yolk->height << endl;

    // (MIN_POS_Y,MAX_POS_Y) is the space where the collision could occur
    if (bottomEnemy < (MIN_POS_Y - YOLK_HEIGHT)) return false;
    if (topEnemy > MAX_POS_Y) return false;

    leftYolk = yolk->posX;
    rightYolk = yolk->posX + yolk->width;
    topYolk = yolk->posY;
    bottomYolk = yolk->posY + yolk->height;

    //cout << leftYolk << ' ' << rightYolk << ' ' << topYolk << ' ' << bottomYolk << endl;
    //cout << "////\n";

    if( bottomYolk <= topEnemy )
    {
        return false;
    }

    if( topYolk >= bottomEnemy )
    {
        return false;
    }

    if( rightYolk <= leftEnemy )
    {
        return false;
    }

    if( leftYolk >= rightEnemy )
    {
        return false;
    }
    return true;
}

void Enemy::free()
{
    //SDL_DestroyTexture(texture);
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
