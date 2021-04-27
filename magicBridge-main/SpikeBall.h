#ifndef SPIKEBALL_H
#define SPIKEBALL_H

#include <vector>

#include "Enemy.h"
#include "Core.h"
#include "Coin.h"
#include "Music.h"

const int MAX_ROWS = 5;
const int NUM_OF_EMPTY_POS = 4;
const int EMPTY_POS_WIDTH = NUM_OF_EMPTY_POS * SPIKEBALL_WIDTH;
const int NUM_OF_COLS = 9;

struct Coin;

struct Ball : public Enemy
{
    Ball();
    ~Ball();
    void render(SDL_Renderer* renderer, STATE state);
    void free();

    bool setBall;
};

struct SpikeBall : public Enemy
{
    SpikeBall();
    ~SpikeBall();
    void setPos();
    void move(double mul);
    bool checkCollision(Yolk* yolk);
    void increaseVelY();
    void render(SDL_Renderer* renderer, STATE state);
    void free();

    int numOfRows;
    int firstEmptyPos, lastEmptyPos;
    bool setCoin;
    Ball **ball;
    Coin *coin;
    vector <Coin*> fcoin;
    Music _music;
};

#endif // SPIKEBALL_H
