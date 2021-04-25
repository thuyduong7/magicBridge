#ifndef BIRD_H
#define BIRD_H

#include "Enemy.h"
#include "Core.h"

struct Bird : public Enemy
{
    Bird();
    ~Bird();
    void setPos();
    void move(double mul);
    bool checkCollision(Yolk* yolk);
    void increaseVelY();
    void render(SDL_Renderer* renderer, STATE state);
    void free();

    DIRECTION dir;
    int minX, maxX;
    int distance;
    SDL_RendererFlip flip;
};

#endif // BIRD_H
