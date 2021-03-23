#include "Game.h"
#include "Core.h"
#include "Materials.h"
#include <iostream>
using namespace std;

bool Game::init()
{
    bool success = true;
    bridge = new Bridge [NUM_OF_DOTS];
    for (int i = 0; i < NUM_OF_DOTS; i++){
        bridge[i].posX = i * DOT_WIDTH;
        // 80 gives enough space for bridge to move dowm
        bridge[i].posY = BRIDGE_IDLE_HEIGHT;
        bridge[i].texture = Materials::getTexture(BRIDGE);
        if (bridge[i].texture == NULL) success = false;
    }
    // Set Yolk to stand on the bridge
    yolk = new Yolk((SCREEN_WIDTH - YOLK_WIDTH)/2, bridge[0].posY - YOLK_HEIGHT);
    if (yolk->texture == NULL) success = false;
    //last_cur_dir = TOTAL_OF_DIRECTION;
    return success;
}

void Game::handleEvent(SDL_Event& e)
{
    if (e.key.keysym.sym == SDLK_LEFT){
        bridge->setDir(LEFT);
        yolk->setDir(LEFT);
    }
    else if (e.key.keysym.sym == SDLK_RIGHT){
        bridge->setDir(RIGHT);
        yolk->setDir(RIGHT);
    }
}

void Game::loop()
{
    if (bridge->dir == LEFT){
        if (bridge[0].posY < MAX_POS_Y){
            for (int i = 0; i < NUM_OF_DOTS; i++){
                // (i-NUM_OF_DOTS/2) to return a symmetry  ( -5 -4 -3 -2 -1 0 1 2 3 4 5 )
                // *3 to increase the speed of the bridge coming up and down
                // The dot in the middle remains the same
                bridge[i].posY -= (i - NUM_OF_DOTS/2)*3;
            }
        }
        yolk->run(bridge[0].posY - BRIDGE_IDLE_HEIGHT);
        bridge->dir = TOTAL_OF_DIRECTION;
    }
    if (bridge->dir == RIGHT){
        if (bridge[NUM_OF_DOTS-1].posY < MAX_POS_Y){
            for (int i = 0; i < NUM_OF_DOTS; i++){
                // (i-NUM_OF_DOTS/2) to return a symmetry  ( -5 -4 -3 -2 -1 0 1 2 3 4 5 )
                // *3 to increase the speed of the bridge coming up and down
                // The dot in the middle remains the same
                bridge[i].posY += (i - NUM_OF_DOTS/2)*3;
            }
        }
        yolk->run(bridge[0].posY - BRIDGE_IDLE_HEIGHT);
        bridge->dir = TOTAL_OF_DIRECTION;
    }

    yolk->move(bridge);
}

void Game::render()
{
    yolk->render(bridge);
    for (int i = 0; i < NUM_OF_DOTS; i++){
        bridge[i].render();
    }
}


