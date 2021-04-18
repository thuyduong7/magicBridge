#ifndef SPIKE_H
#define SPIKE_H

#include "Enemy.h"
#include "Core.h"

struct Spike : public Enemy
{
    Spike();
    ~Spike();
    void setPos();
    void move();
    bool checkCollision(Yolk* yolk);
    //void increaseVelY();
    void render(SDL_Renderer* renderer, bool& quit);
    void free();

    DIRECTION dir;
};

#endif // SPIKE_H
