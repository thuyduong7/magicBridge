#ifndef GAME_H
#define GAME_H

#include "Background.h"
#include "Bridge.h"
#include "Yolk.h"
#include "Enemy.h"
#include "Radish.h"
#include "Spike.h"
#include "Bird.h"
#include "SpikeBall.h"
#include "Coin.h"

struct Game
{
    bool init();
    void handleEvent(SDL_Event& e);
    void keypressed(SDL_Event& e);
    void keyreleased(SDL_Event& e);
    void loop(bool& quit);
    void update();
    void render(SDL_Renderer* renderer, bool& quit, bool& die);
    void free();

    Background* background;
    Background* backgroundLayer;
    //Bridge comprises of 11 dots
    Bridge* bridge;
    Yolk* yolk;
    //DIRECTION cur_dir, last_cur_dir;


    Enemy* recentEnemy;
};

#endif // GAME_H
