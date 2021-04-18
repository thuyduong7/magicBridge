#include "Radish.h"

double RADISH_VEL_X = 0.5;
int MAX_MOVE = 60;

Radish::Radish() : Enemy(RADISH)
{
    posY = -RADISH_HEIGHT;
    defaultPosX = posX;
    dir = RIGHT;
    time = 0;
}

Radish::~Radish()
{
}

void Radish::setPos()
{
    // "-int(RADISH_VEL_X * MAX_MOVE)" "+(RADISH_VEL_X * MAX_MOVE)" let enough space for radish to move in zigzag
    posX = rand()%(PLAYING_SCREEN_WIDTH - RADISH_WIDTH - int(RADISH_VEL_X * MAX_MOVE)) + (MIN_POS_X + RADISH_VEL_X * MAX_MOVE);
    defaultPosX = posX;
    //cout << posX << ' ';
}

//int LEFT_MAX = 5;

void Radish::move()
{
    posY += velY;
    if (dir == RIGHT){
        if (time == MAX_MOVE){
            time = 0;
            dir = LEFT;
            return;
        }
        posX -= RADISH_VEL_X;
        time++;
    }
    else if (dir == LEFT){
        if (time == MAX_MOVE){
            time = 0;
            dir = RIGHT;
            return;
        }
        posX += RADISH_VEL_X;
        time++;
    }
}

bool Radish::checkCollision(Yolk* yolk)
{
    collider.w = (RADISH_WIDTH*3)/5;
    collider.h = (RADISH_HEIGHT*3)/5;
    collider.x = posX + (collider.w/2);
    collider.y = posY + (collider.h/2);
    //cout << collider.w << ' ' << collider.h << ' ' << collider.x << ' ' << collider.y << endl;
    Enemy::checkCollision(yolk);
}

void Radish::render(SDL_Renderer* renderer, bool& quit)
{
    srcRect = enemyMat.getSprite(RADISH, RUN, frame/FRAME_VALUE);
    dstRect = {posX, posY, width, height};
    enemyMat.render(renderer, texture, srcRect, dstRect);
    if (!quit) frame++;
    if (frame/FRAME_VALUE >= TOTAL_RADISH_SPRITE) frame = 0;
}

void Radish::free()
{
    Enemy::free();
}

