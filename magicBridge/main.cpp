#include <iostream>

#include "Core.h"

using namespace std;

Core core;
const char* gameTitle = "Magic Bridge";
const int FPS = 70;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* argv[])
{
    if (!core.init(gameTitle, SCREEN_WIDTH, SCREEN_HEIGHT)){
        cout << "Fail to initialize\n";
    }
    else{
        if (!core.loadMedia()){
            cout << "Fail to load media\n";
        }
        else{
            while (!core.quit){
                Uint32 startTime = SDL_GetTicks();
                core.handleEvent();
                core.render();
                Uint32 frameTime = SDL_GetTicks() - startTime;
                if (frameTime < DELAY_TIME){
                    SDL_Delay((int)(DELAY_TIME - frameTime));
                }
            }
        }
    }
    core.close();
    return 0;
}
