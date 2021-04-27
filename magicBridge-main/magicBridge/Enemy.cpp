#include "Enemy.h"

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
    srcRect = {posX,posY,width,height};
    frame = 0;
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

    // (MIN_POS_Y,MAX_POS_Y) is the space where the collision could occur
    if (bottomEnemy < (MIN_POS_Y - YOLK_HEIGHT)) return false;
    if (topEnemy > MAX_POS_Y) return false;

    leftYolk = yolk->posX;
    rightYolk = yolk->posX + yolk->width;
    topYolk = yolk->posY;
    bottomYolk = yolk->posY + yolk->height;

    if (bottomYolk <= topEnemy) return false;

    if (topYolk >= bottomEnemy) return false;

    if (rightYolk <= leftEnemy) return false;

    if (leftYolk >= rightEnemy) return false;
    return true;
}
