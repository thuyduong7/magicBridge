#ifndef YOLK_H
#define YOLK_H

#include <SDL.h>
//#include <queue>
#include <cmath>

#include "Bridge.h"

const int YOLK_WIDTH = 78;
const int YOLK_HEIGHT = 71;
const int YOLK_FRAME_VALUE = 4;
const int STANDING_GAP = 3;

//const int YOLK_VEL = 2;

struct Yolk
{
        Yolk(int x, int y);
        ~Yolk();
        //static SDL_Rect* setSprite(SDL_Rect* spriteSheet);
        void setDir(DIRECTION _dir);
        void run(double _gap);
        void move(Bridge* bridge);
        void render(SDL_Renderer* renderer, Bridge* bridge, bool& quit, bool& die);

        int width, height;
        double posX, posY;
        double velX;
        //std::queue <DIRECTION> dir;
        DIRECTION dir, last_dir;
        SDL_Texture* texture;
        Materials yolkMat;
        SDL_Rect srcRect, dstRect;
        int frame;
        double gap;
        bool change_dir;
        int time, numOfCoins;
};

#endif // YOLK_H
