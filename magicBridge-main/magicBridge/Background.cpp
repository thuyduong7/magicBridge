#include "Background.h"
#include "Core.h"

Background::Background(MAT_TYPE _type)
{
    texture = backgroundMat.getTexture(_type);
    posX = 0;
    posY = 0;
    width = SCREEN_WIDTH;
    height = SCREEN_HEIGHT;
    srcRect = {posX, posY, width, height};
    offset = 0;
    frame = 0;
    if (_type == BACKGROUND) vel = BACKGROUND_VEL;
    else vel = BACKGROUND_LAYER_VEL;
}

Background::~Background()
{

}

void Background::move(const double mul)
{
    offset += (vel * mul);
    if(offset > height) offset = 0;
}

void Background::render(SDL_Renderer* renderer)
{
    dstRect = {posX, offset, width, height};
    backgroundMat.render(renderer, texture, srcRect, dstRect);
}

void Background::renderOffset(SDL_Renderer* renderer)
{
    dstRect = {posX, offset - height, width, height};
    backgroundMat.render(renderer, texture, srcRect, dstRect);
}

void Background::renderIntro(SDL_Renderer* renderer)
{
    dstRect = {posX, offset, width, height};
    backgroundMat.render(renderer, texture, backgroundMat.getSprite(INTRO,IDLE,frame/INTRO_FRAME_VALUE), dstRect);
    frame++;
    if (frame/INTRO_FRAME_VALUE >= TOTAL_INTRO_SPRITE) frame = 0;
}
