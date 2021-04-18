#ifndef BALL_H
#define BALL_H

#include "Enemy.h"
#include "Core.h"

struct Ball : public Enemy
{
    Ball();
    ~Ball();
    void render(SDL_Renderer* renderer, bool quit);
    void free();

    bool setBall;
};

#endif // BALL_H
