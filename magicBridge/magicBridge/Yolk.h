#ifndef YOLK_H
#define YOLK_H

#include <SDL.h>
#include <queue>
#include <cmath>

#include "Bridge.h"
#include "Enemy.h"

const int YOLK_WIDTH = 80;
const int YOLK_HEIGHT = 71;
const int YOLK_FRAME_VALUE = 4;

//const int YOLK_VEL = 2;

struct Yolk
{
        Yolk(int x, int y);
        ~Yolk();
        //static SDL_Rect* setSprite(SDL_Rect* spriteSheet);
        void setDir(DIRECTION _dir);
        void run(double _gap);
        void move(Bridge* bridge);
        void checkCollision(Enemy enemy);
        void render(SDL_Renderer* renderer, Bridge* bridge);

        int width, height;
        double posX, posY;
        double velX;
        std::queue <DIRECTION> dir;
        DIRECTION cur_dir, last_cur_dir;
        SDL_Texture* texture;
        Materials yolkMat;
        SDL_Rect srcRect, dstRect;
        int frame;
        double gap;
};

#endif // YOLK_H