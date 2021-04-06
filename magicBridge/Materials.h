#ifndef MATERIALS_H
#define MATERIALS_H

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int TOTAL_YOLK_RUN_SPRITE = 6;
const int TOTAL_RADISH_SPRITE = 5;
const int TOTAL_SPIKE_SPRITE = 5;
const int TOTAL_BIRD_SPRITE = 2;

enum MAT_TYPE
{
    BACKGROUND,
    BRIDGE,
    YOLK,

    //Enemies
    RADISH,
    SPIKE,
    BIRD,
    SPIKEBALL
};

enum SPRITE_TYPE
{
    IDLE,
    RUN,
    DIE
};

struct Materials
{
    bool load(SDL_Renderer* renderer);
    SDL_Texture* loadFromFile(string path, SDL_Renderer* renderer);
    SDL_Texture* getTexture(MAT_TYPE type);
    SDL_Rect getSprite(MAT_TYPE type, SPRITE_TYPE _type, int i = 0);
    void render(SDL_Renderer* renderer, SDL_Texture* _texture, SDL_Rect scrRect, SDL_Rect dstRect,
                SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0, SDL_Point* center = NULL);
    void free();

};

#endif // MATERIALS_H
