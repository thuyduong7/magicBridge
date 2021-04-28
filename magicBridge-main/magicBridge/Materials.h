#ifndef MATERIALS_H
#define MATERIALS_H

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int TOTAL_YOLK_IDLE_SPRITE = 2;
const int TOTAL_YOLK_RUN_SPRITE = 6;
const int TOTAL_RADISH_SPRITE = 5;
const int TOTAL_SPIKE_SPRITE = 5;
const int TOTAL_BIRD_SPRITE = 2;
const int TOTAL_COIN_SPRITE = 3;
const int TOTAL_BUTTON_SPRITE = 2;
const int TOTAL_INTRO_SPRITE = 2;

enum MAT_TYPE
{
    BACKGROUND,
    BACKGROUND2,
    BACKGROUNDLAYER1,
    BACKGROUNDLAYER1_2,
    BACKGROUNDLAYER2,
    BACKGROUNDLAYER2_2,
    BACKGROUNDLAYER3,
    BACKGROUNDLAYER4,
    BACKGROUNDLAYER5,
    BACKGROUNDLAYER5_2,
    BACKGROUNDLAYER6,
    INTRO,
    BRIDGE,
    BRIDGE2,
    YOLK,

    //Enemies
    RADISH,
    SPIKE,
    BIRD,
    SPIKEBALL,

    COIN,

    //Buttons
    START_BUTTON,
    HELP_BUTTON,
    SETTINGS_BUTTON,
    TICK_BUTTON,
    CONTINUE_BUTTON,
    QUIT_BUTTON,

};

enum SPRITE_TYPE
{
    IDLE,
    RUN,
    HIT,
    DIE
};


struct Materials
{
    bool load(SDL_Renderer* renderer);
    SDL_Texture* loadFromFile(string path, SDL_Renderer* renderer);
    SDL_Texture* getTexture(MAT_TYPE type);
    SDL_Rect getSprite(MAT_TYPE type, SPRITE_TYPE _type, int i = 0);
    void setAlpha(SDL_Texture* _texture, Uint8 alpha);
    void render(SDL_Renderer* renderer, SDL_Texture* _texture, SDL_Rect scrRect, SDL_Rect dstRect,
                SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0, SDL_Point* center = NULL);
    void free();

};

#endif // MATERIALS_H
