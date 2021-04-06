#ifndef BIRD_H
#define BIRD_H

#include "Enemy.h"
#include "Core.h"

enum SIDE
{
    _LEFT,
    _SIDE
};

struct Bird : public Enemy
{
    Bird();
    void setPos();
    void move();
    bool checkCollision(Yolk* yolk);
    void render(SDL_Renderer* renderer);

    SIDE side;
    DIRECTION dir;
    int minX, maxX;
    SDL_RendererFlip flip;
};

#endif // BIRD_H
