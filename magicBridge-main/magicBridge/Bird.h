#ifndef BIRD_H
#define BIRD_H

#include "Enemy.h"
#include "Core.h"

struct Bird : public Enemy
{
    Bird();
    ~Bird();
    void setPos();
    void move(const double& mul);
    bool checkCollision(Yolk* yolk);
    void increaseVelY();
    void render(SDL_Renderer* renderer, STATE state);

    DIRECTION dir;
    int minX, maxX;
    int distance;
    SDL_RendererFlip flip;

    double BIRD_VEL_X = 1;
    double BIRD_VEL_Y = 3;
};

#endif // BIRD_H
