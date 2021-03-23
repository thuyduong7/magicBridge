#ifndef MATERIALS_H
#define MATERIALS_H

#include <SDL.h>
#include <SDL_image.h>

#include "Texture.h"

const int TOTAL_YOLK_RUN_SPRITE = 6;

enum MAT_TYPE
{
    BRIDGE,
    YOLK
};

struct Materials
{
    static bool load();
    static SDL_Texture* getTexture(MAT_TYPE type);
    void getSprite();
    static void free();

    static SDL_Texture* dot;
    static SDL_Texture* yolk;
    static SDL_Rect yolkIdle;
    static SDL_Rect yolkRun[TOTAL_YOLK_RUN_SPRITE];
    static SDL_Rect yolkDie;
};

#endif // MATERIALS_H
