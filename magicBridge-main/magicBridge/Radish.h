#ifndef RADISH_H
#define RADISH_H

#include "Enemy.h"
#include "Core.h"

struct Radish : public Enemy
{
    Radish();
    ~Radish();
    void setPos();
    void move(const double& mul);
    bool checkCollision(Yolk* yolk);
    void render(SDL_Renderer* renderer, STATE state);

    DIRECTION dir;
    int time;
};

#endif // RADISH_h
