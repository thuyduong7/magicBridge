#include "Yolk.h"
#include "Core.h"
#include "Materials.h"

Yolk::Yolk(int x, int y)
{
    width = YOLK_WIDTH;
    height = YOLK_HEIGHT;
    posX = x;
    posY = y;
    velX = 0;
    lastVelX = 0;
    texture = yolkMat.getTexture(YOLK);
    dir = TOTAL_OF_DIRECTION;
    last_dir = TOTAL_OF_DIRECTION;
    srcRect = {posX, posY, width, height};
    frame = 0;
    change_dir = false;
    time = 0;
    score = 0;
    a = 255;
    decrease = true;
    change = 0;
    state = PLAY;
    hit = false;
}

Yolk::~Yolk()
{

}

void Yolk::setDir(double _gap)
{
    gap = abs(_gap);

    if (_gap < 0) dir = RIGHT;
    else if (_gap > 0) dir = LEFT;
    else dir = TOTAL_OF_DIRECTION;
    if (last_dir != dir && last_dir != TOTAL_OF_DIRECTION){
        // If Yolk is on the edge of the screen, Yolk will change direction immediately (velX = 0)
        // Or else he will move in his last direction for a short time before changing direction
        if (posX > MIN_POS_X && posX < (MAX_POS_X-YOLK_WIDTH)) change_dir = true;
        else velX = 0;
    }
    last_dir = dir;
}

void Yolk::move(Bridge* bridge)
{
    if (change_dir){
        time++;
        if (dir == LEFT) velX += (lastVelX/200);
        else velX -= (lastVelX/200);
        posX += velX;
        if (posX <= MIN_POS_X){
            posX = MIN_POS_X;
            time = 25;
        }
        if (posX >= (MAX_POS_X - YOLK_WIDTH)){
            posX = MAX_POS_X - YOLK_WIDTH;
            time = 25;
        }
        if (time == 25){
            velX = 0;
            time = 0;
            change_dir = false;
        }
    }
    else {
        if (dir == LEFT){
            velX -= (gap/500);
            posX += velX;
            if (posX <= MIN_POS_X){
                posX = MIN_POS_X;
                dir = TOTAL_OF_DIRECTION;
            }
        }
        else if (dir == RIGHT){
            velX += (gap/500);
            posX += velX;
            if (posX >= (MAX_POS_X - YOLK_WIDTH)){
                posX = MAX_POS_X - YOLK_WIDTH;
                dir = TOTAL_OF_DIRECTION;
            }
        }
        lastVelX = velX;
    }
    // Set posY according to posX
    posY = bridge[int(posX/DOT_WIDTH)].posY - YOLK_HEIGHT + STANDING_GAP;
    if (posX == MIN_POS_X) posY = bridge[0].posY - YOLK_HEIGHT + STANDING_GAP;
    //cout << dir << ' ' << posX << ' ' << posY << endl;

}

void Yolk::handleCollision()
{
    if (state == PLAY){
        state = PAUSE_1;
        pauseTime = SDL_GetTicks();
        hit = true;
    }
    else if (state == HIT_1 || state == PAUSE_2){
        state = HIT_2;
        time = 0;
        hit = true;
    }
}

void Yolk::checkState()
{
    switch (state)
    {
        case PAUSE_1:
            blend(pauseTime);
            if ((SDL_GetTicks()-pauseTime) >= 3000){
                state = HIT_1;
                hitTime = SDL_GetTicks();
                //cout << "HIT_1" << endl;
            }
            break;

        case PAUSE_2:
            blend(pauseTime);
            if ((SDL_GetTicks()-pauseTime) >= 1000){
                state = PLAY;
                hitTime = SDL_GetTicks();
                //cout << "PLAY" << endl;
            }
            break;

        case HIT_1:
            if ((SDL_GetTicks()-hitTime) >= 9000){
                state = PAUSE_2;
                pauseTime = SDL_GetTicks();
                //cout << "PAUSE_2" << endl;
            }
    }
}

void Yolk::blend(Uint32 pauseTime)
{
    if (decrease){
            //cout << SDL_GetTicks() - pauseTime << endl;
            a -= 15;
            change++;

        if (change == 5){
            decrease = false;
            change = 0;
        }
    }
    else if (!decrease){
            //cout << SDL_GetTicks() - pauseTime << endl;
            a += 15;
            change++;

        if (change == 5){
            decrease = true;
            change = 0;
        }
    }
}

void Yolk::render(SDL_Renderer* renderer)
{
    dstRect = {posX, posY, width, height};
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (state != PAUSE_1 && state != PAUSE_2) a = 255;
    switch (state){
        case PLAY:
        {
            if (dir == TOTAL_OF_DIRECTION)
                srcRect = yolkMat.getSprite(YOLK, IDLE);
            //When the bridge is inclined and Yolk is not at the edge of the screen
            //if (posX != MIN_POS_X && posX != (MAX_POS_X - YOLK_WIDTH) && bridge[0].posY != BRIDGE_IDLE_HEIGHT)
            else
                srcRect = yolkMat.getSprite(YOLK, RUN, frame/YOLK_FRAME_VALUE);
            break;
        }
        case PAUSE_1: case HIT_1: case PAUSE_2:
        {
            if (dir == TOTAL_OF_DIRECTION)
                srcRect = yolkMat.getSprite(YOLK, IDLE,1);
            else
                srcRect = yolkMat.getSprite(YOLK, HIT, frame/YOLK_FRAME_VALUE);
            break;
        }
        case HIT_2:
        {
            srcRect = yolkMat.getSprite(YOLK,DIE,0);
            if (time < 7){
                posY -=3;
                time++;
            }
            else posY += 3;
            break;
        }
    }
    if ( (dir == RIGHT && change_dir == false) || (dir == LEFT && change_dir == true) ||
        (posX == MAX_POS_X - YOLK_WIDTH) || (last_dir == RIGHT && gap == 0) )
        flip = SDL_FLIP_HORIZONTAL;

    yolkMat.setAlpha(texture, a);
    yolkMat.render(renderer, texture, srcRect, dstRect, flip);
    if (hit){
        SDL_Delay(500);
        hit = false;
    }
    if (dir != TOTAL_OF_DIRECTION) frame++;
    if (frame/YOLK_FRAME_VALUE >= TOTAL_YOLK_RUN_SPRITE) frame = 0;
}
