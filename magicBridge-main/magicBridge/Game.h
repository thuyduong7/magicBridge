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
#include <vector>

bool initGame();
void handleEventStart(const SDL_Event& e, const Music& music, MODE& mode, bool& quit);
void handleEventHelp(const SDL_Event& e, const Music& music, MODE& mode);
void handleEventPlaying(const SDL_Event& e, const Music& music, MODE& mode, bool& quit);
void handleEventEnd(const SDL_Event& e, const Music& music, MODE& mode);
void handleEventPause(const SDL_Event& e, const Music& music, MODE& mode);
void loop(const Music& music, MODE& mode);
void update();
void start(SDL_Renderer* renderer, const Music& music);
void help(SDL_Renderer* renderer, const Music& music);
void playing(SDL_Renderer* renderer);
void pause(SDL_Renderer* renderer);
void end(SDL_Renderer* renderer);
void freeGame();

#endif // GAME_H
