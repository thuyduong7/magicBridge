#ifndef YOLK_H
#define YOLK_H

#include <cmath>

#include "Bridge.h"

const int YOLK_WIDTH = 78;
const int YOLK_HEIGHT = 71;
const int YOLK_FRAME_VALUE = 4;
const int STANDING_GAP = 3;

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
        Yolk(const int& x, const int& y);
        ~Yolk();
        void setDir(double _gap);
        void move(Bridge* bridge);
        void handleCollision();
        void checkState();
        void blend(Uint32 pauseTime);
        void render(SDL_Renderer* renderer);

        STATE state;
        int width, height;
        double posX, posY;
        SDL_Texture* texture;
        SDL_Rect srcRect, dstRect;
        double velX, lastVelX;
        DIRECTION dir, last_dir;
        Materials yolkMat;
        int frame;
        // Velocity of main character depends on the gap between the current highest point of the bridge and its idle height
        double gap;
        // Check if main character is changing direction or not
        // If it is, it will continue on the last direction for a short time
        //according to its last velocity (lastVelX) before changing direction
        bool change_dir;
        //The number of times to move on the last direction before changing direction
        //and it is also used to make the main character go up for a short time before ending game
        int time;
        //Check if main character hit enemies or not
        bool hit;
        int score;
        //Use for blending when main character hit enemies
        Uint8 a;
        //Check when to decrease or increase the alpha to make flicker effects for main character
        bool decrease;
        //The amount of time to continuously decrease or increase the alpha
        int change;
        Uint32 pauseTime, hitTime;
};

#endif // YOLK_H
