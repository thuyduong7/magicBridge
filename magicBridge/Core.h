#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"

const int SCREEN_WIDTH = 440;
const int SCREEN_HEIGHT = 800;

// The height at which the bridge remains idle
const int BRIDGE_IDLE_HEIGHT = SCREEN_HEIGHT - DOT_HEIGHT - 80;

//The max y that bridge can fall down to
const int MAX_POS_Y = BRIDGE_IDLE_HEIGHT + 70;

//The min y that bridge can go up to
const int MIN_POS_Y = BRIDGE_IDLE_HEIGHT - 70;


struct Game;

struct Core
{
    public:
        Core();
        ~Core();
        bool init(const char* gameTitle, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
        bool loadMedia();
        void handleEvent(bool& quit);
        void render();
        void close();
        //bool quit;
};

#endif // CORE_H

