#include "Radish.h"

double RADISH_VEL = 0.25;
int MAX_MOVE = 50;

Radish::Radish() : Enemy(RADISH)
{
    defaultPosX = posX;
    dir = RIGHT;
    time = 0;
}

void Radish::setPos()
{
    // "-int(RADISH_VEL * MAX_MOVE)" "+(RADISH_VEL * MAX_MOVE)" let enough space for radish to move in zigzag
    posX = rand()%(SCREEN_WIDTH - RADISH_WIDTH - int(RADISH_VEL * MAX_MOVE)) + (RADISH_VEL * MAX_MOVE);
    defaultPosX = posX;
    //cout << posX << ' ';
}

//int LEFT_MAX = 5;

void Radish::move()
{
    posY++;
    if (dir == RIGHT){
        if (time == MAX_MOVE){
            time = 0;
            dir = LEFT;
            return;
        }
        posX -= RADISH_VEL;
        time++;
    }
    else if (dir == LEFT){
        if (time == MAX_MOVE){
            time = 0;
            dir = RIGHT;
            return;
        }
        posX += RADISH_VEL;
        time++;
    }
}

void Radish::render(SDL_Renderer* renderer)
{
    srcRect = enemyMat.getSprite(RADISH, RUN, frame/FRAME_VALUE);
    dstRect = {posX, posY, width, height};
    enemyMat.render(renderer, texture, srcRect, dstRect);
    frame++;
    if (frame/FRAME_VALUE >= TOTAL_RADISH_SPRITE) frame = 0;
}

Radish::~Radish()
{
    SDL_DestroyTexture(texture);
}

