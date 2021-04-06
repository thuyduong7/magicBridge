#ifndef BALL_H
#define BALL_H

#include "Enemy.h"
#include "Core.h"

struct Ball : public Enemy
{
    Ball();
    //bool checkCollision(Yolk* yolk);
    void render(SDL_Renderer* renderer);

    bool setBall;
};

#endif // BALL_H
