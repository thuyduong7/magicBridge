#ifndef RADISH_H
#define RADISH_H

#include "Enemy.h"
#include "Core.h"

struct Radish : public Enemy
{
    Radish();
    ~Radish();
    void setPos();
    void move();
    void render(SDL_Renderer* renderer);

    DIRECTION dir;
    int defaultPosX;
    int time;
};

#endif // RADISH_h
