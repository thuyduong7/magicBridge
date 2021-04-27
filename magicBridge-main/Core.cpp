#include "Core.h"
#include "Materials.h"
#include "Music.h"

using namespace std;

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
Game game;
Materials material;
Music music;

Core::Core()
{
    //quit = false;
    mode = 1;
}

Core::~Core(){}

//Initiailize SDL
bool Core::init(const char* gameTitle, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        cout << "Fail to initialize SDL. SDL_Error: " << SDL_GetError();
        return false;
    }
    window = SDL_CreateWindow(gameTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL){
        cout << "Fail to create window. SDL_Error: " << SDL_GetError();
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL){
        cout << "Fail to create renderer. SDL_Error: " << SDL_GetError();
        return false;
    }
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) &imgFlags)){
        cout << "Fail to initialize SDL_image. IMG_Error: " << IMG_GetError();
        return false;
    }
     //Initialize SDL_mixer
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError();
        return false;
    }
    if (TTF_Init() == -1){
        cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError();
        return false;
    }
    return true;
}

bool Core::loadMedia()
{
    //Load all needed materials for the game
    if (!material.load(renderer)){
        return false;
    }
    //Load music
    if (!music.loadMusic()){
        return false;
    }
    //Initialize characters, objects,...
    if (!game.init()){
        cout << "Fail to initialize game.";
        return false;
    }
    return true;
}

void Core::handleEvent(bool& quit)
{
    if (quit) return;

    SDL_Event e;
    while (SDL_PollEvent(&e) != 0){
        if (e.type == SDL_QUIT){
            quit = true;
        }

        else{
            switch (mode)
            {
                case 1:
                    game.handleEventStart(e,music,mode,quit);
                    break;

                case 2:
                    game.handleEventPlaying(e,music,mode,quit);
                    break;

                case 3:
                    game.handleEventHelp(e,music,mode);
                    break;

                case 4:
                    game.handleEventPause(e,music,mode);
                    break;

                case 5:
                    game.handleEventEnd(e,music,mode);
                    break;
            }
        }
    }
    if (mode == 2) game.loop(quit,music,mode);
}

void Core::render(bool& quit)
{
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        switch (mode)
            {
                case 1:
                    game.start(renderer,quit,music);
                    break;

                case 2:
                    game.playing(renderer,quit);
                    game.update();
                    break;

                case 3:
                    game.help(renderer,quit,music);
                    break;

                case 4:
                    game.pause(renderer,quit);
                    break;

                case 5:
                    game.end(renderer,quit);
                    break;
            }

        SDL_RenderPresent(renderer);

        //if (mode == 2) game.update();

}

void Core::close()
{
    material.free();
    game.free();
    music.free();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    SDL_Quit();
    IMG_Quit();
}

