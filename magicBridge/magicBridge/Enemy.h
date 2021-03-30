#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>

#include "Materials.h"

const int FRAME_VALUE = 6;

const int RADISH_WIDTH = 65;
const int RADISH_HEIGHT = 63;

const int SPIKE_WIDTH = 70;
const int SPIKE_HEIGHT = 78;

struct Enemy
{
    Enemy(){};
    Enemy(MAT_TYPE _type);
    SDL_Texture* getTexture();
    void setPos(MAT_TYPE _type);
    void render(SDL_Renderer* renderer);

    MAT_TYPE type;
    int posX, posY;
    int width, height;
    int velX, velY;
    int totalSprite;
    SDL_Texture* texture;
    Materials enemyMat;
    SDL_Rect srcRect, dstRect;
    int frame;

};

#endif // ENEMY_H
