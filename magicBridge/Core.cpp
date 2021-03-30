#include "Core.h"
#include "Materials.h"

using namespace std;

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
Game game;
Materials material;

Core::Core()
{
    quit = false;
}

Core::~Core()
{

}

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
    return true;
}

bool Core::loadMedia()
{
    //Load all needed materials for the game
    if (!material.load(renderer)){
        return false;
    }
    //Initialize characters, objects,...
    if (!game.init()){
        cout << "Fail to initialize game.";
        return false;
    }
    return true;
}

void Core::handleEvent()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0){
        if (e.type == SDL_QUIT){
            quit = true;
        }
        else if (e.type == SDL_KEYDOWN){
            game.handleEvent(e);
        }
    }
    game.loop();
}

void Core::render()
{
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        game.render(renderer);

        SDL_RenderPresent(renderer);

}

void Core::close()
{
    material.free();
    game.free();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    SDL_Quit();
    IMG_Quit();
}

