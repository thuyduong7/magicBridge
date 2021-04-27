#ifndef COIN_H
#define COIN_H

#include "Core.h"
#include "Enemy.h"

#include <vector>

struct Coin : public Enemy
{
    Coin();
    ~Coin();
    void setPos(vector<Enemy*> &enemy);
    void move(double mul);
    bool checkCollision(Yolk* yolk);
    bool checkCollisionEnemy(Enemy* enemy);
    //void increaseVelY();
    void render(SDL_Renderer* renderer, STATE state);
    void free();

    int sumOFCoins;
};


#endif // COIN_H
