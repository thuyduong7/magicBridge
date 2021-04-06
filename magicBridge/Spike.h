#ifndef SPIKE_H
#define SPIKE_H

#include "Enemy.h"
#include "Core.h"

struct Spike : public Enemy
{
    Spike();
    void setPos();
    void move();
    bool checkCollision(Yolk* yolk);
    void render(SDL_Renderer* renderer);

    DIRECTION dir;
};

#endif // SPIKE_H
