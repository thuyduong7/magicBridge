#include "Materials.h"
#include "Yolk.h"

SDL_Texture* Materials::dot;
SDL_Texture* Materials::yolk;
SDL_Rect Materials::yolkIdle;
SDL_Rect Materials::yolkRun[TOTAL_YOLK_RUN_SPRITE];
SDL_Rect Materials::yolkDie;

bool Materials::load()
{
    dot = Texture::loadFromFile("Assets/Dot.png");
    if (dot == NULL){
        cout << "Fail to load dot\n";
        return false;
    }
    yolk = Texture::loadFromFile("Assets/Yolk.png");
    if (yolk == NULL){
        cout << "Fail to load Yolk\n";
        return false;
    }

    yolkIdle.x = 0;
    yolkIdle.y = 0;
    yolkIdle.w = YOLK_WIDTH;
    yolkIdle.h = YOLK_HEIGHT;

    yolkDie.x = 0;
    yolkDie.y = YOLK_HEIGHT;
    yolkDie.w = YOLK_WIDTH;
    yolkDie.h = YOLK_HEIGHT;

    for (int i = 0; i < TOTAL_YOLK_RUN_SPRITE; i++){
        yolkRun[i].x = YOLK_WIDTH * i;
        yolkRun[i].y = YOLK_HEIGHT*2;
        yolkRun[i].w = YOLK_WIDTH;
        yolkRun[i].h = YOLK_HEIGHT;
    }
    return true;
}

SDL_Texture* Materials::getTexture(MAT_TYPE type)
{
    SDL_Texture* newTexture = NULL;
    if (type == BRIDGE) newTexture = dot;
    else if (type == YOLK) newTexture = yolk;
    return newTexture;
}

void Materials::free()
{
    SDL_DestroyTexture(dot);
}
