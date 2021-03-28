#include "Background.h"
#include "Core.h"
#include "Materials.h"

Background::Background()
{
    texture = Materials::getTexture(BACKGROUND);
    posX = 0;
    posY = 0;
    width = SCREEN_WIDTH;
    height = SCREEN_HEIGHT;
    srcRect = {posX, posY, width, height};
}

Background::~Background()
{

}

void Background::render()
{
    dstRect = srcRect;
    Texture::render(texture, srcRect, dstRect);
}
