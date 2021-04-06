#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>

#include "Materials.h"
#include "Bridge.h"
#include "Yolk.h"

const int FRAME_VALUE = 6;

const int RADISH_WIDTH = 65;
const int RADISH_HEIGHT = 63;

const int SPIKE_WIDTH = 70;
const int SPIKE_HEIGHT = 78;

const int BIRD_WIDTH = 92;
const int BIRD_HEIGHT = 66;

const int SPIKEBALL_WIDTH = 44;
const int SPIKEBALL_HEIGHT = 44;

//struct Yolk;

struct Enemy
{
    Enemy(){};
    Enemy(MAT_TYPE _type);
    //SDL_Texture* getTexture();
    virtual void setPos(){};
    virtual void move(){};
    virtual bool checkCollision(Yolk* yolk);
    virtual void render(SDL_Renderer* renderer){};

    MAT_TYPE type;
    double posX, posY;
    int width, height;
    double velX, velY;
    int totalSprite;
    SDL_Texture* texture;
    Materials enemyMat;
    SDL_Rect srcRect, dstRect;
    SDL_Rect collider;
    int frame;

};

#endif // ENEMY_H
