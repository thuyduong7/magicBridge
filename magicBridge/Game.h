#ifndef GAME_H
#define GAME_H

#include "Background.h"
#include "Bridge.h"
#include "Yolk.h"

//The max number of time to press left or right
const int COUNT_MAX = 4;

struct Game
{
    bool init();
    void handleEvent(SDL_Event& e);
    void loop();
    void render();

    Background* background;
    //Bridge comprises of 11 dots
    Bridge* bridge;
    Yolk* yolk;
    DIRECTION cur_dir, last_cur_dir;
};

#endif // GAME_H
