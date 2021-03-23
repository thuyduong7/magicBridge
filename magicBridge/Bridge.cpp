#include "Bridge.h"
#include "Materials.h"
#include "Core.h"
#include "Texture.h"
//Bridge includes 11 dots

Bridge::Bridge()
{
    width = DOT_WIDTH;
    height = DOT_HEIGHT;
    posX = 0;
    posY = 0;
    texture = Materials::getTexture(BRIDGE);
    dir = TOTAL_OF_DIRECTION;
    srcRect = {posX, posY, width, height};
}

Bridge::~Bridge()
{

}


void Bridge::setDir(DIRECTION _dir)
{
    dir = _dir;
}

void Bridge::render()
{
    dstRect = {posX, posY, width, height};
    Texture::render(texture, srcRect, dstRect);
}


