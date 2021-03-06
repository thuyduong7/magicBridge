#include <ctime>

#include "Core.h"

const char* gameTitle = "Magic Bridge";
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* argv[])
{
    srand(time(0));
    Core core;
    if (!core.init(gameTitle, SCREEN_WIDTH, SCREEN_HEIGHT)){
        cout << "Fail to initialize\n";
    }
    else{
        if (!core.loadMedia()){
            cout << "Fail to load media\n";
        }
        else{
            bool quit = false;
            while (!quit){
                Uint32 startTime = SDL_GetTicks();
                core.handleEvent(quit);
                core.render(quit);
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
