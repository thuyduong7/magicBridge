#ifndef SPIKE_H
#define SPIKE_H

#include "Enemy.h"
#include "Core.h"

struct Spike : public Enemy
{
    Spike();
    ~Spike();
    void setPos();
    void move(double mul);
    bool checkCollision(Yolk* yolk);
    void render(SDL_Renderer* renderer, STATE state);

    DIRECTION dir;
};

#endif // SPIKE_H
