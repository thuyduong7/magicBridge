#ifndef SPIKEBALL_H
#define SPIKEBALL_H

#include "Enemy.h"
#include "Core.h"
#include "Ball.h"

const int MAX_ROWS = 5;
const int NUM_OF_EMPTY_POS = 4;
const int NUM_OF_COLS = 10;

struct Ball;

struct SpikeBall : public Enemy
{
    SpikeBall();
    ~SpikeBall();
    void setPos();
    void move();
    void render(SDL_Renderer* renderer);

    int numOfRows;
    int firstEmptyPos;
    Ball **ball;
    bool setBall;
};

#endif // SPIKEBALL_H
