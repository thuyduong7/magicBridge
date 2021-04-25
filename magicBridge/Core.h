#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Game.h"

const int SCREEN_WIDTH = 440;
const int SCREEN_HEIGHT = 780;

const int PILLAR_WIDTH = 40;

const int PLAYING_SCREEN_WIDTH = SCREEN_WIDTH - 2 * PILLAR_WIDTH;

// The height at which the bridge remains idle
const int BRIDGE_IDLE_HEIGHT = 590;

//The max y that bridge can fall down to
const int MAX_POS_Y = BRIDGE_IDLE_HEIGHT + 100;

//The min y that bridge can go up to
const int MIN_POS_Y = BRIDGE_IDLE_HEIGHT - 100;

const int MIN_POS_X = PILLAR_WIDTH;
const int MAX_POS_X = MIN_POS_X + PLAYING_SCREEN_WIDTH;

const int MIN_BIRD_DISTANCE = PLAYING_SCREEN_WIDTH * 1/3;

struct Game;

struct Core
{
    public:
        Core();
        ~Core();
        bool init(const char* gameTitle, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
        bool loadMedia();
        //bool loadMusic();
        void handleEvent(bool& quit);
        void render(bool& quit);
        void close();
        //bool quit;
        int mode;
};

#endif // CORE_H

