#include "Bird.h"

Bird::Bird() : Enemy(BIRD)
{
    posY = -BIRD_HEIGHT;
    velY = BIRD_VEL_Y;
}

Bird::~Bird()
{

}

void Bird::setPos()
{
    dir = DIRECTION(rand() % 2);
    distance = (rand() % (PLAYING_SCREEN_WIDTH-BIRD_WIDTH));
    if (distance < MIN_BIRD_DISTANCE) distance = MIN_BIRD_DISTANCE;
    minX = (rand() % (PLAYING_SCREEN_WIDTH - distance - BIRD_WIDTH)) + MIN_POS_X;
    maxX = minX + distance;
    posX = (rand()%distance) + minX;
}

void Bird::move(const double& mul)
{

    posY += (velY * mul);

    if (dir == RIGHT){
        posX += (BIRD_VEL_X * mul);
        if (posX < minX || posX > maxX){
            dir = LEFT;
            posX -= (BIRD_VEL_X * mul);
        }
        flip = SDL_FLIP_NONE;
    }
    else if (dir == LEFT){
        posX -= (BIRD_VEL_X * mul);
        if (posX < minX || posX > maxX){
            dir = RIGHT;
            posX += (BIRD_VEL_X * mul);
        }
        flip = SDL_FLIP_HORIZONTAL;
    }
}

bool Bird::checkCollision(Yolk* yolk)
{
    if (yolk->state == PAUSE_1) return false;
    collider.w = (BIRD_WIDTH*3)/5;
    collider.h = (BIRD_HEIGHT*3)/5;
    collider.x = posX;
    collider.y = posY;
    Enemy::checkCollision(yolk);
}

void Bird::render(SDL_Renderer* renderer, STATE state)
{
    srcRect = enemyMat.getSprite(BIRD, RUN, frame/FRAME_VALUE);
    dstRect = {posX, posY, width, height};
    enemyMat.render(renderer, texture, srcRect, dstRect, flip);
    if (state != HIT_2) frame++;
    if (frame/FRAME_VALUE >= (TOTAL_BIRD_SPRITE)) frame = 0;
}
