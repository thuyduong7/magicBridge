#include "Background.h"
#include "Core.h"

//Background
Background::Background(MAT_TYPE _type)
{
    texture = backgroundMat.getTexture(_type);
    posX = 0;
    posY = 0;
    width = SCREEN_WIDTH;
    height = SCREEN_HEIGHT;
    srcRect = {posX, posY, width, height};
    offset = 0;
}

Background::~Background()
{

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
