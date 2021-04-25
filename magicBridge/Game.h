#ifndef GAME_H
#define GAME_H

#include "Core.h"
#include "Materials.h"
#include "Music.h"
#include "Background.h"
#include "Bridge.h"
#include "Yolk.h"
#include "Enemy.h"
#include "Radish.h"
#include "Spike.h"
#include "Bird.h"
#include "SpikeBall.h"
#include "Coin.h"
#include "Timer.h"
#include "Text.h"
#include "Button.h"


struct Game
{
    Game();
    bool init();
    void handleEventStart(SDL_Event& e, const Music& music, int& mode, bool& quit);
    void handleEventHelp(SDL_Event& e, const Music& music, int& mode);
    void handleEventPlaying(SDL_Event& e, const Music& music, int& mode, bool& quit);
    void handleEventEnd(SDL_Event& e, const Music& music, int& mode);
    void handleEventPause(SDL_Event& e, const Music& music, int& mode);
    void loop(bool& quit, const Music& music, int& mode);
    void update();
    void start(SDL_Renderer* renderer, bool& quit);
    void help(SDL_Renderer* renderer, bool& quit);
    void playing(SDL_Renderer* renderer, bool& quit);
    void pause(SDL_Renderer* renderer, bool& quit);
    void end(SDL_Renderer* renderer, bool& quit);
    void free();

    //Background
    Background* background;
    Background* backgroundLayer1;
    Background* backgroundLayer2;
    Background* backgroundLayer3;
    Background* backgroundLayer4;

    //Buttons
    Button* startButton;
    Button* helpButton;
    Button* pauseButton;
    Button* continueButton;
    Button* quitButton;

    //Bridge comprises of 11 dots
    Bridge* bridge;
    Yolk* yolk;
    Timer timer;
    Text text;

    double mul;
    int round, highScore, lastMode;
    //DIRECTION cur_dir, last_cur_dir;
};

#endif // GAME_H
