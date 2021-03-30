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

struct Game;

struct Core
{
    public:
        Core();
        ~Core();
        bool init(const char* gameTitle, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
        bool loadMedia();
        void handleEvent();
        void render();
        void close();
        bool quit;
};

#endif // CORE_H

