#include "Yolk.h"
#include "Core.h"
#include "Materials.h"

#include <iostream>
using namespace std;

Yolk::Yolk(int x, int y)
{
    width = YOLK_WIDTH;
    height = YOLK_HEIGHT;
    posX = x;
    posY = y;
    velX = 0;
    texture = yolkMat.getTexture(YOLK);
    dir = TOTAL_OF_DIRECTION;
    last_dir = TOTAL_OF_DIRECTION;
    srcRect = {posX, posY, width, height};
    frame = 0;
    change_dir = false;
    time = 0;
}

Yolk::~Yolk()
{

}
/**
SDL_Rect* Yolk::setSprite(SDL_Rect* spriteSheet)
{
    for (int i = 0; i < TOTAL_YOLK_RUN_SPRITE; i++){
        spriteSheet[i].x = YOLK_WIDTH * i;
        spriteSheet[i].y = 0;
        spriteSheet[i].w = YOLK_WIDTH;
        spriteSheet[i].h = YOLK_HEIGHT;
    }
    return spriteSheet;
}
*/

void Yolk::setDir(DIRECTION _dir)
{
    //dir.push(_dir);
    dir = _dir;
}

void Yolk::run(double _gap)
{
    gap = abs(_gap);
    /**
    if (!dir.empty()){
        cur_dir = dir.front();
        dir.pop();
    }
    */
    if (_gap < 0) dir = RIGHT;
    else dir = LEFT;
    if (last_dir != dir && last_dir != TOTAL_OF_DIRECTION){
        // If Yolk is on the edge of the screen, Yolk will change direction immediately (velX = 0)
        // Or else he will move in his last direction for a short time before changing direction
        if (posX > 0 && posX < SCREEN_WIDTH-YOLK_WIDTH) change_dir = true;
        else velX = 0;
            //time = 0;
    }
    last_dir = dir;
}

void Yolk::move(Bridge* bridge)
{
    if (change_dir == true){
        time++;
        if (dir == LEFT) velX += gap/800;
        else velX -= gap/800;
        posX += velX;
        if (posX <= 0) posX = 0;
        if (posX >= SCREEN_WIDTH - YOLK_WIDTH) posX = SCREEN_WIDTH - YOLK_WIDTH;
        if (time == 20){
            velX = 0;
            time = 0;
            change_dir = false;
        }
    }
    else if (dir == LEFT && posX > 0 && bridge[0].posY > BRIDGE_IDLE_HEIGHT){
        velX -= gap/400;
        posX += velX;
        if (posX <= 0){
            posX = 0;
            dir = TOTAL_OF_DIRECTION;
        }
    }
    else if (dir == RIGHT && posX < SCREEN_WIDTH-YOLK_WIDTH && bridge[0].posY < BRIDGE_IDLE_HEIGHT){
        velX += gap/400;
        posX += velX;
        if (posX >= SCREEN_WIDTH - YOLK_WIDTH){
            posX = SCREEN_WIDTH - YOLK_WIDTH;
            dir = TOTAL_OF_DIRECTION;
        }
    }
    if (dir != TOTAL_OF_DIRECTION)
        posY = bridge[int(nearbyint((posX/DOT_WIDTH)))].posY - YOLK_HEIGHT;

}


void Yolk::render(SDL_Renderer* renderer, Bridge* bridge)
{
    //Set the default sprite of Yolk
    srcRect = yolkMat.getSprite(YOLK, IDLE);
    //When the bridge is inclined and Yolk is not at the edge of the screen
    if (posX != 0 && posX != (SCREEN_WIDTH - YOLK_WIDTH) && bridge[0].posY != BRIDGE_IDLE_HEIGHT)
        srcRect = yolkMat.getSprite(YOLK, RUN, frame/YOLK_FRAME_VALUE);

    dstRect = {posX, posY, width, height};

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if ( (dir == RIGHT && change_dir == false) || (dir == LEFT && change_dir == true) ||
        (posX == SCREEN_WIDTH - YOLK_WIDTH) || (last_dir == RIGHT && gap == 0) )
        flip = SDL_FLIP_HORIZONTAL;

    yolkMat.render(renderer, texture, srcRect, dstRect, flip);

    if (dir != TOTAL_OF_DIRECTION && posX != 0 && bridge[0].posY != BRIDGE_IDLE_HEIGHT) frame++;
    if (frame/YOLK_FRAME_VALUE >= TOTAL_YOLK_RUN_SPRITE) frame = 0;
}

