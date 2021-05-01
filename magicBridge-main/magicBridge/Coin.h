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
    void move(const double& mul);
    bool checkCollision(Yolk* yolk);
    bool checkCollisionEnemy(Enemy* enemy);
    void render(SDL_Renderer* renderer, STATE state);
};


#endif // COIN_H
