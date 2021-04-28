#ifndef GAME_H
#define GAME_H

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

#include <fstream>

bool initGame();

void handleEventStart(const SDL_Event& e, const Music& music, MODE& mode, bool& quit);
void handleEventPlaying(const SDL_Event& e, const Music& music, MODE& mode, bool& quit);
void handleEventHelp(const SDL_Event& e, const Music& music, MODE& mode);
void handleEventSettings(const SDL_Event& e, const Music& music, MODE& mode);
void handleEventPause(const SDL_Event& e, const Music& music, MODE& mode);
void handleEventEnd(const SDL_Event& e, const Music& music, MODE& mode);

void loop(const Music& music, MODE& mode);
void update();

void start(SDL_Renderer* renderer, const Music& music);
void playing(SDL_Renderer* renderer);
void help(SDL_Renderer* renderer, const Music& music);
void settings(SDL_Renderer* renderer, const Music& music);
void pause(SDL_Renderer* renderer);
void end(SDL_Renderer* renderer);

void freeGame();

#endif // GAME_H
