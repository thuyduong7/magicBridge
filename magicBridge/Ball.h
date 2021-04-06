#ifndef BALL_H
#define BALL_H

#include "Enemy.h"
#include "Core.h"

struct Ball : public Enemy
{
    Ball();
    void render(SDL_Renderer* renderer);
};

#endif // BALL_H
