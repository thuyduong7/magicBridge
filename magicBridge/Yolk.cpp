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
    cur_dir = TOTAL_OF_DIRECTION;
    last_cur_dir = TOTAL_OF_DIRECTION;
    srcRect = {posX, posY, width, height};
    frame = 0;
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
    dir.push(_dir);
}

void Yolk::run(double _gap)
{
    gap = abs(_gap);
    last_cur_dir = cur_dir;
    if (!dir.empty()){cur_dir = dir.front();
    dir.pop();
    }
    if (_gap < 0) cur_dir = RIGHT;
    else cur_dir = LEFT;
    if (last_cur_dir != cur_dir) velX = 0;

}

void Yolk::move(Bridge* bridge)
{
    if (cur_dir == LEFT && posX > 0 && bridge[0].posY > BRIDGE_IDLE_HEIGHT){
        velX -= gap/30;
        posX += velX/30;
        cout << velX << ' ' << posX << endl;
        if (posX <= 0){
            posX = 0;
            cur_dir = TOTAL_OF_DIRECTION;
        }
    }
    if (cur_dir == RIGHT && posX < SCREEN_WIDTH-YOLK_WIDTH && bridge[0].posY < BRIDGE_IDLE_HEIGHT){
        velX += gap/30;
        posX += velX/30;
        cout << velX << ' ' << posX << endl;
        if (posX >= SCREEN_WIDTH - YOLK_WIDTH){
            posX = SCREEN_WIDTH - YOLK_WIDTH;
            cur_dir = TOTAL_OF_DIRECTION;
        }
    }
    if (cur_dir != TOTAL_OF_DIRECTION){
        posY = bridge[int(nearbyint((posX/DOT_WIDTH)))].posY - YOLK_HEIGHT;
        cout << int(nearbyint(posX/DOT_WIDTH)) << ' ' <<  bridge[int(nearbyint(posX/DOT_WIDTH))].posY << ' ' << posY << endl;
    }
}

void Yolk::checkCollision(Enemy enemy)
{

}

void Yolk::render(SDL_Renderer* renderer, Bridge* bridge)
{
    //Set the default sprite of Yolk
    srcRect = yolkMat.getSprite(YOLK, IDLE);
    //When the bridge is inclined and Yolk is not at the edge of the screen
    if (posX != 0 && posX != SCREEN_WIDTH - YOLK_WIDTH && bridge[0].posY != BRIDGE_IDLE_HEIGHT)
        srcRect = yolkMat.getSprite(YOLK, RUN, frame/YOLK_FRAME_VALUE);

    dstRect = {posX, posY, width, height};

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (cur_dir == RIGHT || posX == SCREEN_WIDTH - YOLK_WIDTH || (last_cur_dir == RIGHT && gap == 0))
        flip = SDL_FLIP_HORIZONTAL;

    yolkMat.render(renderer, texture, srcRect, dstRect, flip);

    if (cur_dir != TOTAL_OF_DIRECTION && posX != 0 && bridge[0].posY != BRIDGE_IDLE_HEIGHT) frame++;
    if (frame/YOLK_FRAME_VALUE >= TOTAL_YOLK_RUN_SPRITE) frame = 0;
}

