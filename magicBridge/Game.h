#ifndef GAME_H
#define GAME_H

#include "Background.h"
#include "Bridge.h"
#include "Yolk.h"
#include "Enemy.h"



struct Game
{
    bool init();
    void handleEvent(SDL_Event& e);
    void loop();
    void render(SDL_Renderer* renderer);
    void free();

    Background* background;
    //Bridge comprises of 11 dots
    Bridge* bridge;
    Yolk* yolk;
    DIRECTION cur_dir, last_cur_dir;


    Enemy* recentEnemy;
};

#endif // GAME_H
