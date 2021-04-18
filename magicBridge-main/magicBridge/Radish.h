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
    bool checkCollision(Yolk* yolk);
    //void increaseVelY();
    void render(SDL_Renderer* renderer, bool& quit);
    void free();

    DIRECTION dir;
    int defaultPosX;
    int time;
};

#endif // RADISH_h
