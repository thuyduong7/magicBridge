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

const int BIRD_WIDTH = 85;
const int BIRD_HEIGHT = 61;

const int SPIKEBALL_WIDTH = 40;
const int SPIKEBALL_HEIGHT = 40;

const int COIN_WIDTH = 28;
const int COIN_HEIGHT = 37;

const double VEL_Y = 3;
const double SPIKE_VEL_Y = 2.5;

struct Enemy
{
    Enemy(){};
    Enemy(MAT_TYPE _type);
    ~Enemy(){};
    //SDL_Texture* getTexture();
    virtual void setPos(){};
    virtual void move(double mul){};
    virtual bool checkCollision(Yolk* yolk);
    //virtual void increaseVelY();
    virtual void render(SDL_Renderer* renderer, STATE state){};
    virtual void free();

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
    double multiple;
};

#endif // ENEMY_H
