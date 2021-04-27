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

enum STATE
{
    PLAY,
    //After hitting for the first time, the main character will be protected for some seconds
    PAUSE_1,
    //The main character hit enemies for the first time and will die if it hit enemies again during an amount of time
    HIT_1,
    //The main character hit enemies for the second time and died
    HIT_2,
    //After this time, the main character will get back to normal
    PAUSE_2
};

struct Yolk
{
        Yolk(int x, int y);
        ~Yolk();
        //static SDL_Rect* setSprite(SDL_Rect* spriteSheet);
        void setDir(double _gap);
        //void run(double _gap);
        void move(Bridge* bridge);
        void handleCollision();
        void checkState();
        void blend(Uint32 pauseTime);
        void render(SDL_Renderer* renderer);

        int width, height;
        double posX, posY;
        double velX, lastVelX;
        //std::queue <DIRECTION> dir;
        DIRECTION dir, last_dir;
        STATE state;
        SDL_Texture* texture;
        Materials yolkMat;
        SDL_Rect srcRect, dstRect;
        int frame;
        double gap;
        bool change_dir;
        bool hit;
        int time, numOfCoins;
        //Use for blending when main character hit objects for the first time
        Uint8 a;
        bool decrease;
        int change;
        Uint32 pauseTime, hitTime;
};

#endif // YOLK_H
