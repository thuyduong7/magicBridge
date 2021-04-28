#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <SDL.h>

using namespace std;

const int SCREEN_WIDTH = 440;
const int SCREEN_HEIGHT = 780;

const int PILLAR_WIDTH = 40;

const int PLAYING_SCREEN_WIDTH = SCREEN_WIDTH - 2 * PILLAR_WIDTH;

// The height at which the bridge remains idle
const int BRIDGE_IDLE_HEIGHT = 590;

//The min y that bridge can go up to
const int MIN_POS_Y = BRIDGE_IDLE_HEIGHT - 100;

//The max y that bridge can fall down to
const int MAX_POS_Y = BRIDGE_IDLE_HEIGHT + 100;

const int MIN_POS_X = PILLAR_WIDTH;
const int MAX_POS_X = MIN_POS_X + PLAYING_SCREEN_WIDTH;

//Modes to handle events and render during the game
enum MODE
{
    START,
    PLAYING,
    HELP,
    SETTINGS,
    PAUSE,
    END
};

struct Core
{
    Core();
    ~Core();
    bool init(const char* gameTitle, const int& SCREEN_WIDTH, const int& SCREEN_HEIGHT);
    bool loadMedia();
    void handleEvent(bool& quit);
    void render(bool& quit);
    void close();

    SDL_Renderer* renderer = NULL;
    SDL_Window* window = NULL;
    MODE mode;
};

#endif // CORE_H

