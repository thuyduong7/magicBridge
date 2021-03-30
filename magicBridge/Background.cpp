#include "Background.h"
#include "Core.h"

Background::Background()
{
    texture = backgroundMat.getTexture(BACKGROUND);
    posX = 0;
    posY = 0;
    width = SCREEN_WIDTH;
    height = SCREEN_HEIGHT;
    srcRect = {posX, posY, width, height};
}

Background::~Background()
{

}

void Background::render(SDL_Renderer* renderer)
{
    dstRect = srcRect;
    backgroundMat.render(renderer, texture, srcRect, dstRect);
}
