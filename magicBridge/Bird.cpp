#include "Bird.h"

double BIRD_VEL = 0.5;

Bird::Bird() : Enemy(BIRD)
{
}

void Bird::setPos()
{
    side = SIDE(rand() % 2);
    dir = DIRECTION(rand() % 2);
    if (side == _LEFT) {
        posX = rand()%(SCREEN_WIDTH*2/3 - BIRD_WIDTH);
        minX = 0;
        maxX = SCREEN_WIDTH*2/3 - BIRD_WIDTH;
    }
    else {
        posX = rand()%(SCREEN_WIDTH*2/3 - BIRD_WIDTH) + SCREEN_WIDTH*1/3;
        minX = SCREEN_WIDTH*1/3;
        maxX = SCREEN_WIDTH - BIRD_WIDTH;
    }
    //cout << side << ' ' << dir << ' ' << minX << ' ' << maxX << endl;
}

void Bird::move()
{

    posY++;

    if (dir == RIGHT){
        posX += BIRD_VEL;
        if (posX < minX || posX > maxX){
            dir = LEFT;
            posX -= BIRD_VEL;
        }
        flip = SDL_FLIP_NONE;
    }
    else if (dir == LEFT){
        posX -= BIRD_VEL;
        if (posX < minX || posX > maxX){
            dir = RIGHT;
            posX += BIRD_VEL;
        }
        flip = SDL_FLIP_HORIZONTAL;
    }
}

void Bird::render(SDL_Renderer* renderer)
{
    srcRect = enemyMat.getSprite(BIRD, RUN, frame/FRAME_VALUE);
    dstRect = {posX, posY, width, height};
    enemyMat.render(renderer, texture, srcRect, dstRect, flip);
    frame++;
    if (frame/FRAME_VALUE >= (TOTAL_BIRD_SPRITE)) frame = 0;
}
